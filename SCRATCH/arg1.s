        .globl _start

val1:
        .quad 3, 2, 1, 0

val2:
        .byte 1, 2, 3, 4

_start:
        leaq val1(%rip), %rbx
        addq $8, %rbx
        movq val1(, %rbx, 1), %rax
        ///* movq (%rbx), %rax */
        ret
