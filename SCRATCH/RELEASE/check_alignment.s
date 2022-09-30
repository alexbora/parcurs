        .global _check_alignment

_check_alignment:
        pushf
        orq $0x40000, (%rsp)
        popf
        ret
