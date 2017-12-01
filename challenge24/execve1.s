.globl _start
.section .text

_start:

        mov x8, #221   // execve syscall
        adrp x0, message
        add x0, x0, :lo12:message
        mov x1, 0
        mov x2, 0
        svc #0

        mov x8, #93
        mov x0, #42
        svc #0

        ret

.section .rodata
message:
        .ascii "/bin/sh\0"
