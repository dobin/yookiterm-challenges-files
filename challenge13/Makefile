CFLAGS = -O0 -z execstack -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer -ggdb

all: challenge13

challenge13: challenge13.c
	gcc challenge13.c $(CFLAGS) -o challenge13 -lcrypt

clean:
	rm challenge13
