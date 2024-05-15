from pprint import pprint
from bs4 import BeautifulSoup as bs
import bs4
import os
import sys
import jinja2
import re
import shutil
from copy import deepcopy

"""RTE Generator to load RTE XML files and generate a set of .c and .h files
"""


"""mapping of objects to template file names (e.g. signalclass uses two template, runnable uses none)
"""

templatemap = {
    "signalclass": ["signalclass", "signaltype"],
    "runnable": [],  # runnables code will be part of swc
    "signalobject": [],  # signalobjects code will be part of the respective pool
    "event": [],  # no code for events
    "resource": [],  # no code for resources
}

"""order in which to generate the files
"""
generate_order = [
    "signalclasses",
    "signalpools",
    "signalobjects",
    "tasks",
    "runnables",
    "swcs",
    "events",
    "resources",
]


class RteGeneratorException(Exception):
    """Custom exception class to be caught by GUI
    """
    pass

class RTEgen():
    """generator main class
    """

    def __init__(self):
        return

    def cfg2dict(self, data):
        """convert configuration data to dictionary

        Args:
            data (bs4 tree): configset as bs4 element tree of config elements w. name and value

        Returns:
            dict: config as dictionary
        """
        config = {}
        for item in data:
            if type(item) is not bs4.element.Tag:
                continue
            if "name" in item.attrs:
                config[item.attrs["name"]] = item.attrs["value"]
            else:
                for k, v in self.cfg2dict(item).items():
                    config[item.name+"_"+k] = v
        config["prefix"] = {}
        for k, v in list(config.items()):
            if k.endswith("Prefix"):
                v = config.pop(k)
                k = k.replace("Prefix", "")
                config["prefix"][k] = v
        return config

    def parseData(self, parent, noWrap=False):
        """convert XML tree into usable format preserving node types

        Args:
            parent (bs4 tree): input data
            noWrap (bool, optional): don't wrap the elment into a {type:{data}} dictionary. Defaults to False.

        Returns:
            dict(str,list(dict(str,dict))): list of elements grouped under their root tag
            e.g.
            {"signalclasses":[
                {"signalclass":{"name":"sc_test"...}}
            ]
            } 
        """
        data = []
        if parent.name == "configset":
            self.configSet = self.cfg2dict(parent)
            return
        if parent.name == "naming":
            self.namingSet = self.cfg2dict(parent)
            return

        for node in parent.children:
            if type(node) is not bs4.element.Tag:
                continue
            ret = self.parseData(node)
            if ret is not None:
                data.append(ret)
            if node.attrs:
                data.append({node.name: node.attrs})
        if not data and parent.attrs:
            return
        if noWrap:
            result = {}
            for item in data:
                for k, v in item.items():
                    result[k] = v
            return result
        return {parent.name: data}

    def getTemplates(self, obj, outdir, template):
        """gather templates for objecttype and generate output file names

        Args:
            obj (str): object type (signalclass, signalovbject etc.)
            outdir (str): location of the output file

        Returns:
            list(tuple(template,filename)): list of templates with corresponding filename
        """
        filedir = os.path.dirname(self.currentFile)
        templatePath = os.path.join(filedir, template)
        templates = []
        for suffix in ["h", "c"]:
            for templatename in templatemap.get(obj, [obj]):
                templateFile = "%s/%s.tmpl.%s" % (templatePath,
                                                  templatename, suffix)
                lines=[]
                outputFile = None
                with open(templateFile) as fp:
                    for line in fp:
                        match = re.search("#Path: (.*)",line)
                        if match:
                            outputFile="%s.%s"%(match.group(1),suffix)
                            outputFile = os.path.join(outdir,outputFile)
                            continue
                        lines.append(line)
                if outputFile is None:
                    raise RuntimeError("Missing path in template %r"%templateFile)
                
                    
                    
                template = self.env.from_string("".join(lines))
                templates.append((templatename,template, self.env.from_string(outputFile)))
        return templates

    def writeFile(self, filename, content):
        """write content to file, preserving user code
        -find usercode blocks by RegEx
        -save usercode by tag
        -insert blocks into new content

        Args:
            filename (str): name of the file
            content (str): content to write
        """
        start = self.configSet["userCodeStart"]
        end = self.configSet["userCodeEnd"]
        startRgx = start.format(TAG="(.*?)")

        userCodeSave = {}
        os.makedirs(os.path.dirname(filename),exist_ok=True)
        if os.path.isfile(filename):  # if the file exists
            with open(filename, "r") as fp:
                userCode = fp.read()
                start = self.configSet["userCodeStart"]
                end = self.configSet["userCodeEnd"]
                startRgx = start.format(TAG="(.*?)")
                # find all usercode start markers
                for start_marker in re.finditer(startRgx, userCode):
                    marker = start_marker.group(1)  # save tag
                    codeFind = "{start}(.*?){end}".format(start=start.format(
                        TAG=marker), end=end.format(TAG=marker))  # build REGEX for code block
                    # find complete code block
                    match = re.search(codeFind, userCode, flags=re.DOTALL)
                    if match is not None:
                        userCodeSave[marker] = match.group(
                            1)  # save code block

        # find usercode markers in ouput content
        for start_marker in re.finditer(startRgx, content):
            marker = start_marker.group(1)
            codeFind = "{start}(.*?){end}".format(start=start.format(TAG=marker),
                                                  end=end.format(TAG=marker))  # build REGEX for code block

            # find complete code block
            match = re.search(codeFind, content, flags=re.DOTALL)
            if match and marker in userCodeSave:
                # replace the content section with the saved user code
                content = content[:match.start(
                    1)]+userCodeSave[marker]+content[match.end(1):]

        with open(filename, "w") as fp:
            fp.write(content)

    def generateObjects(self, itemtype, inputdata, templates):
        """render and write out all templates

        Args:
            itemtype (str): type of the object (e.g. signalclass)
            data (any): data to use in the templates
            templates (list): list of templates and filesnames to render (as produced by getTemplates
        """


        for templatetype, template, filename in templates:
            data=inputdata
            name = data["name"].replace(" ", "_").lower()

            templatevars=dict(
                data=data,
                allData=self.data,
                name=name,
                cfg=self.configSet,
                nmg=self.namingSet
            )

            filename = filename.render(**templatevars)
            filename_nosuffix = os.path.splitext(os.path.basename(filename))[0]
            
            if hasattr(self, "preprocess_data_%s" % itemtype):
                data = getattr(self, "preprocess_data_%s" % itemtype)(templatetype,inputdata,filename)
                if data is None:
                    print("skip",templatetype,name)
                    continue
            
            content = template.render(
                filename_nosuffix=filename_nosuffix,
                filename=filename,
                **templatevars,
            )
            self.writeFile(filename, content)

    def load(self, filename):
        """load configuration from file

        Args:
            filename (str): XML file to load data from
        """
        self.currentFile = filename
        with open(filename) as fp:
            soup = bs(fp.read(), features="lxml-xml")
        self.data = self.parseData(soup.rte, noWrap=True)

    def preprocess_swcs(self, values):
        """preprocessor for SWC
        add signalpools
        add runnables contained in swc
        
        self.data ist die Struktur
        values ist alles in tag SWC
        
        deepcopy um eine lokale Kopie zu bekommen und die ursprünglichen Daten nicht manipuliert werden
        """
        values = deepcopy(values)
        sigpools = [list(x.values())[0] for x in self.data["signalpools"]]
        for swc in values:
            _, swc = list(swc.items())[0]
            swc["signalpools"] = sigpools
            swc["runnables"] = []
            for runnable in self.data["runnables"]:
                _, data = list(runnable.items())[0]

                component = data["component"]
                if swc["name"] == component:
                    swc["runnables"].append(list(runnable.values())[0])

        return values

    def preprocess_tasks(self, values):
        """preprocessor for Tasks
        add runnables contained in task
        add swcs handled by task
        update eventlist to include signobject triggers
        """
        values = deepcopy(values)
        runnables = deepcopy(self.data["runnables"])
        for task in values:
            _, task = list(task.items())[0]
            taskname = task["name"]
            eventlist = set(filter(None, task["events"].split("|")))
            eventlist |= self.findTaskTriggers(task)
            eventlist.add(task["tickEvent"])
            eventlist = [e for e in eventlist if not e in ["", "0"]]
            eventlist.sort()

            task["events"] = "|".join(eventlist)

            task["runnables"] = []
            task["swcs"] = []
            for runnable in runnables:
                _, runnable = list(runnable.items())[0]
                if runnable["task"] == taskname:
                    task["runnables"].append(runnable)
                    task["swcs"].append(runnable["component"])

        return values
    
    def preprocess_data_signalclass(self,templatetype,data,filename):
        """preprocess data for a single signalclass instance
        """
        fn,ext = os.path.splitext(filename)

        if not data["needsDefaultInDriver"] and not data["needsDefaultOutDriver"] and ext==".c" and templatetype=="signaltype":
            return
        return data

    def preprocess_signalclasses(self, values):
        values = deepcopy(values)
        signalobjects = self.preprocess_signalobjects(
            self.data["signalobjects"])
        for sigclass in values:
            _, sigclass = list(sigclass.items())[0]
            sigclass["needsDefaultInDriver"] = False
            sigclass["needsDefaultOutDriver"] = False
            for sigobj in signalobjects:
                _, sigobj = list(sigobj.items())[0]
                if sigobj["signalclass"] == sigclass["name"]:
                    if sigobj["indriver"] == "default":
                        sigclass["needsDefaultInDriver"] |= True
                    if sigobj["outdriver"] == "default":
                        sigclass["needsDefaultOutDriver"] |= True

        return values

    def preprocess_signalpools(self, values):
        """preprocessor for signalpools
        add signalobjects contained in pool
        """
        values = deepcopy(values)
        signalobjects = self.preprocess_signalobjects(
            self.data["signalobjects"])
        for signalpool in values:
            _, signalpool = list(signalpool.items())[0]
            signalname = signalpool["name"]
            signalpool["signalobjects"] = []
            for signalobject in signalobjects:
                _, signalobject = list(signalobject.items())[0]
                if signalobject["signalpool"] == signalname:
                    signalpool["signalobjects"].append(signalobject)

        return values

    def findTaskTriggers(self, task):
        """Find events from signalobjects, that need to trigger a task
        """
        eventlist = set()
        for runnable in self.data["runnables"]:
            _, runnable = list(runnable.items())[0]
            if runnable["task"] == task["name"]:
                eventlist |= set(runnable["events"].split("|"))

        return eventlist

    def findTasksForEvent(self, event):
        """find tasks that handle an event
        this includes error and update triggers from
        signalobjects that are inputs to this task

        Args:
            event (str): the event to check

        Raises:
            RuntimeError: if event is not handled by any tasks

        Yields:
            task: set of tasks handling the event
        """
        if event == "0" or not event:
            return
        found = False

        for task in self.data["tasks"]:
            _, task = list(task.items())[0]
            eventlist = set(filter(None, task["events"].split("|")))
            eventlist |= self.findTaskTriggers(task)
            eventlist = [e for e in eventlist if not e in ["", "0"]]

            if event in eventlist:
                yield task
                found = True
        if not found:
            raise RteGeneratorException("No task for Event %r" % event)

    def preprocess_signalobjects(self, values):
        """preprocessor for signalobjects
        add list of tasks that receive update and error events
        """
        values = deepcopy(values)
        for signalobject in values:
            _, signalobject = list(signalobject.items())[0]
            signalobject["updateTasks"] = set()
            signalobject["errorTasks"] = set()

            for taskUpd in self.findTasksForEvent(signalobject["onDataUpdate"]):
                signalobject["updateTasks"].add(taskUpd["name"])

            for taskErr in self.findTasksForEvent(signalobject["onDataError"]):
                signalobject["errorTasks"].add(taskErr["name"])
            signalobject["updateTasks"] = list(signalobject["updateTasks"])
            signalobject["errorTasks"] = list(signalobject["errorTasks"])

        return values

    def writeInfo(self, itemtype, values, template):
        """write section to info file

        Args:
            itemtype (str): type of item (e.h. signalclass)
            values (list): data
        """
        filedir = os.path.dirname(self.currentFile)
        templatePath = os.path.join(filedir, template, itemtype+".info")
        if not os.path.isfile(templatePath):
            return
        data = []
        for v in values:
            _, v = list(v.items())[0]
            data.append(v)
        with open(templatePath) as fp:
            template = self.env.from_string(fp.read())
            self.infoFP.write(template.render(values=data).strip()+"\n\n")

    def getPyModPath(self, pymod):
        """get python module directory
        """
        if pymod in sys.modules:
            return os.path.dirname(os.path.abspath(sys.modules[pymod].__file__))
        return ""

    def varSub(self, path):
        """replace {PROJECT_PATH}, {GUI_PATH} and {GEN_PATH}
        with appropriate absolute path
        """
        for var, value in [
            ("PROJECT_PATH", os.path.dirname(os.path.abspath(self.currentFile))),
            ("GUI_PATH", self.getPyModPath("RteGui")),
            ("GEN_PATH", self.getPyModPath("RteGen")),
        ]:
            path = path.replace("{%s}" % var, value)
        return path

    def generate(self, outdir=None, template=None):
        """generate the RTE project

        Args:
            outdir (str, optional): directory to put the files into. Defaults to directory specified in the config.

        Raises:
            RuntimeError: on malformed data
        """
        if outdir is None:
            outdir = self.varSub(self.configSet["path_out"])
        if template is None:
            template = self.varSub(self.configSet["templateDir"])

        self.env = jinja2.Environment(
            loader=jinja2.FileSystemLoader(template), autoescape=False)

        os.makedirs(outdir, exist_ok=True)
        self.infoFP = open(os.path.join(outdir, "info.txt"), "w")

        shutil.copy(template+"/rte.c", outdir)
        shutil.copy(template+"/rte.h", outdir)
        shutil.copy(template+"/rte_types.h", outdir)
        
        to_generate = list(self.data.items())
        to_generate.sort(key=lambda k: generate_order.index(k[0]))
        for obj, values in to_generate:
            templates = None

            print("generating", obj)
            #Hier werden die ganzen Preprozess Funktionen aufgerufen
            if hasattr(self, "preprocess_%s" % obj):
                values = getattr(self, "preprocess_%s" % obj)(values)

            for value in values:
                if len(value.items()) != 1:
                    raise RuntimeError("invalid data %r" % data)
                itemtype, data = list(value.items())[0]
                if templates is None:
                    templates = self.getTemplates(itemtype, outdir, template)

                self.generateObjects(itemtype, data, templates)
            if values:
                self.writeInfo(itemtype, values, template)

        self.infoFP.close()
