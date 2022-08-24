        .global _main, myval, OFFSET

        .data
myval:
        .double 4

        .equ OFFSET, -8

        .text
output:
        .ascii "%f\n\0"

_main:
        enter $0, $0
        /* movq $6, OFFSET(%rbp) */
        movq $1, %rax
        movq $7, %rdx
        cvtsi2sd %rax, %xmm0
        cvtsi2sd %rbx, %xmm1
        divsd %xmm1, %xmm0
        /* call _print_float */
        mov $2, %esi
        leaq output(%rip), %rdi
        call _printf
        xorl %eax, %eax
        leave
        ret
