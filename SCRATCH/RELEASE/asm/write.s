        .global _main

        .data
txt:
        .asciz "a"

txt2:
        .quad 97

        .text
        .p2align 4
_main:
        movl $1, %edx
        movl $1, %edi
        leaq txt2(%rip), %rsi
        jmp *_write@GOTPCREL(%rip)
        xorq %rax, %rax
        ret
