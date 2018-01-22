all: write execve1 execve3 syscall shellcodetest

write: write.s
        as write.s -o write.o
        ld write.o -o write

		
execve1: execve1.s
        as execve1.s -o execve1.o
        ld execve1.o -o execve1

execve3: execve3.s
        as execve3.s -o execve3.o
        ld execve3.o -o execve3

syscall: syscall.c
        gcc syscall.c -o syscall

shellcodetest: shellcodetest.c
        gcc shellcodetest.c -o shellcodetest

clean:
        rm execve1.o execve1
        rm execve3.o execve3
        rm syscall
        rm shellcodetest

		
clean:
        rm write write.o
        rm execve1.o execve1
        rm execve3.o execve3
        rm syscall
        rm shellcodetest

