        .globl _main

_main:
        movb $1, %al
        cmpb $2, %al
        setz %al
        ret
