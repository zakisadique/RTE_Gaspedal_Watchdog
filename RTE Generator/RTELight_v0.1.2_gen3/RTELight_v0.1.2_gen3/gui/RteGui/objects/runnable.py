from .xmlObject import xmlObject
from .prefixedName import prefixedName
from . import prefixedName as prefixedName_
class runnable(xmlObject,prefixedName):
    update_fields_ = ["component"]
    shortname: {"type":str,"default":"My Runnable"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"Runnable"}
    component: {"type":"choice","value_from":"swc.name"}
    task: {"type":"choice","value_from":"task.name"}
    cycletime: {"type":int,"default":100,"suffix":" ms"}
    signalIN: {"type":"list|checkable","joiner":"|","value_from":"signalobject.name"}
    signalOUT: {"type":"list|checkable","joiner":"|","value_from":"signalobject.name"}
    events: {"type":"list|checkable","joiner":"|","value_from":"event.name"}
    
    @property
    def name(self):
        prefix = prefixedName_.prefixes.get(self.__class__.__name__,"")
        postfix = prefixedName_.postfixes.get(self.__class__.__name__,"")
        swcprefix = prefixedName_.prefixes.get("swc","")
        
        if not self.component:
            swcname=""
        else:
            swcname=self.component[len(swcprefix):].upper()+"_"
        return (prefix+swcname+self.shortname+postfix).replace(" ","_")