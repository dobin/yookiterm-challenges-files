all: noteheap

noteheap: noteheap.c noteheap-model.c noteheap-cmdparser.c
	gcc -c noteheap.c noteheap-model.c noteheap-cmdparser.c
	gcc noteheap.o noteheap-model.o noteheap-cmdparser.o -o noteheap

clean:
	rm noteheap.o noteheap-model.o noteheap-cmdparser.o noteheap
