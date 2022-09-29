        .global _main

        .p2align 4
_main:
        movq $2, %rdi
        movq $1111, %rax
        andq %rdi, %rax
        ret

