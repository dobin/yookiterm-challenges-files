section .data
msg db 'Hi there',0xa

section .text
global _start
_start:

xor eax,eax
xor ebx,ebx
xor ecx,ecx
xor edx,edx

mov al, 0x4
mov bl, 0x1
mov ecx, msg
mov dl, 0x8
int 0x80

mov al, 0x1
xor ebx,ebx
int 0x80
