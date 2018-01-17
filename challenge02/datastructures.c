#include <stdio.h>
#include <string.h>

void funcWithArray() {
        unsigned int dummy1 = 0xaabbccdd;
        char charArray[4];
        unsigned int dummy2 = 0x11223344;

        printf("funcWithArray:\n");

        charArray[0] = 1;
        charArray[1] = 2;
        charArray[2] = 3;
        charArray[3] = 4;

        printf("Dummy 1 (%p): %i/0x%x\n", &dummy1, dummy1, dummy1);
        printf("Dummy 2 (%p): %i/0x%x\n\n", &dummy2, dummy2, dummy2);

        printf("CharArray #0  (%p): %i/0x%hhx\n", (void *) &charArray[0], charArray[0], charArray[0]);
        printf("CharArray #1  (%p): %i/0x%hhx\n", (void *) &charArray[1], charArray[1], charArray[1]);
        printf("CharArray #4  (%p): %i/0x%hhx\n", (void *) &charArray[4], charArray[4], charArray[4]);
        printf("CharArray #-1 (%p): %i/0x%hhx\n", (void *) &charArray[-1], charArray[-1], charArray[-1]);
}


struct cStruct {
        short x;
        long y;
        char z[3];
};

void funcWithStruct() {
        printf("funcWithStruct:\n");

        struct cStruct cstruct;
        cstruct.x = 1;
        cstruct.y = 2;
        cstruct.z[0] = 0x10;
        cstruct.z[1] = 0x11;
        cstruct.z[2] = 0x12;

        printf("cStruct.x    (%p): %i/0x%x)\n", (void *) &cstruct.x, cstruct.x, cstruct.x);
        printf("cStruct.y    (%p): %ld/0x%lx)\n", (void *) &cstruct.y, cstruct.y, cstruct.y);
        printf("cStruct.z[0] (%p): %i/0x%hhx)\n", (void *) &cstruct.z[0], cstruct.z[0], cstruct.z[0]);
        printf("cStruct.z[1] (%p): %i/0x%hhx)\n", (void *) &cstruct.z[1], cstruct.z[1], cstruct.z[1]);
        printf("cStruct.z[2] (%p): %i/0x%hhx)\n", (void *) &cstruct.z[1], cstruct.z[2], cstruct.z[2]);
}


void funcWithStrcpy() {
        printf("funcWithStrcpy:\n");

        char dest1[8] = "1111111";
        char dest2[8] = "2222222";

        printf("Init:\n");
        printf("%p Dest1 : %s\n", dest1, dest1);
        printf("%p Dest2 : %s\n", dest2, dest2);

        strncpy(dest2, "33333333", 8);

        printf("After strncpy():\n");
        printf("%p Dest1 : %s\n", dest1, dest1);
        printf("%p Dest2 : %s\n", dest2, dest2);
}


void main(void) {

        funcWithArray();
        printf("\n");
        funcWithStruct();
        printf("\n");
        funcWithStrcpy();

}
