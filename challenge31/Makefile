all: noteheap

CC=gcc

noteheap: noteheap.c noteheap-model.c noteheap-cmdparser.c
	$(CC) -c noteheap.c noteheap-model.c noteheap-cmdparser.c
	$(CC) noteheap.o noteheap-model.o noteheap-cmdparser.o -o noteheap

clean:
	rm noteheap.o noteheap-model.o noteheap-cmdparser.o noteheap
