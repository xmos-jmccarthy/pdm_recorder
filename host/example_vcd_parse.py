#!/usr/bin/env python3

import argparse
import json
import sys
from pyDigitalWaveTools.vcd.parser import VcdParser


def main(filename):
    with open(filename) as vcd_file:
        vcd = VcdParser()
        vcd.parse(vcd_file)
        data = vcd.scope.toJson()
        print(json.dumps(data, indent=4, sort_keys=True))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--infile",
                      type=str,
                      default="xscope.vcd",
                      help=
"""Name of input vcd file to parse.""")
    args = parser.parse_args()

    main(args.infile)