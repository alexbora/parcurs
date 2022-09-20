        .global _main
        .type _main, @function

        .data
file:
        .ascii "myfile.txt\0"
mode:
        .asciz "w++"

mydata:
        .zero 1024

        .bss
        .lcomm myvar, 8

        .extern yourvar

        .p2align 4
        .text

_main:
        pushq %rbp
        movq %rsp, %rbp
        subq $16, %rsp

        leaq mode(%rip), %rsi
        leaq file(%rip), %rdi
        call _fopen

        xorq %rax, %rax

        leave
        ret
