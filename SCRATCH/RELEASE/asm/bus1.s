        .global _main

_main:
        pushf
        /* orq $0b10000, (%rsp) */
        /* movq $1, %rax */
        /* shl $18, %rax */
        /* movq $0x40000, %rax */
        orq $0x40000, (%rsp)
        /* andq (%rsp), %rax */
        shrq $18, (%rsp)
        movq (%rsp), %rax
        /* movq (%rsp), %rax */
        popf
        ret
