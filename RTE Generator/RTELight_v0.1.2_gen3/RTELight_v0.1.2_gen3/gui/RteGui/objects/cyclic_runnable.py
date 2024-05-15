from .xmlObject import xmlObject
class cyclic_runnable(xmlObject):
    _objname="runnable"
    name: {"type":str,"default":"My Runnable"}
    component: {"type":str,"default":"SWC_Task"}
    cycletime: {"type":int,"default":100}
