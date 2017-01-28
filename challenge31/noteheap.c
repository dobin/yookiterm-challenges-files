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
	}
}


void fileReceiver(char *filename) {
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("Reading from file: %s\n", filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file\n");
		exit(2);
	}

	while (( read = getline(&line, &len, fp)) != -1) {
		if (line[read-1] == '\n') {
			line[read-1] = '\0';
			read--;
		}
		if (read > 0) {
			printf("read line: %s\n", line);
			cmdParser(line);
		}

	}

	fclose(fp);
}


void printHelp(char **argv) {
	printf("Usage: %s [OPTION]\n", argv[0]);
	printf("  --cmd     Interactive command interface\n");
	printf("  --file    Read commands from file\n");
}


void main(int argc, char **argv) {
	if (argc != 2 && argc != 3) {
		printHelp(argv);
		exit(0);
	}

	modelInit();

	if (strcmp(argv[1], "--cmd") == 0) {
		printf("Welcome to noteheap v1.0\n");
		cmdReceiver();
	} else if (argc == 3 && (strcmp(argv[1], "--file") == 0)) {
		fileReceiver(argv[2]);
	} else {
		printHelp(argv);
		exit(0);
	}
}
