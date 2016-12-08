#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Call: %s <name>\n", argv[0]);
        exit(0);
    }

    printf("Hello %s\n", argv[1]);
}
