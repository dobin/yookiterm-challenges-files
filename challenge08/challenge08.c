#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) {
        if (argc != 2) {
                printf("Usage: %s <idx>\n", argv[0]);
                return;
        }

        int array[4] = { 0xAA, 0xBB, 0xCC, 0xDD };
        int idx = atoi(argv[1]);
        printf("Number at index %i: 0x%x\n", idx, array[idx]);
}
