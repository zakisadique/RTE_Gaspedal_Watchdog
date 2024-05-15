from .xmlObject import xmlObject
from . import prefixedName
class naming(xmlObject):
    signalpoolPrefix: {"type":str,"default":"sp_"}
    signalpoolPostfix: {"type":str,"default":""}

    taskPrefix: {"type":str,"default":"tsk_"}
    taskPostfix: {"type":str,"default":""}

    signalclassPrefix: {"type":str,"default":"sc_"}
    signalclassPostfix: {"type":str,"default":""}

    signalobjectPrefix: {"type":str,"default":"so_"}
    signalobjectPostfix: {"type":str,"default":""}

    swcPrefix: {"type":str,"default":"swc_"}
    swcPostfix: {"type":str,"default":""}

    runnablePrefix: {"type":str,"default":""}
    runnablePostfix: {"type":str,"default":"_run"}

    eventPrefix: {"type":str,"default":"ev_"}
    eventPostfix: {"type":str,"default":""}

    resourcePrefix: {"type":str,"default":"res_"}
    resourcePostfix: {"type":str,"default":""}

    addrPrefix: {"type":str,"default":"ADR_"}
    addrStartPostfix: {"type":str,"default":"_START"}
    addrEndPostfix: {"type":str,"default":"_END"}

    def updateData(self):
        for k in self.__dict__:
            self.updateKey(k)
    
    def updateKey(self,k):
        if k.endswith("Prefix"):
            obj=k.replace("Prefix","")
            prefixedName.prefixes[obj]=getattr(self,k,"")
        
        if k.endswith("Postfix"):
            obj=k.replace("Postfix","")
            prefixedName.postfixes[obj]=getattr(self,k,"")

    def __init__(self):
        xmlObject.__init__(self)
        self.updateData()
    
    def __setattr__(self,attr,value):
        xmlObject.__setattr__(self,attr,value)
        self.updateKey(attr)

    def getExtra(self):
        return []
