        #iddef __APPLE__
        .global _main
        #else
        .global main
        #endif

        .p2align 4
        .data
val:
        .quad 9
        .p2align 4
val2:
        .quad 3

        .p2align 4
        .text
        #ifdef __APPLE__
_main:
        #else
main:
        #endif
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
