        .data

        .text

        .global main

main:
        movq $2, %rax
        movq $1, %rbx
        cmpxchg %rax, %rbx

        ret
