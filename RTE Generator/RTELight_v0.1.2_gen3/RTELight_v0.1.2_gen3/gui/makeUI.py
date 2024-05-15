import os
import PySide2
import sys
import subprocess

uic_exe = os.path.join(os.path.dirname(PySide2.__file__), "uic")

if sys.platform == "win32":
    uic_exe += ".exe"

uic_cmd = [uic_exe, "-g", "python", "-o"]


os.chdir(os.path.dirname(os.path.abspath(__file__)))

srcpath = "sources/uifiles"

for root, dirs, files in os.walk(srcpath):
    for filename in files:
        fp = os.path.join(root, filename)
        tgtpath = os.path.relpath(fp, start=srcpath)
        tgtpath = tgtpath.replace(".ui", ".py")
        tgtpath = os.path.join("RteGui/GUI/UIBase", tgtpath)
        tgtdir = os.path.dirname(tgtpath)
        if not os.path.isdir(tgtdir):
            os.makedirs(tgtdir)

        cmd = uic_cmd + [
            tgtpath,
            fp
        ]
        print("running command: ", " ".join(cmd))
        subprocess.call(cmd)
