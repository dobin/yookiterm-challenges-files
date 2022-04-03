CFLAGS = -O0 -m32 -z execstack -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer -ggdb

all: challenge10

challenge10: challenge10.c
	gcc challenge10.c $(CFLAGS) -o challenge10 -lcrypt

clean:
	rm challenge10
