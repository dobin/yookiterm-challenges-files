#!/usr/bin/env python

import sys

binary = open(sys.argv[1],'rb')

for byte in binary.read():
 sys.stdout.write("\\x"+byte.encode("hex"))

print ""
