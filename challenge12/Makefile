CFLAGS = -O0 -z execstack -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer -ggdb

all: challenge12

challenge12: challenge12.c
	gcc challenge12.c $(CFLAGS) -o challenge12 -lcrypt

clean:
	rm challenge12
