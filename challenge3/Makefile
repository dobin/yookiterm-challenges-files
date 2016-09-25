
all: print print2 print3 shellcodetest

print: print.asm
	nasm -f elf print.asm
	ld -m elf_i386 -o print print.o  

print2: print2.asm
	nasm -f elf print2.asm
	ld -m elf_i386 -o print2 print2.o

print3: print3.asm
	nasm -f elf print3.asm
	ld -m elf_i386 -o print3 print3.o

shellcodetest: shellcodetest.c
	gcc shellcodetest.c -z execstack -o shellcodetest

clean:
	rm shellcodetest print print.o print2 print2.o print3 print3.o

