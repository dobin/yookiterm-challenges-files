CFLAGS = -O1 -fno-stack-protector -ggdb 

all: challenge53

challenge53: challenge53.c
	clang challenge53.c $(CFLAGS) -fsanitize=address -o challenge53-asan -lcrypt
	afl-clang challenge53.c $(CFLAGS) -fsanitize=address -o challenge53-fuzz -lcrypt
	gcc challenge53.c $(CFLAGS) -o challenge53 -lcrypt

clean:
	rm challenge53
