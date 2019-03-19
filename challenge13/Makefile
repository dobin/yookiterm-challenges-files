all: challenge13

challenge13: challenge13.c
	gcc -no-pie -z execstack -fno-stack-protector challenge13.c -o challenge13 -lcrypt

clean:
	rm challenge13
