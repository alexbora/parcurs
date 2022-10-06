        .global _main

        .p2align 4
        .data
val:
        .quad 9
        .p2align 4
val2:
        .quad 3

        .p2align 4
        .text
_main:
        //movq val(%rip), %xmm0
        //movq $5, %rax
        //cvtsi2sd %rax, %xmm0
        //movdqa val2(%rip), %xmm0

        movq val(%rip), %xmm6
        pslldq $8, %xmm6
        movdqa val2(%rip), %xmm5
        movsd %xmm5, %xmm6
        psrldq $8, %xmm6
        movq %xmm6, %rax
        ret

        /* working */
