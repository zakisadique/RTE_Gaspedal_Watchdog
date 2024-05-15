from PySide2 import QtWidgets,QtGui,QtCore
from functools import partial

def widgetFromInfo(info,editor):
    if info["type"] is bool:
        widget = QtWidgets.QCheckBox()

    if info["type"] is str:
        widget = QtWidgets.QLineEdit()
        if "readonly" in info:
            widget.setReadOnly(True)

    if info["type"] is int:
        widget = QtWidgets.QSpinBox()
        widget.setMaximum(2**16-1)
        if "prefix" in info:
            widget.setPrefix(info["prefix"])
        if "suffix" in info:
            widget.setSuffix(info["suffix"])
        if "base" in info:
            widget.setDisplayIntegerBase(info["base"])

    if info["type"] is float:
        widget = QtWidgets.QDoubleSpinBox()
        widget.setMaximum(2**16-1)
    
    if type(info["type"]) is str:
        if info["type"].split("|")[0] == "button":
            widget = QtWidgets.QPushButton()
            widget.setText(info["label"])
            widget.clicked.connect(partial(editor.action,info["action"]))
        if info["type"].split("|")[0] == "label":
            widget = QtWidgets.QLabel()
            widget.setText(info["text"])
            

        if info["type"].split("|")[0] == "list":
            widget = QtWidgets.QTreeWidget()
            widget.checkable=False
            if "checkable" in info["type"].split("|"):
                widget.checkable=True
            
            widget.setAlternatingRowColors(True)
            widget.setIndentation(0)
            widget.setHeaderHidden(True)

        if info["type"].split("|")[0] == "choice":
            widget = QtWidgets.QComboBox()

            if "editable" in info["type"].split("|"):
                widget.setEditable(True)
            if "values" in info:
                for value in info["values"]:
                    widget.addItem(value,value)
    
    if "valuemap" in info:
        def setData(data):
            for key,value in info["valuemap"].items():
                if value==data:
                    setWidgetValue(widget,key,noSetData=True)
                    return
        
        def getData():
            data = getWidgetValue(widget,noGetData=True)
            return info["valuemap"][data]
        
        widget.setData=setData
        widget.getData=getData

    if "default" in info:
        setWidgetValue(widget,info["default"])

    return widget


def setWidgetValue(widget, value,noSetData=False):
    if hasattr(widget, "setData") and not noSetData:
        return widget.setData(value)

    if isinstance(widget, QtWidgets.QLineEdit):
        return widget.setText(value)

    if isinstance(widget, QtWidgets.QPushButton):
        return

    if isinstance(widget, (QtWidgets.QDoubleSpinBox, QtWidgets.QSpinBox)):
        return widget.setValue(value)

    if isinstance(widget, QtWidgets.QCheckBox):
        return widget.setChecked(value)

    if isinstance(widget, QtWidgets.QPlainTextEdit):
        return widget.setPlainText(value)

    if isinstance(widget, QtWidgets.QTextEdit):
        return widget.setHtml(value)

    if isinstance(widget, QtWidgets.QDateTimeEdit):
        return widget.setDateTime(value)

    if isinstance(widget, QtWidgets.QDateEdit):
        return widget.setDate(value)

    if isinstance(widget, QtWidgets.QDateTimeEdit):
        return widget.setTime(value)

    if isinstance(widget, QtWidgets.QTreeWidget):
        jnr=widget.info["joiner"]
        values = value.lower().split(jnr)
        root = widget.invisibleRootItem()
        for idx in range(root.childCount()):
            child = root.child(idx)
            checked = child.text(0).lower() in values
            if checked:
                child.setCheckState(0, QtCore.Qt.Checked)
            else:
                child.setCheckState(0, QtCore.Qt.Unchecked)
        return


    if isinstance(widget, QtWidgets.QComboBox):
        if not widget.isEditable():
            dataidx = widget.findData(value,flags=QtCore.Qt.MatchFixedString)
            if dataidx != -1:
                return widget.setCurrentIndex(dataidx)
            if type(value) is int:
                return widget.setCurrentIndex(value)
        else:
            idx = widget.findData(value)
            if idx !=-1:
                widget.setCurrentIndex(idx)
            else:
                widget.lineEdit().setText(value)
        return
        

    raise RuntimeError("setWidgetValue unknown widget %r %s" %
                       (widget.__class__, widget.objectName()))


def getWidgetValue(widget, content=False,noGetData=False):
    if hasattr(widget, "getData") and not noGetData:
        return widget.getData()

    if isinstance(widget, QtWidgets.QPushButton):
        return

    if isinstance(widget, QtWidgets.QLineEdit):
        return widget.text()

    if isinstance(widget, (QtWidgets.QDoubleSpinBox, QtWidgets.QSpinBox)):
        return widget.value()

    if isinstance(widget, QtWidgets.QCheckBox):
        return widget.isChecked()

    if isinstance(widget, QtWidgets.QPlainTextEdit):
        return widget.toPlainText()

    if isinstance(widget, QtWidgets.QTextEdit):
        return widget.toHtml()

    if isinstance(widget, QtWidgets.QDateTimeEdit):
        return widget.dateTime().toPython().replace(microsecond=0)

    if isinstance(widget, QtWidgets.QDateEdit):
        return widget.date().toPython()

    if isinstance(widget, QtWidgets.QDateTimeEdit):
        return widget.time().toPython().replace(microsecond=0)

    if isinstance(widget, QtWidgets.QComboBox):
        if not widget.isEditable():
            return widget.currentData()
        else:
            return widget.lineEdit().text()

    
    if isinstance(widget, QtWidgets.QTreeWidget):
        jnr=widget.info["joiner"]
        result = []
        root = widget.invisibleRootItem()
        for idx in range(root.childCount()):
            child = root.child(idx)
            
            if child.checkState(0) == QtCore.Qt.Checked:
                result.append(child.text(0))
            
        return jnr.join(result)

    raise RuntimeError("getWidgetValue unknown widget %r %s" %
                       (widget.__class__, widget.objectName()))
