all: challenge14

challenge14: challenge14-server.c
	gcc -no-pie -z execstack -fstack-protector-all challenge14-server.c -o challenge14-server 

clean:
	rm challenge14
