        .global _main

        .p2align 4
        .data

name_a:
        .asciz "A"
age_a:
        .quad 11

name_b:
        .asciz "B"
age_b:
        .quad 13

people:
        .asciz "me"
        .long 7, 5, 1975
        .asciz "tut"
        .long 29, 10, 2008
        .byte 0
endpeople:

        .text
        .p2align 4
_main:
        movq name_a+2+8+2(%rip), %rax
        movl $(endpeople - people), %eax
        movq people+3+4(%rip), %rax
        ret

