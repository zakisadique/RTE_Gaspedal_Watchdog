from .xmlObject import xmlObject
from . import prefixedName as mPrefixedName
from .prefixedName import prefixedName
class signalpool(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Signalpool"}
    name: {"type":str,"readonly":True}
    description: {"type":str}
    startaddr: {"type":"choice|editable","values":["default"]}
    getDefaultStart: {"type":"button","action":"getDefaultStart|reload","label":"get default value","readonly":True}
    endaddr: {"type":"choice|editable","values":["default"]}
    getDefaultEnd: {"type":"button","action":"getDefaultEnd|reload","label":"get default value","readonly":True}

    
    def getDefaultStart(self):
        self.startaddr = (mPrefixedName.prefixes["addr"]+self.name+mPrefixedName.postfixes["addrStart"]).replace(" ","_").upper()
    
    def getDefaultEnd(self):
        self.endaddr = (mPrefixedName.prefixes["addr"]+self.name+mPrefixedName.postfixes["addrEnd"]).replace(" ","_").upper()