#include <stdio.h>
#include <string.h>

void Array() {
        unsigned int stackTop = 0xaabbccdd;
        char charArray[4];
        unsigned int stackBot = 0x11223344;

        printf("Array():\n");

        charArray[0] = 1;
        charArray[1] = 2;
        charArray[2] = 3;
        charArray[3] = 4;

        printf("stackTop      @ %p: 0x%x\n", &stackTop, stackTop);
        printf("CharArray #0  @ %p: 0x%hhx\n", (void *) &charArray[0], charArray[0]);
        printf("CharArray #1  @ %p: 0x%hhx\n", (void *) &charArray[1], charArray[1]);
        printf("CharArray #4  @ %p: 0x%hhx (part of stackTop)\n", (void *) &charArray[4], charArray[4]);
        printf("CharArray #-1 @ %p: 0x%hhx (part of stackBot)\n", (void *) &charArray[-1], , charArray[-1]);
        printf("stackBot      @ %p: 0x%x\n\n", &stackBot, stackBot);
}


struct cStruct {
        short x;
        long y;
        char z[3];
};

void Struct() {
        printf("Struct():\n");

        struct cStruct cstruct;
        cstruct.x = 1;
        cstruct.y = 2;
        cstruct.z[0] = 0x10;
        cstruct.z[1] = 0x11;
        cstruct.z[2] = 0x12;

        printf("cStruct.x    @ %p\n", (void *) &cstruct.x);
        printf("cStruct.y    @ %p\n", (void *) &cstruct.y);
        printf("cStruct.z[0] @ %p\n", (void *) &cstruct.z[0]);
        printf("cStruct.z[1] @ %p\n", (void *) &cstruct.z[1]);
        printf("cStruct.z[2] @ %p\n", (void *) &cstruct.z[1]);
}


void Strncpy() {
        printf("Strncpy():\n");

        char dest1[8] = "1234567\0";
        char dest2[8] = "1234567\0";

        printf("Init:\n");
        printf("dest1 @ %p: %s\n", dest1, dest1);
        printf("dest2 @ %p: %s\n", dest2, dest2);

        strncpy(dest2, "AABBCCDD", 8);

        printf("After strncpy(dest2, \"AABBCCDD\"):\n");
        printf("dest1 @ %p: %s\n", dest1, dest1);
        printf("dest2 @ %p: %s (missing nul terminator)\n", dest2, dest2);
}

void main(void) {

        Array();
        printf("\n");

        Struct();
        printf("\n");

        Strncpy();
}
