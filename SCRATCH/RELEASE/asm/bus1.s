        .global _main

_main:
        pushf
        /* orq $0b10000, (%rsp) */
        andq $0b10000, (%rsp)
        popf
        movq (%rsp), %rax
        ret
