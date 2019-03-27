#!/cygdrive/c/Python37/Python.exe

import re
import sys

argLen = len(sys.argv)
if argLen >= 2:
    inpFile = sys.argv[1]
else:
    sys.exit()

if argLen >= 3:
    outFile = sys.argv[2]
else:
    sys.exit()
    
inp = open(inpFile, 'r')
fOut = open(outFile, 'wb')
out = False
for l in inp:
    if not out:
        if re.search(r".*?// <-", l):
            out = True
            fOut.write(b"#if 1	// <-\n")
    else:
        if re.search(r"#define *INCLUDE", l):
            continue
        fOut.write(l.encode('utf-8'))
        if re.search(r".*?// ->", l):
            out = False
inp.close()
fOut.close()
