        .global _main

_main:
        /* movq $17, %rax */
        movb $16, %bl
        xor %rax, %rax
        movb $1, %al
        shlb $4, %al
        andb %al, %bl
        /* andq $0b10000, %rax */
        jz exit
        shrq $4, %rax
        ret

exit:
        xor %rax, %rax
        ret
