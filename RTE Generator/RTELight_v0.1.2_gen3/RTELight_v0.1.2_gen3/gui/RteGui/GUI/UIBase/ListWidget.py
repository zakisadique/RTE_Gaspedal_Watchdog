# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ListWidget.ui'
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


class Ui_ListWidget(object):
    def setupUi(self, ListWidget):
        if not ListWidget.objectName():
            ListWidget.setObjectName(u"ListWidget")
        ListWidget.resize(400, 300)
        self.verticalLayout = QVBoxLayout(ListWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.newBtn = QPushButton(ListWidget)
        self.newBtn.setObjectName(u"newBtn")

        self.horizontalLayout.addWidget(self.newBtn)


        self.verticalLayout_2.addLayout(self.horizontalLayout)

        self.treeWidget = QTreeWidget(ListWidget)
        __qtreewidgetitem = QTreeWidgetItem()
        __qtreewidgetitem.setText(0, u"1");
        self.treeWidget.setHeaderItem(__qtreewidgetitem)
        self.treeWidget.setObjectName(u"treeWidget")
        self.treeWidget.setAlternatingRowColors(True)
        self.treeWidget.setIndentation(0)
        self.treeWidget.setHeaderHidden(True)

        self.verticalLayout_2.addWidget(self.treeWidget)

        self.srchbar = QLineEdit(ListWidget)
        self.srchbar.setObjectName(u"srchbar")

        self.verticalLayout_2.addWidget(self.srchbar)


        self.verticalLayout.addLayout(self.verticalLayout_2)


        self.retranslateUi(ListWidget)

        QMetaObject.connectSlotsByName(ListWidget)
    # setupUi

    def retranslateUi(self, ListWidget):
        ListWidget.setWindowTitle(QCoreApplication.translate("ListWidget", u"ListWidget", None))
        self.newBtn.setText(QCoreApplication.translate("ListWidget", u"New {objname}", None))
        self.srchbar.setPlaceholderText(QCoreApplication.translate("ListWidget", u"Search...", None))
    # retranslateUi

