        .global _main

_main:
        /* movq $2, %rax */
        /* movb $0, %al */
        xorl %eax, %eax
        cmpb $0, %al
        lahf
        /* shrl $14, %eax */
        shrl $2, %eax
        ret
