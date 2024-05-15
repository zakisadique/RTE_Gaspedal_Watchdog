from .UIBase.ListWidget import Ui_ListWidget
from PySide2 import QtWidgets,QtGui,QtCore


class ListWidget(QtWidgets.QWidget,Ui_ListWidget):
    """ListWidged to display a list of items
    displayed text is derived from the `name` field of the item in the list
    """
    entriesUpdated = QtCore.Signal(object)
    def __init__(self,*a,**kwa):
        QtWidgets.QWidget.__init__(self,*a,**kwa)
        Ui_ListWidget.__init__(self)
        Ui_ListWidget.setupUi(self,self)
        self.editor = None
        self.treeWidget.currentItemChanged.connect(self.itemChanged)
        self.newBtn.pressed.connect(self.addItem)
        self.installEventFilter(self)

    def clear(self):
        """clear the list
        """
        self.treeWidget.clear()

    def eventFilter(self,obj,event):
        """handle keypress events of the `delete` button
        """
        if event.type() == QtCore.QEvent.KeyPress:
            if event.key() == QtCore.Qt.Key_Delete:
                node=self.treeWidget.currentItem()
                if node:
                    self.treeWidget.invisibleRootItem().removeChild(node)
                    self.notifyUpdate()
        return True

    def updateList(self):
        """reload all names in the list
        """
        root = self.treeWidget.invisibleRootItem()
        for idx in range(root.childCount()):
            node=root.child(idx)
            node.setText(0,node.item.name)

    def notifyUpdate(self):
        """notify other widgets that the data in the list has been updated
        e.g. inform other tabs of new signalclasses
        """
        self.entriesUpdated.emit(self.getData())

    def addItem(self,item=None):
        """add item to the list
        if item is None, a new item of the dataclass of the editor is creates
        """
        if item is None:
            item = self.editor.dataclass()
        node = QtWidgets.QTreeWidgetItem([item.name])
        node.item = item
        self.treeWidget.addTopLevelItem(node)

        self.notifyUpdate()

    def itemChanged(self,current,prev):
        """Qt Slot, triggered if the current selection is changed
        save old item, load new item
        """
        if prev is not None:
            prev.item=self.editor.saveData()
            self.notifyUpdate()
        self.editor.setEnabled(current is not None)
        if current is None:
            return
        self.editor.loadData(current.item)

    def setEditor(self,editor):
        """set the editor linked to this list widget
        """
        self.editor = editor

    def getData(self):
        """return a list of the data of all items in the list
        """
        result = []
        node = self.treeWidget.invisibleRootItem()
        for c in range(node.childCount()):
            result.append(node.child(c).item)
        return result