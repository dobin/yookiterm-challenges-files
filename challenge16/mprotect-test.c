#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

void main(void) {
        char stackvar[16];
        int ret;
        long long stackbase = (long long)( &stackvar ) & ~(PAGE_SIZE -1); // round down

        printf("Stack var: %p\n", &stackvar);
        printf("Stackbase: 0x%llx\n", stackbase);
        ret = mprotect( (void *) stackbase, PAGE_SIZE, PROT_READ|PROT_WRITE|PROT_EXEC);

        printf("Ret: %i\n", ret);
}
