#include <stdio.h>
#include <stdlib.h>

char globalVariable[] = "GlobalVar";
const char globalStaticVariable[] = "GlobalStaticVar";

void function(void) {
	printf("blah");
}


int main(int argc, char **argv) {
	char localStackVar[16] = "StackVar";
	char *heapVar = malloc(16);

	printf("Global variable:        %p\n", globalVariable);
	printf("Global static variable: %p\n", globalStaticVariable);
	printf("Stack variable:         %p\n", localStackVar);
	printf("Heap variable:          %p\n", heapVar);
	printf("Function:               %p\n", &function);
}

