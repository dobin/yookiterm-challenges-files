#include <stdio.h>
#include <stdlib.h>

char globalVariable[] = "GlobalVar";
const char globalStaticVariable[] = "GlobalStaticVar";

int main(int argc, char **argv) {
	char *localStackVar = "StackVar";
	char *heapVar = malloc(16);

	printf("Global variable:        0x%p\n", globalVariable);
	printf("Global static variable: 0x%p\n", globalStaticVariable);
	printf("Stack variable:         0x%p\n", localStackVar);
	printf("Heap variable:          0x%p\n", heapVar);
}
