        .global _print_float

        .data
format:
        .ascii "%f\12\0"

        .text
        .p2align 4

_print_float:
        movq %rdi, -8(%rbp)
        movq	___stderrp@GOTPCREL(%rip), %rax
        movq (%rax), %rdi
        leaq format(%rip), %rsi
        /* movsd myval(%rip), %xmm0 */
        cvtsi2sd -8(%rbp), %xmm0
        /* movq OFFSET(%rbp), %r11 */

        /* %rax 1 no of xmm registers, %rdi stderr, %rsi format, %xmm0 value */

        movl $1, %eax
        call _fprintf
        xor %al, %al

        ret
