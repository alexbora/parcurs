        .global _main
        .data
source:
        .quad 1, 2, 3
dest:
        .quad 0, 0, 0

        .text
_main:
        leaq source(%rip), %rsi
        leaq dest(%rip), %rdi
        movq $2, %rcx
        rep movsq
        movb $0b1, -8(%rdi)
        movq -8(%rdi), %rax
        ret
