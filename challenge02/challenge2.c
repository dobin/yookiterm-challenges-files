#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Array() {
        unsigned int stackTop = 0xaabbccdd;
        char charArray[4] = { 1, 2, 3, 4 };
        unsigned int stackBot = 0x11223344;

        printf(
        "unsigned int stackTop = 0xaabbccdd; \n"
        "char charArray[4] = { 1, 2, 3, 4 }; \n"
        "unsigned int stackBot = 0x11223344; \n"
        "\n"
        );
        printf("stackBot      @ %p: 0x%x\n", &stackBot, stackBot);
        printf("charArray[-1] @ %p: 0x%hhx (part of stackBot)\n", (void *) &charArray[-1], charArray[-1]);
        printf("charArray[0]  @ %p: 0x%hhx\n", (void *) &charArray[0], charArray[0]);
        printf("charArray[1]  @ %p: 0x%hhx\n", (void *) &charArray[1], charArray[1]);
        printf("charArray[4]  @ %p: 0x%hhx (part of stackTop)\n", (void *) &charArray[4], charArray[4]);
        printf("stackTop      @ %p: 0x%x\n", &stackTop, stackTop);
}


struct __attribute__((__packed__)) cStruct {
        short x;
        long y;
        char z[2];
};

void Struct() {
        struct cStruct cstruct;
        cstruct.x = 1;
        cstruct.y = 2;
        cstruct.z[0] = 0x10;
        cstruct.z[1] = 0x11;

        printf(
        "struct cStruct { \n"
        "        short x; \n"
        "        long y; \n"
        "        char z[2]; \n"
        "}; \n"

        "cstruct.x = 1; \n"
        "cstruct.y = 2; \n"
        "cstruct.z[0] = 0x10; \n"
        "cstruct.z[1] = 0x11; \n"
        "\n"
        );

        printf("cStruct.x    @ %p (size %i)\n", (void *) &cstruct.x, sizeof(cstruct.x));
        printf("cStruct.y    @ %p (size %i)\n", (void *) &cstruct.y, sizeof(cstruct.y));
        printf("cStruct.z[0] @ %p (size %i)\n", (void *) &cstruct.z[0], sizeof(cstruct.z[0]));
        printf("cStruct.z[1] @ %p (size %i)\n", (void *) &cstruct.z[1], sizeof(cstruct.z[1]));
}


void Strncpy() {
        char dest1[8] = "1234567\0";
        char dest2[8] = "1234567\0";

        printf(
        "char dest1[8] = \"1234567\\0\"; \n"
        "char dest2[8] = \"1234567\\0\"; \n"
        "\n"
        );

        printf("dest1 @ %p: %s\n", dest1, dest1);
        printf("dest2 @ %p: %s\n", dest2, dest2);

        strncpy(dest2, "AABBCCDD", 8);

        printf("After strncpy(dest2, \"AABBCCDD\"), without space for nul:\n");
        printf("dest1 @ %p: %s\n", dest1, dest1);
        printf("dest2 @ %p: %s (missing nul terminator)\n", dest2, dest2);
}

void main(int argc, char **argv) {
        if (argc != 2) {
                printf("%s: array|struct|strncpy", argv[0]);
                exit(1);
        }
        if (strcmp(argv[1], "array") == 0) {
                Array();
        }
        if (strcmp(argv[1], "struct") == 0) {
                Struct();
        }
        if (strcmp(argv[1], "strncpy") == 0) {
                Strncpy();
        }
        printf("\n");
}
