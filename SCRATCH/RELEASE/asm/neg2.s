        .global _main

_main:
        movq $1, %rax
        /* negq %rax */
        notq %rax
        ret

