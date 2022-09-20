        .globl _start

        .data
name1:
        .ascii "txt"
        .byte 4

name2:
        .ascii "txt2"
        .byte 5

        .text
_start:
        movb $7, %al
        movb $6, %ah
        xchgb %ah, %al
        ret
