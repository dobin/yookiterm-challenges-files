CFLAGS = -O0 -m32 -z execstack -fno-stack-protector -no-pie -fno-pie -fno-omit-frame-pointer

all: challenge09

challenge09: challenge09.c
	gcc challenge09.c $(CFLAGS) -o challenge09 -lcrypt

clean:
	rm challenge09
