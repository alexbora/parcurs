        .global _square

        .text

_square:
        movq %rdi, %rax
        imulq %rdi
        ret

