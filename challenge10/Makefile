all: challenge10

challenge10: challenge10.c
	gcc -m32 -z execstack -fno-stack-protector challenge10.c -o challenge10 -lcrypt

clean:
	rm challenge10
