        .data
src:
        .quad 4, 2, 3
dst:
        .quad 0, 0, 0

        .text

        .global main

main:
        movq $dst, %rdi
        movq $src, %rsi
        movq $3, %rcx
        rep movsq
        movq dst+8, %rax
        ret
