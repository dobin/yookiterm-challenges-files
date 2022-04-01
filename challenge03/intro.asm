section .data
msg db 'AABBCCDD'


section .text
global _start
_start:

mov eax, 10
mov ah, 0x1
add eax, 0x10

mov eax, 0x11223344

mov ebx, 0x8048001
mov eax, [ebx]

mov ebx, 0x41424344
mov eax, [ebx]
