#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

// strncpy()
void main(int argc, char **argv) {
    char buffer[128];

    char str[SIZE];
    strncpy(str, "1234567", SIZE); // str[7] = ‘\0’
    printf("A: %i  %s\n", strlen(str), str);

    strncpy(str, "12345678", SIZE);  // str[7] = ‘8’
                            // str[8] = ‘\0’
    printf("B: %i  %s\n", strlen(str), str);

    strncpy(str, "123456789", SIZE);   // str[7] = ‘8’
                                // str[8] = ‘9’
                                // str[9] = ‘\0’
    printf("C: %i  %s\n", strlen(str), str);
}