        .global _printf

        .data
text:
        .ascii "Ha\n"

        .text
_printf:
        leaq text(%rip), %rdi
        call _printf
        xorl %eax, %eax
        leaveq
        retq

