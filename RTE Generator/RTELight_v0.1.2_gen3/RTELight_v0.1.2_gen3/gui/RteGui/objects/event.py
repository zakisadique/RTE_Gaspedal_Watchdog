from .xmlObject import xmlObject
from .prefixedName import prefixedName
class event(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Event"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"A Event"}
    