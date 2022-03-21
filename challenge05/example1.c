#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// signed int
void example(int inputLen, char *input) {
    char arr[1024];
    printf("Input len : %i / 0x%x\n", inputLen, inputLen);

    if (inputLen > 1024) {
            printf("Not enough space (%i is bigger than 1024)\n", inputLen);
            return;
    }
    printf("Ok, copying %u bytes\n", inputLen);
    memcpy(arr, input, inputLen);


}

void main(int argc, char **argv) {
    if (argc != 3) {
        printf("%s <0xinputLen> <input>\n", argv[0]);
        exit(1);
    }

    int inputLen = strtoll(argv[1], NULL, 0);
    char *input = argv[2];

    example(inputLen, input);
}