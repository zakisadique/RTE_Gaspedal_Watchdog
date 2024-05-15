from .xmlObject import xmlObject
from .prefixedName import prefixedName

class swc(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My SWC"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"Software component"}
    