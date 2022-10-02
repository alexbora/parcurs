        #iddef __linux__
        .global check_alignment
        #else
        .global _check_alignment
        #endif

        .p2align 4
        .text

        #ifdef __linux__
check_alignment:
        #else
_check_alignment:
        #endif
        pushq %rax
        lahf
        orq $0x4, %rax
        sahf
        popq %rax
        ret

        /* pushf */
        /* orq $0x40000, (%rsp) */
        /* popf */
        /* ret */
