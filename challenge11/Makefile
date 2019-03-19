all: challenge11

challenge11: challenge11.c
	gcc -m32 -no-pie -z execstack -fno-stack-protector challenge11.c -o challenge11 -lcrypt

clean:
	rm challenge11
