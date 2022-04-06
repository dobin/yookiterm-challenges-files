CFLAGS = -O1 -fno-stack-protector -ggdb -fsanitize=address

all: challenge53

challenge53: challenge53.c
	clang challenge53.c $(CFLAGS) -o challenge53 -lcrypt
	afl-gcc challenge53.c $(CFLAGS) -o challenge53-fuzz -lcrypt

clean:
	rm challenge53
