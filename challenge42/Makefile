all: write execve1 execve2 execve3 shellcodetest

write: write.s
  as write.s -o write.o
  ld write.o -o write

execve1:
  as execve1.s -o execve1.o
  ld execve1.o -o execve1

execve2:
  as execve2.s -o execve2.o
  ld execve2.o -o execve2

execve1:
  as execve3.s -o execve3.o
  ld execve3.o -o execve3

shellcodetest:
	gcc shellcodetest.c -o shellcodetest -fno-stack-protector -z execstack

clean:
	rm write.o write
	rm execve1.o execve1
	rm execve2.o execve2
	rm execve3.o execve3
	rm shellcodetest
	
