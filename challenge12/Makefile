all: challenge12

challenge12: challenge12.c
	gcc -z execstack -fno-stack-protector challenge12.c -o challenge12 -lcrypt

clean:
	rm challenge12
