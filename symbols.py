#!/cygdrive/c/Python39/Python.exe

import re
import sys

if len(sys.argv) < 2:
    sys.exit()

f = open(sys.argv[1], "r")

for line in f:
    l = line.strip()
    fields = re.split("\s+", l)
    name = fields[-1]
    size = fields[-2]
    if size == ".hidden":
        size = fields[-3]
    if size == "00000000":
        continue
    print("%-40s %8s" % (name, size))
f.close
    
