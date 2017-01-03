#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "noteheap-cmdparser.h"
#include "noteheap-model.h"

#define INPUT_SIZE 128


void cmdReceiver() {
	char input[INPUT_SIZE];

	while(1) {
		printf("> ");
		gets(input);
		cmdParser(input);

/*
		strcpy(input, "todo add work 123 this is the todo");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list view work");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list add private work:0");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list view private");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list del work:0");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list view private");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "alarm add testalarm");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "alarm list");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list view private");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "todo edit private:0 32 this is the NEW todo");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "list view private");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "alarm list");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");

		strcpy(input, "alarm del 0");
		printf("> %s\n", input);
		cmdParser(input);
		printf("\n");
*/
	}
}


void main(int argc, char **argv) {
	modelInit();

	printf("Welcome to noteheap v1.0\n");
	cmdReceiver();
}
