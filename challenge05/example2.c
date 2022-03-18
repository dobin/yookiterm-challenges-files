#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

// unsigned int
void example(char *buf1, char *buf2, unsigned int len1, unsigned int len2)
{
    char mybuf[BUF_SIZE];

    if((len1 + len2) > BUF_SIZE){    // Truncate if (len1 + len2) > 2^32
        printf("Not enough space: %i + %i > %i\n", len1, len2, BUF_SIZE);
        return -1;
    }

    printf("Ok, copying %u and then %u bytes\n", len1, len2);
    memcpy(mybuf, buf1, len1);      
    memcpy(mybuf + len1, buf2, len2); // buffer overflow
}

void main(int argc, char **argv) {
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];


    if (argc != 3) {
        printf("%s <0xlen1> <0xlen2>\n", argv[0]);
        exit(1);
    }

    int len1 = strtol(argv[1], NULL, 0);
    int len2 = strtol(argv[2], NULL, 0);

    example(buf1, buf2, len1, len2);
}