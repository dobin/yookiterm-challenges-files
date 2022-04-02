#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

// strncpy() fail
void main(int argc, char **argv) {
    char buffer[128];

    char str1[SIZE];
    char str2[SIZE];

    strncpy(str1, "XXXXYYYY", SIZE);
    strncpy(str2, "AAAABBBB", SIZE);

    printf("str1 @ %p: %02u  %s\n", str1, strlen(str1), str1);
    printf("str2 @ %p: %02u  %s\n", str2, strlen(str2), str2);
}