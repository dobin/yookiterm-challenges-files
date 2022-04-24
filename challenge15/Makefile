CFLAGS = -O0 -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer -ggdb

all: challenge15

challenge15: challenge15.c
	gcc challenge15.c $(CFLAGS) -o challenge15 -lcrypt

clean:
	rm challenge15
