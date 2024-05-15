from .UIBase.DataEdit import Ui_DataEdit
from PySide2 import QtWidgets,QtGui,QtCore
from .EditorWidget import EditorWidget
from .WidgetHelper import setWidgetValue
from functools import partial
"""List / Editor combo widget
"""
class DataEdit(QtWidgets.QWidget,Ui_DataEdit):
    def __init__(self,*a,**kwa):
        QtWidgets.QWidget.__init__(self,*a,**kwa)
        Ui_DataEdit.__init__(self)
        Ui_DataEdit.setupUi(self,self)
        self.editorWidget = None
        self.updateInputs=set()

    def notifyUpdate(self):
        self.data_list.entriesUpdated.emit(self.getData())

    def getData(self):
        """save current item then return all data in the list
        """
        node = self.data_list.treeWidget.currentItem()
        if node is not None:
            node.item = self.editorWidget.getData()
        return self.data_list.getData()

    def clear(self):
        """clear the list
        """
        self.data_list.clear()

    def addItem(self,item):
        """add item an to the list
        """
        self.data_list.addItem(item)

    def updateData(self,updType,widget,data):
        """update fields in the editor that rely on data from other tabs
        """
        self.editorWidget.updateData(updType,data)

    def setObject(self,objtype,objname):
        """set the object type handled by this tab
        create the appropriate editor widget and load it into location
        connect name update from editor to list to update name of current item

        Args:
            objtype (type): class of the object
            objname (str): name of the object
        """
        self.objtype=objtype
        self.data_list.newBtn.setText(self.data_list.newBtn.text().format(objname=objname))
        self.editorWidget = EditorWidget(objtype)
        self.editorWidget.setupUi(self.editor)
        self.data_list.setEditor(self.editorWidget)
        self.update_fields=["name","shortname"]
        if hasattr(objtype,"update_fields_"):
            self.update_fields+=objtype.update_fields_
        for f in self.update_fields: # for all fields that should trigger updateds
            if not "readonly" in objtype.__annotations__[f]: #check if field is readonly
                wgt = self.editorWidget.attrWidgets[f]
                if type(wgt) is QtWidgets.QLineEdit:
                    wgt.textChanged.connect(partial(self.updateCurrentItem,f))
                elif type(wgt) is QtWidgets.QComboBox:
                    wgt.currentIndexChanged.connect(partial(self.updateCurrentItem,f))
                else:
                    raise RuntimeError("Unknown Widget %r"%wgt)


        #collect all fields that should receive updates from other widgets
        for attrib,info in objtype.__annotations__.items():
            if "value_from" in info:
                self.updateInputs.add(info["value_from"])

    def updateEntries(self):
        """reload editor data
        update all names in the list
        triggert when a prefix or suffix is changed
        """
        item = self.editorWidget.getData()
        self.editorWidget.loadData(item)
        self.data_list.updateList()

    def updateCurrentItem(self,attr,text):
        """update all fields in `update_fields` of the currently opened item in the editor
        and reload its name in the list

        triggered on name change (e.g. `name` is reloaded if `shortname` is edited)
        """
        node = self.data_list.treeWidget.currentItem()
        item = self.editorWidget.getData()
        if node is not None:
            node.setText(0,item.name)
        for f in self.update_fields:
            if f==attr:
                continue
            wgt=self.editorWidget.attrWidgets[f]
            value = getattr(item,f)
            setWidgetValue(wgt,value)
        