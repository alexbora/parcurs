        .global _printf

        .data
.text:
        .ascii "Ha\0\n"
.text_end:

        .text
_printf:
        movq $1, %rax
        movq $1, %rdi
        leaq $(text)GOTPRCREL, %rsi
        movq $(text_end - text), %rdx
        syscall
        ret
