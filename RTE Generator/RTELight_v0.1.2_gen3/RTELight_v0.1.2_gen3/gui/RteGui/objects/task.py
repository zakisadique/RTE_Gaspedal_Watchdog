from .xmlObject import xmlObject
from .prefixedName import prefixedName
class task(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Task"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"Task doing work"}
    timertickperiod: {"type":int,"default":1,"suffix":" ms"}
    tickEvent: {"type":"choice","value_from":"event.name","values":["0"]}
    mode: {"type":"choice","values":["Event","Cyclic","Cyclic and Event","System"]}
    signalpoolsRO: {"type":"list|checkable","joiner":"|","value_from":"signalpool.name"}
    signalpoolsRW: {"type":"list|checkable","joiner":"|","value_from":"signalpool.name"}
    events: {"type":"list|checkable","joiner":"|","value_from":"event.name"}