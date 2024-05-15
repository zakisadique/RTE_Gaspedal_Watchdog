from PySide2 import QtWidgets,QtGui,QtCore
from .WidgetHelper import widgetFromInfo,setWidgetValue,getWidgetValue
from collections import defaultdict


"""

"""
class EditorWidget():
    def __init__(self,dataclass):
        self.dataclass = dataclass

    def setEnabled(self,enabled):
        self.widget.setEnabled(enabled)

    def notifyUpdate(self):
        return

    def updateData(self,updType,data):
        """triggerd when another tab has new data
        update the corresponding widgets in this editor
        """
        for wgt in self.updateWidget[updType]: # check all widgets that should receive updates of this type
            if isinstance(wgt, QtWidgets.QComboBox): #QCombobox
                wdata = wgt.currentData() # save old data
                idx = wgt.currentIndex()
                wgt.clear()
                if "values" in wgt.info: # add static values
                    for value in wgt.info["values"]:
                        wgt.addItem(value,value)
                for entry in data: # add values from data
                    value = entry
                    for attr in updType.split(".")[1:]: # unwrap nestes attr
                        value=getattr(value,attr)
                    wgt.addItem(value,value)
                dataidx = wgt.findData(wdata,flags=QtCore.Qt.MatchFixedString) # find old data
                if dataidx!=-1:
                    idx=dataidx
                wgt.setCurrentIndex(idx) # reload old data

            if isinstance(wgt, QtWidgets.QTreeWidget): #TreeWidget
                wgtvalue = getWidgetValue(wgt) #save old data
                wgt.clear()
                for entry in data:
                    value = entry
                    for attr in updType.split(".")[1:]: # unwrap nestes attr
                        value=getattr(value,attr)
                    node = QtWidgets.QTreeWidgetItem([value])
                    if wgt.checkable:
                        node.setFlags(node.flags() | QtCore.Qt.ItemIsUserCheckable
                                | QtCore.Qt.ItemIsTristate) # make node checkable
                        node.setCheckState(0, QtCore.Qt.Unchecked)
                    wgt.addTopLevelItem(node) # add node

                setWidgetValue(wgt,wgtvalue) # reload old data

    def setupUi(self,widget):
        """create a list of widgets and labels from the
        __annotations__ of the dataclass
        """
        self.widget=widget
        self.widget.setEnabled(False)
        self.attrWidgets = {}
        self.updateWidget = defaultdict(list)
        self.layout = QtWidgets.QGridLayout(self.widget)

        for line,(attrib,info) in enumerate(self.dataclass.__annotations__.items()): #for every data field of the dataclass
            attrWidget = widgetFromInfo(info,self) #get a corresponding editor widget
            attrWidget.info=info #save info into the widget
            self.attrWidgets[attrib] = attrWidget # save widget in attr->widget dict
            if "value_from" in info and info["type"].split("|")[0] in ["choice","list"]: # if widget should receive updates, save it
                srcdata = info["value_from"]
                self.updateWidget[srcdata].append(attrWidget) 
            label = QtWidgets.QLabel(info.get("label",attrib)) #make a label for the widget
            if info["type"]=="button":
                label.setText("")
            if attrib.startswith("_"):
                label.setText("")
            self.layout.addWidget(label,line,0) # add label
            self.layout.addWidget(attrWidget,line,1) # add widget

        spacer = QtWidgets.QSpacerItem(20,20,QtWidgets.QSizePolicy.Minimum,
                                      QtWidgets.QSizePolicy.Expanding)
        self.layout.addItem(spacer,line+1,0) # add a spacer in the end to keep widgets together

    
    def action(self,action):
        """trigger button action(s) of the dataclass instance
        """
        data=self.saveData()
        for action in action.split("|"): # for every action in list
            if action=="reload":
                self.loadData(data)
            else:
                func=getattr(data,action) # get action method from dataclass
                func() # run it

    def loadData(self,data):
        """load data into the editor
        """
        for attr,widget in self.attrWidgets.items():
            if attr.startswith("_"):
                continue
            value = getattr(data,attr)
            setWidgetValue(widget,value)
    
    def saveData(self):
        """get data from the editor
        create a new dataclass instance, then populate all attributes
        """
        klass = self.dataclass()
        for attr,widget in self.attrWidgets.items():
            if attr.startswith("_"):
                continue
            value = getWidgetValue(widget)
            setattr(klass,attr,value)

        return klass

    def getData(self):
        """alias for saveData to be compatible to ListWidget
        """
        return self.saveData()