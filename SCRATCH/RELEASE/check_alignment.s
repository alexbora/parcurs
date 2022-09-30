        .global _check_alignment

        .p2align 4
        .text
_check_alignment:
        pushf
        orq $0x40000, (%rsp)
        popf
        ret
