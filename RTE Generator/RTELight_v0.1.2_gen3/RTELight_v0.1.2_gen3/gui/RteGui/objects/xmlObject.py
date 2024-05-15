class xmlObject():
    """helper function for objects
    loads default for fields on init
    if not default is specified initialise field with default of correct type
    on write convert data to correct type and prevent write to readonly fields
    """
    def __init__(self):
        for attr,info in self.__annotations__.items():
            if info.get("readonly",False) and not info.get("doWrite",False):
                continue
            if "default" in info:
                value = info["default"]
            else:
                value = info["type"]
                if type(value) is not type:
                    value = type(value)
                value = value()
            if not hasattr(self,attr):
                setattr(self,attr,value)
        
    def __setattr__(self,attr,value):
        if attr in self.__annotations__:
            info=self.__annotations__[attr]
            if info.get("readonly",False) and not info.get("doWrite",False):
                return
            tp=info["type"]
            if not "valuemap" in info:
                if type(tp) is type:
                    value = tp(value)
        
        return object.__setattr__(self,attr,value)