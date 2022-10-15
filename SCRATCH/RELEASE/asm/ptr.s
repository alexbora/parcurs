        .global _main

        .data

f:
        .quad _TEST1
        .quad _TEST2
        .text
_main:
        jmp *f+8(%rip)
        ret

_TEST1:
        movl $1, %eax
        ret
_TEST2:
        movl $2, %eax
        ret
