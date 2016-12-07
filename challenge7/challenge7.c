#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void functionMinimal(void) {
        return;
}

int functionBasic(int c) {
        int d;
        d = c + 1;
        return d;
}

char* functionAdvanced(char *a, char *b) {
        strcpy(a, b);
        return a;
}


int main(int argc, char **argv) {
        char *a = "AAAAA";
        char *b = "BBB";
        int ret2;
        char *ret3;

        functionMinimal();

        ret2 = functionBasic(5);

        ret3 = functionAdvanced(a, b);
}