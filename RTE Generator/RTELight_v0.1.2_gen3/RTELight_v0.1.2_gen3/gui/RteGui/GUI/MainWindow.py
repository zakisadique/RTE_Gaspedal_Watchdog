import configparser
from socket import gethostname
from PySide2.QtWebEngineWidgets import QWebEngineView
from .UIBase.MainWindow import Ui_MainWindow
from .DataEdit import DataEdit
from .EditorWidget import EditorWidget
from .XmlHandler import XmlHandler
from PySide2 import QtWidgets, QtGui, QtCore
# from ..objects.cyclic_runnable import cyclic_runnable
# from ..objects.event_runnable import event_runnable
from ..objects.event import event
from ..objects.resource import resource
from ..objects.task import task
from ..objects.signalclass import signalclass
from ..objects.signalobject import signalobject
from ..objects.configset import configset, current_version
from ..objects.naming import naming
from ..objects.signalpool import signalpool
from ..objects.runnable import runnable
from ..objects.swc import swc
from functools import partial
import traceback
import os,sys

"""Path for machine-specific config
"""
configfile=gethostname()+".ini"
configdir=os.path.dirname(os.path.abspath(__file__))
configdir=os.path.abspath(os.path.join(configdir,".."))
configfile=os.path.abspath(os.path.join(configdir,"..",configfile))



"""MainWindow of the application
tabs can be configured in the `tabs` list
editors in the tabs are generated from the objtype __annotations__
data is loaded and saved to the xml-path specified in `datapath`
"""

tabs=(
    {"title":"Configuration","objtype":configset,"mode":"editor","datapath":"rte.configset"},
    {"title":"Naming conventions","objtype":naming,"mode":"editor","datapath":"rte.naming"},
    {"title":"Signalpools","objname":"Signalpool","objtype":signalpool,"datapath":"rte.signalpools"},
    {"title":"Tasks","objname":"Task","objtype":task,"datapath":"rte.tasks"},
    {"title":"Signal classes","objname":"Signal class","objtype":signalclass,"datapath":"rte.signalclasses"},
    {"title":"Signal objects","objname":"Signal object","objtype":signalobject,"datapath":"rte.signalobjects"},
    {"title":"SWCs","objname":"SWC","objtype":swc,"datapath":"rte.swcs"},
    {"title":"Runnables","objname":"Runnable","objtype":runnable,"datapath":"rte.runnables"},
    {"title":"Events","objname":"Event","objtype":event,"datapath":"rte.events"},
    {"title":"Resources","objname":"Resource","objtype":resource,"datapath":"rte.resources"},
    # {"title":"Cyclic runnable","objname":"Cyclic runnable","objtype":cyclic_runnable,"datapath":"rte.runnables.cyclic"},
    # {"title":"Event runnable","objname":"Event runnable","objtype":event_runnable,"datapath":"rte.runnables.event"},
)

def msgBoxException(exctype,value,tback):
    from PySide2 import QtWidgets
    msgBox = QtWidgets.QMessageBox()
    msgBox.setWindowTitle("Exception!")
    msgBox.setText("".join(traceback.format_exception(exctype,value,tback)))
    msgBox.exec_()

sys.excepthook = msgBoxException

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow,XmlHandler):
    def __init__(self, *a, **kwa):
        """Initialize the mainwindow, create the tabs with correspondind DataEdit (List+Editor combo) widgets
        connect update signals between the tabs (for e.g. update of names)
        the `updateInputs` attribute of the tab is derived from the value_from fields
        """
        QtWidgets.QMainWindow.__init__(self, *a, **kwa)
        Ui_MainWindow.__init__(self)
        Ui_MainWindow.setupUi(self, self)

        self.winTitle=self.windowTitle()
        self.currentFile=None
        self.rteGenPath=None

        self.actionOpenFile.triggered.connect(self.openFile)
        self.actionSaveFile.triggered.connect(self.saveFile)
        self.actionSaveGenerate.triggered.connect(self.saveGenerate)
        self.actionHelp.triggered.connect(self.showHelp)
        self.actionAbout.triggered.connect(self.showAbout)
        self.actionSaveAs.triggered.connect(self.saveAs)
        self.prevTab = 0
        self.tabWidget.currentChanged.connect(self.changeTab)

        self.tabWidgets = {}

        for tabdata in tabs:
            objname = tabdata["objtype"].__name__
            if tabdata.get("mode","list")=="list":
                widget = DataEdit(self)
                widget.setObject(tabdata["objtype"],tabdata["objname"])
            else:
                widget=QtWidgets.QWidget(self)
                editor = EditorWidget(tabdata["objtype"])
                editor.setupUi(widget)
                widget.updateInputs=[]
                widget.getData=editor.getData
                widget.loadData=editor.loadData
                widget.saveData=editor.saveData
                if objname=="naming":
                    widget.notifyUpdate=self.namingUpdate
                else:
                    widget.notifyUpdate=editor.notifyUpdate
                widget.setEnabled(True)

            self.tabWidget.addTab(widget,tabdata["title"])
            self.tabWidgets[objname]=widget
            widget.datapath = tabdata["datapath"]
            widget.objtype = tabdata["objtype"]

        for key,wgt in self.tabWidgets.items():
            for update in wgt.updateInputs:
                updType = update.split(".")[0]
                self.tabWidgets[updType].data_list.entriesUpdated.connect(partial(wgt.updateData,update,wgt))

        self.updateMenu()

    def showHelp(self):
        """show help window
        """
        print("palim")
        dlg = QtWidgets.QMainWindow(self)
        WebView = QWebEngineView(dlg)
        url = QtCore.QUrl.fromUserInput(os.path.join(configdir,"help","index.html"))
        WebView.load(url)
        dlg.setCentralWidget(WebView)
        dlg.setAttribute(QtCore.Qt.WA_DeleteOnClose, True)
        dlg.show()
        return

    def showAbout(self):
        """show about window
        """
        msgBox = QtWidgets.QMessageBox()
        msgBox.setWindowTitle("About")
        msgBox.setText("RTEGen Light\n"
        "Version %s" % current_version)
        msgBox.exec_()
        return

    def namingUpdate(self):
        """trigge update of all other widgets if `naming` tab was updated
        """
        if "naming" in self.tabWidgets:
            data=self.tabWidgets["naming"].getData()
            data.updateData()
            for widget in self.tabWidgets.values():
                if isinstance(widget,DataEdit):
                    widget.updateEntries()
            

    def changeTab(self,new):
        """save data in current tab on change
        """
        prev = self.prevTab
        self.tabWidget.widget(prev).notifyUpdate()
        self.prevTab = new

    def updateMenu(self):
        """update the state of the main menu if a file is loaded or saved
        """
        self.actionOpenFile.setEnabled(True)
        self.actionSaveFile.setEnabled(self.currentFile is not None)
        self.actionSaveGenerate.setEnabled(self.currentFile is not None)
        self.actionSaveGenerate.setEnabled(self.currentFile is not None)
        self.actionSaveAs.setEnabled(True)
        if self.currentFile:
            self.setWindowTitle("%s - %s"%(self.winTitle,os.path.basename(self.currentFile)))
        else:
            self.setWindowTitle(self.winTitle)


    def loadPCconfig(self):
        """load machine-specific config
        """

        if not os.path.isfile(configfile):
            return
        config = configparser.ConfigParser()
        with open(configfile) as fp:
            config.read_file(fp)
        
        self.rteGenPath = config["RteGen"]["path"]
        sys.path.append(self.rteGenPath)

    def savePCconfig(self):
        """save machine-specific config
        """

        config = configparser.ConfigParser()
        config["RteGen"]={
            "path":self.rteGenPath
        }
        with open(configfile,"w") as fp:
            config.write(fp)


    def saveGenerate(self):
        """search for the RTE generator and call it
        """
        self.saveFile()
        self.loadPCconfig()
        RTEgen = None
        try:
            from RteGen.RTEgen import RTEgen, RteGeneratorException
        except ImportError:
            QtWidgets.QMessageBox.information(self,"RteGen not found","The RteGen python Module was not found, please specify the installation directory.")
            if self.rteGenPath is not None:
                if self.rteGenPath in sys.path:
                    sys.path.remove(self.rteGenPath)
            filename = QtWidgets.QFileDialog.getOpenFileName(
            self,
            "Load RteGen",
            ".",
            "Python module (__init__.py)"
        )[0]
            if not filename:
                return
            self.rteGenPath = os.path.dirname(filename)
            self.rteGenPath = os.path.dirname(self.rteGenPath)
            sys.path.append(self.rteGenPath)
            self.savePCconfig()
            
        if RTEgen is None:
            return
        try:
            generator = RTEgen()
            generator.load(self.currentFile)
            generator.generate()
        except RteGeneratorException as e:
            msgBox = QtWidgets.QMessageBox()
            msgBox.setWindowTitle("Error!")
            msgBox.setText(e.args[0])
            msgBox.exec_()
            
            

    def saveFile(self):
        """save data to a XML file
        """
        self.changeTab(self.tabWidget.currentIndex())
        self.updateMenu()
        XmlHandler.saveData(self,self.currentFile,self.tabWidgets)

    def saveAs(self):
        """save data to a XML file under a new name
        """
        filename = QtWidgets.QFileDialog.getSaveFileName(
            self,
            "Save File",
            ".",
            "XML (*.xml)"
        )[0]

        if not filename:
            return

        self.currentFile=os.path.abspath(filename)
        self.saveFile()

    def loadFile(self,filename):
        """load data from a XML file
        """
        if filename is None:
            return
        self.currentFile=os.path.abspath(filename)
        self.updateMenu()
        XmlHandler.loadData(self,self.currentFile,self.tabWidgets)


    def openFile(self):
        """open and load an existing XML file
        """
        filename = QtWidgets.QFileDialog.getOpenFileName(
            self,
            "Load File",
            ".",
            "XML (*.xml)"
        )[0]

        if not filename:
            return

        self.loadFile(filename)

        