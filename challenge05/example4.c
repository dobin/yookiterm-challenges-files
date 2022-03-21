#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// integer truncation
int* example(int *array, int len){
   int *myarray, i;

   myarray = malloc(len * sizeof(int));   // len < 0? len = 0?
   if(myarray == NULL){
       printf("Error: Could not allocate array\n");
       return NULL;
   }

   printf("Could allocate array with size: %lu (%i)\n", (len * sizeof(int)), len);

   for(i = 0; i < len; i++){
       myarray[i] = array[i];
   }

   return myarray;
}

void main(int argc, char **argv) {
    if (argc != 2) {
        printf("%s <len>\n", argv[0]);
        exit(1);
    }

    int arr[] = { 42, 42 };
    int inputLen = strtoll(argv[1], NULL, 0);

    example(arr, inputLen);
}