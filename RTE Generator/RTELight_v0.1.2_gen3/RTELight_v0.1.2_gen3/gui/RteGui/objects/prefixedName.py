prefixes={}
postfixes={}

class prefixedName():
    """Helper class to add name property with prefix and suffix for specific object type
    `prefixes` and `postfixes` will be set externally on config load

    """
    @property
    def name(self):
        
        prefix = prefixes.get(self.__class__.__name__,"")
        postfix = postfixes.get(self.__class__.__name__,"")
        return (prefix+self.shortname+postfix).replace(" ","_")

    def getstate(self):
        """get attributes to write into XML file
        the `update_fields_` of the object is used to add fields that are not part of the internal __dict__
        """
        data=dict(self.__dict__)
        if hasattr(self,"update_fields_"):
            for k in self.update_fields_:
                data[k]=getattr(self,k)
        data["name"]=self.name
        return data