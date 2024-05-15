from .xmlObject import xmlObject
from . import prefixedName


current_version = "0.1.2"

class configset(xmlObject):
    version: {"type":str,"default":"Erika 2"}
    guivers: {"type":str,"readonly":True,"doWrite":True}
    _info: {"readonly":True,"type":"label","text":"supported variables for paths: {PROJECT_PATH}: directory of XML file\n{GUI_PATH}: root path of RteGui {GEN_PATH}:root path of RteGen"}
    path_out: {"type":str,"default":"{PROJECT_PATH}\out","label":"output path\nrelative to current path"}
    templateDir: {"type":str,"default":r"{GEN_PATH}\..\templates","label":"directory w. template files,\npath relative to current path"}
    userCodeStart: {"type":str,"default":r"/\* USER CODE START {TAG} \*/"}
    userCodeEnd: {"type":str,"default":r"/\* USER CODE END {TAG} \*/"}

    def __init__(self):
        xmlObject.__init__(self)
        self.loaded_guivers = "0.0.0"

    @property
    def guivers(self):
        return current_version

    @guivers.setter
    def guivers(self,value):
        self.loaded_guivers = value

    def getExtra(self):
        return [("guivers",self.guivers)]