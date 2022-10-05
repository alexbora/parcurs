        .global _main

        .p2align 4
        .data
val:
        .double 75.5
        .p2align 4
val2:
        .quad 1, 2

        .p2align 4
        .text
_main:
        movq val(%rip), %xmm0
        movq $5, %rax
        cvtsi2sd %rax, %xmm0
        movdqa val2(%rip), %xmm0
        ret
