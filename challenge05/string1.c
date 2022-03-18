#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// strcpy()
void main(int argc, char **argv) {
    char buffer[128];

    char str[8];
    strcpy(str, "1234567"); // str[7] = ‘\0’
    printf("A: %i  %s\n", strlen(str), str);

    strcpy(str, "12345678");  // str[7] = ‘8’
                            // str[8] = ‘\0’
    printf("B: %i  %s\n", strlen(str), str);

    strcpy(str, "123456789");   // str[7] = ‘8’
                                // str[8] = ‘9’
                                // str[9] = ‘\0’
    printf("C: %i  %s\n", strlen(str), str);
}