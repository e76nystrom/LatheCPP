#!/cygdrive/c/Python37/Python.exe

import re
import sys

argLen = len(sys.argv)
if argLen >= 2:
    inpFile = sys.argv[1]
else:
    sys.exit()

inp = open(inpFile, 'r')
out = False
for l in inp:
    if not out:
        if re.search(r".*?// <-", l):
            out = True
            print("#define LATHE_INC")
            print("#if defined(LATHE_INC)	// <-")
    else:
        if re.search(r"#define *INCLUDE", l):
            continue
        print(l, end='')
        if re.search(r".*?// ->", l):
            out = False
print("#undef INCLUDE")
print("#undef LATHE_INC")
inp.close()
