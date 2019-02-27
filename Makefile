
all: intro

intro: intro.asm
	nasm -f elf intro.asm
	ld -m elf_i386 -o intro intro.o
