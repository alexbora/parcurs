        .globl _main

        .p2align 4
        .text

_main:
        movl $5, %edi
        xorb %al, %al
        subl $1, %edi
        cmpl $4, %edi
        setbe %al
        ret
