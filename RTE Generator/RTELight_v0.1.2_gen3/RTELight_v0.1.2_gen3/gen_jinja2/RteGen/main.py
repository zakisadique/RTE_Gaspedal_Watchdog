from pprint import pprint
from .RTEgen import RTEgen
import os
import argparse

"""main module to launch the RteGen and generate a project from the file specified in the command line
"""

def main():
    generator = RTEgen()
    parser = argparse.ArgumentParser()
    parser.add_argument("xmlfile")
    parser.add_argument("-o","--outdir",required=False,help="Output directory, overrides the value loaded from the XML-File")
    parser.add_argument("-t","--template",required=False,help="Template directory, overrides the value loaded from the XML-File")
    cmdline_args = parser.parse_args()
    if cmdline_args.xmlfile:
        generator.load(cmdline_args.xmlfile)
        generator.generate(outdir=cmdline_args.outdir,template=cmdline_args.template)

if __name__=="__main__":
    main()