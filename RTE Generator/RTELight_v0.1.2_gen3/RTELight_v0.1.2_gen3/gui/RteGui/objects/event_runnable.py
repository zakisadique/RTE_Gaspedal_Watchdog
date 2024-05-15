from .xmlObject import xmlObject
class event_runnable(xmlObject):
    _objname="runnable"
    name: {"type":str,"default":"My Runnable"}
    component: {"type":str,"default":"SWC_Task"}
    event: {"type":"choice","value_from":"event.name"}