#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void functionMinimal(void) {
        return;
}

void functionInt(int c) {
        int d;
        d = c + 1;
}

void functionStrcpy(char *a, char *b) {
        strcpy(a, b);
}

int main(int argc, char **argv) {
        char *a = "AAAAA";
        char *b = "BBB";

        functionMinimal();
        functionInt(5);
        functionStrcpy(a, b);
}