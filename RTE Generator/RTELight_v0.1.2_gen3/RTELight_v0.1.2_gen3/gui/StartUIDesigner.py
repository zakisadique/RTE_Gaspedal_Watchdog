import os
import subprocess
import sys

import PySide2

files = list(map(os.path.abspath, sys.argv[1:]))
os.chdir("sources/uifiles")
subprocess.Popen(
    [os.path.join(os.path.dirname(PySide2.__file__), "designer.exe")] + files)
