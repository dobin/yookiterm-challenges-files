#!/usr/bin/python3

import time
import struct
import sys
import argparse
from pwn import *
import pprint

def main():
    context.update(arch='amd64', os='linux')
    e = ELF(sys.argv[1])
    rop = ROP(e)

    pprint.pprint(rop.gadgets)

    print("Useful gadgets:")
    print(rop.rax)
    print(rop.rdi)
    print(rop.rsi)
    print(rop.rdx)
    print(rop.syscallret)


if __name__ == '__main__':
        main()

