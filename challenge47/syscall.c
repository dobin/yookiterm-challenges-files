#include <stdio.h>
#include <sys/syscall.h>

void main(void) {
        printf("Syscall no. of write : %i\n", SYS_write);
        printf("Syscall no. of execve: %i\n", SYS_execve);
}
