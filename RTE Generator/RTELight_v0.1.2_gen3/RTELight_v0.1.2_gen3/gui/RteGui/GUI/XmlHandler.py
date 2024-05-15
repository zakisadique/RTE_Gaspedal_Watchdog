from bs4 import BeautifulSoup as bs
import bs4
from .. import objects
import itertools

"""Mixin for MainWindow to handle load and save of XML files

"""
class XmlHandler():
    def __init__(self):
        self.config = None
        self.version = (0,0,0)
    
    def unpackAttr(self,value,attr):
        """unwrap nested attribute from object

        Args:
            value (any): the object of which to load the attribute 
            attr (str): atrtibute (e.g. 'rte.signalclasses')

        Returns:
            Any: the value of the attribute
        """
        for a in attr.split("."):
            value=getattr(value,a)
        return value


    def saveData(self,filename,tabWidget):
        """take the data from all tabs and put it onto an XML file
        
        Args:
            tabWidget (QTabWidget): MainWindow's tabWidget
        """
        soup=bs(features="lxml-xml")
        for key,wgt in tabWidget.items():
            tag=soup
            if wgt.datapath is None: # skip data that should not be stored
                continue
            for attr in wgt.datapath.split("."): # traverse datapath
                if not tag.find(attr): # if the tag doesn't exists create it
                    e=soup.new_tag(attr)
                    tag.append(e)
                    tag=e
                else: # otherwise use the existing tag
                    tag=tag.find(attr)
            
            if wgt.datapath.split(".")[-1] not in ["configset","naming"]: # if we're not dealing with a configset
                for item in wgt.getData(): 
                    e=soup.new_tag(getattr(item,"_objname",item.__class__.__name__)) #make a new tag
                    # add the attributes
                    if hasattr(item,"getstate"):
                        e.attrs=item.getstate() 
                    else:
                        e.attrs=item.__dict__
                    tag.append(e) #a append to parent

            else:
                basetag = tag
                config = wgt.getData()
                
                for k,v in itertools.chain(config.__dict__.items(),config.getExtra()): # for every field
                    if not k in config.__annotations__:
                        continue
                    path=config.__annotations__[k].get("datapath","")
                    name=config.__annotations__[k].get("name",k)
                    tag=basetag
                    if path:
                        for attr in path.split("."): # traverse datapath
                            if not tag.find(attr): # if the tag doesn't exists create it
                                e=soup.new_tag(attr)
                                tag.append(e)
                                tag=e
                            else: # otherwise use the existing tag
                                tag=tag.find(attr)

                    e=soup.new_tag("config") # create config tag
                    e.attrs={ # save name and values
                        "name":name,
                        "value":v
                    }
                    tag.append(e)

        with open(filename,"w") as fp:
            fp.write(soup.prettify())


    def cfg2dict(self,data):
        """load configuration from XML file (list of name,value pairs) and convert to dictionary

        Args:
            data (bs4 tree): the config or naming node in the tree

        Returns:
            dict: dictionary of names and values
        """
        config={}
        for item in data: # iterate all tags
            if type(item) is not bs4.element.Tag:
                continue
            if "name" in item.attrs:
                config[item.attrs["name"]]=item.attrs["value"] #save value into dict under name
            else:
                for k,v in self.cfg2dict(item).items(): # recurse subitems
                    config[item.name+"_"+k]=v
        return config

    def loadConfig(self,data,cfgtype,widget):
        """load config data into widget

        Args:
            data (bs4 tree): the config or naming node in the tree
            cfgtype (str): configset or naming
            widget (EditorWidget): widget to load the data into
        """
        config=self.cfg2dict(data)
        module=getattr(objects,cfgtype)
        klass=getattr(module,cfgtype)
        data = klass()
        
        for k,v in config.items():
            setattr(data,k,v)
        
        if cfgtype=="configset":
            self.config = data
            self.version = tuple(map(int,getattr(self.config,"loaded_guivers","0.0.0").split("."))) # convert version string to list of int


        widget.loadData(data)

    def loadTab(self,objtype,data,widget,events,swcs):
        """load data from xml-node into a tab

        Args:
            objtype (str): the type of the object (e.g. signalclass)
            data (bs4 tree): the xml-node (e.h. the `signalclasses` node)
            widget (DataEdit): the DataEdit to load the entries into
            events (set): event accumulator (not needed for version > 0.1.2)
            swcs (set): swc accummulator (not needed for version > 0.1.2)
        """
        if hasattr(widget,"clear"):
            widget.clear()
        if not data:
            return
        for item in data:
            if type(item) is not bs4.element.Tag:
                continue
            if not item.attrs:
                continue
            if not "shortname" in item.attrs and "name" in item.attrs:
                item.attrs["shortname"]=item.attrs["name"]
            
            if self.version < (0,1,2): # old versions extracted events and swcs from other data
                if objtype in ["task","runnable"]:
                    for evt in item.attrs["events"].split("|"):
                        events.add(evt)

                if objtype=="signalobject":
                    events.add(item.attrs["onDataUpdate"])
                    events.add(item.attrs["onDataError"])

                if objtype=="runnable":
                    swcs.add(item.attrs["component"])
            
            classInstance = widget.objtype() # create object
            for k,v in item.attrs.items():
                setattr(classInstance,k,v) # save fields
            widget.addItem(classInstance) # add to list widget
        

    def loadData(self,filename,tabWidget):
        """load data from xml file and insert into tabs

        Args:
            filename (str): name of the file to load
            tabWidget (QTabWidget): MainWindow's tabWidget
        """
        with open(filename) as fp:
            soup = bs(fp.read(),features="lxml-xml")
        events = set()
        swcs = set()
        for key,wgt in tabWidget.items():
            if wgt.datapath is not None:
                data = self.unpackAttr(soup,wgt.datapath)
                if data is None:
                    continue
                if wgt.datapath.split(".")[-1] in ["configset","naming"]: # if we're dealing with a configset
                    self.loadConfig(data,wgt.datapath.split(".")[-1],wgt) # load config
                else:                                          # otherwise
                    self.loadTab(key,data,wgt,events,swcs) # load tab data
        
        if self.version < (0,1,2):
            widget=tabWidget["event"]
            widget.clear()
            for event in events:
                if event=="0" or not event: # skip empty events
                    continue
                evt = widget.objtype()
                # cut off prefix
                evt.shortname=event[len(objects.prefixedName.prefixes["event"]):]
                widget.addItem(evt)
            

            widget=tabWidget["swc"]
            widget.clear()
            for component in swcs:
                if component=="0" or not component: # skip empty components
                    continue
                swc = widget.objtype()
                # cut off prefix
                swc.shortname=component[len(objects.prefixedName.prefixes["swc"]):]
                widget.addItem(swc)
            
                    
