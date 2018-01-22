.globl _start
.section .text

_start:
        adr x0, .  // get PC into x0
        add x0, x0, 24
        mov x1, 0
        mov x2, 0
        mov x8, #221   // execve syscall
        svc #0

        .ascii "/bin/sh\0"
