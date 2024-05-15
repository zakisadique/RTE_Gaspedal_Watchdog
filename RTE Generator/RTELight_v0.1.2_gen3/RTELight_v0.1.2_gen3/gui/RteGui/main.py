from .GUI.MainWindow import MainWindow
from PySide2 import QtWidgets, QtGui, QtCore
import argparse
import sys

"""main module to launch the RteGui and load a project from the file specified in the command line
"""

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("xmlfile",nargs='?')
    cmdline_args = parser.parse_args()
    app = QtWidgets.QApplication()
    QtWidgets.qApp=app
    app.MainWindow = MainWindow()
    app.MainWindow.loadFile(cmdline_args.xmlfile)
    app.MainWindow.show()
    app.exec_()


if __name__ == "__main__":
    main()