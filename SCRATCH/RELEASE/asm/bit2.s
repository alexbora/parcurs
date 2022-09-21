        .global _main

_main:
        movq $2, %rdi
        movq $1111, %rax
        andq %rdi, %rax
        ret

