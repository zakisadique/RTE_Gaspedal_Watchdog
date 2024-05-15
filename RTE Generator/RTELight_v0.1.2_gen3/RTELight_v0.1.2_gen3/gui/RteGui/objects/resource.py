from .xmlObject import xmlObject
from .prefixedName import prefixedName

class resource(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Resource"}
    name: {"type":str,"readonly":True}
    restype: {"type":"choice","values":["semaphore"]}
    description: {"type":str,"default":"A Resource"}
    