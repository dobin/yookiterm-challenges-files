#include <stdio.h>
#include <string.h>

char *shellcode = "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x04\xb3\x01\xb2\x08\x68\x68\x65\x72\x65\x68\x48\x69\x20\x74\x89\xe1\xcd\x80\xb0\x01\x31\xdb\xcd\x80";

int main(void) {
        char stackShellcode[128];
        memcpy(stackShellcode, shellcode, strlen(shellcode));
        ( *( void(*)() ) stackShellcode)();
}
