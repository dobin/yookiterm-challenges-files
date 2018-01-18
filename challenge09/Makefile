all: challenge09

challenge09: challenge09.c
	gcc -m32 -z execstack -fno-stack-protector challenge09.c -o challenge09 -lcrypt

clean:
	rm challenge09
