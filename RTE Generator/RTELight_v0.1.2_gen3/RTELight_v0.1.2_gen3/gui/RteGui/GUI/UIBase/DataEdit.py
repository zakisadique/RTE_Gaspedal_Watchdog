# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'DataEdit.ui'
##
## Created by: Qt User Interface Compiler version 5.15.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QDate, QDateTime, QMetaObject,
    QObject, QPoint, QRect, QSize, QTime, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QCursor, QFont,
    QFontDatabase, QIcon, QKeySequence, QLinearGradient, QPalette, QPainter,
    QPixmap, QRadialGradient)
from PySide2.QtWidgets import *

from ..ListWidget import ListWidget


class Ui_DataEdit(object):
    def setupUi(self, DataEdit):
        if not DataEdit.objectName():
            DataEdit.setObjectName(u"DataEdit")
        DataEdit.resize(541, 300)
        self.verticalLayout = QVBoxLayout(DataEdit)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.splitter = QSplitter(DataEdit)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.data_list = ListWidget(self.splitter)
        self.data_list.setObjectName(u"data_list")
        self.data_list.setMaximumSize(QSize(16777215, 16777215))
        self.splitter.addWidget(self.data_list)
        self.editor = QWidget(self.splitter)
        self.editor.setObjectName(u"editor")
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(3)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.editor.sizePolicy().hasHeightForWidth())
        self.editor.setSizePolicy(sizePolicy)
        self.splitter.addWidget(self.editor)

        self.verticalLayout.addWidget(self.splitter)


        self.retranslateUi(DataEdit)

        QMetaObject.connectSlotsByName(DataEdit)
    # setupUi

    def retranslateUi(self, DataEdit):
        DataEdit.setWindowTitle(QCoreApplication.translate("DataEdit", u"DataEdit", None))
    # retranslateUi

