#include <stdio.h>

void main(int argc, char **argv) {
        if (argc != 2) {
                printf("Usage: %s <idx>", argv[0])
                return
        }

        int array[5] = { 0, 1, 2, 3, 4 };
        int idx = atoi(argv[1]);
        printf("Number at index %i: 0x%x\n", idx, array[idx]);
}
