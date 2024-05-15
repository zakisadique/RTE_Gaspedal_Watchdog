from PySide2 import QtWidgets
from .xmlObject import xmlObject
from .prefixedName import prefixedName
from .event import event
from .resource import resource
class signalobject(xmlObject,prefixedName):
    shortname: {"type":str,"default":"My Signalobject"}
    name: {"type":str,"readonly":True}
    description: {"type":str,"default":"A Signal"}
    signalclass: {"type":"choice","value_from":"signalclass.name"}
    indriver: {"type":"choice|editable","values":["0", "default"],"default":"default"}
    outdriver: {"type":"choice|editable","values":["0", "default"],"default":"default"}
    signalpool: {"type":"choice","value_from":"signalpool.name"}
    resource: {"type":"choice","value_from":"resource.name","values":["None"]}
    resourceDefault: {"type":"button","action":"resourceDefault|reload","label":"New resource","readonly":True}
    onDataUpdate: {"type":"choice","values":["0"],"value_from":"event.name"}
    onDataUpdateDefault: {"type":"button","action":"onDataUpdateDefault|reload","label":"New event","readonly":True}
    onDataError: {"type":"choice","values":["0"],"value_from":"event.name"}
    onDataErrorDefault: {"type":"button","action":"onDataErrorDefault|reload","label":"New event","readonly":True}

    def onDataUpdateDefault(self):
        evtname=self.shortname.replace(" ","_").lower()+"_onData"
        evt = event()
        evt.shortname = evtname
        QtWidgets.qApp.MainWindow.tabWidgets["event"].addItem(evt)
        self.onDataUpdate = evt.name
        return

    def onDataErrorDefault(self):
        evtname=self.shortname.replace(" ","_").lower()+"_onError"
        evt = event()
        evt.shortname = evtname
        QtWidgets.qApp.MainWindow.tabWidgets["event"].addItem(evt)
        self.onDataError = evt.name
        return

    def resourceDefault(self):
        resname=self.shortname.replace(" ","_").lower()+"_Lock"
        res = resource()
        res.shortname = resname
        QtWidgets.qApp.MainWindow.tabWidgets["resource"].addItem(res)
        self.resource = res.name
        return
