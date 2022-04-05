CFLAGS = -O0 -m32 -z execstack -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer -ggdb

all: challenge11

challenge11: challenge11.c
	gcc challenge11.c $(CFLAGS) -o challenge11 -lcrypt

clean:
	rm challenge11
