#include <stdio.h>
#include <stdlib.h>

void IShouldNeverBecalled() {
    printf("I should never be called");
    fflush(stdout);
    exit(0);
}

void vulnerable(char *arg) {
    char buff[16];
    strcpy(buff, arg);
}

void main(int argc, char **argv) {
    vulnerable(argv[1]);
    return(0);
}
