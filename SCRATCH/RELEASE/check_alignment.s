        #ifdef __linux__
        .global check_alignment
        #else
        .global _check_aligment
        #endif

        .p2align 4
        .text
        #ifdef __linux__
check_alignment:
        #else
_check_aligment:
        #endif
        pushf
        orq $0x40000, (%rsp)
        popf
        ret
