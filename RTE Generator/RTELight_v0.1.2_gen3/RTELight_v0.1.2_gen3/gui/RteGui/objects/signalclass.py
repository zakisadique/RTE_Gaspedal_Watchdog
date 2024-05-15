from .xmlObject import xmlObject
from .prefixedName import prefixedName

class signalclass(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Signalclass"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"Signalclass"}