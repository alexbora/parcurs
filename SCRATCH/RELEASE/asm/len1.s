        .global _main

        .data
string:
        .ascii "text\0"

        .text
_main:
        xorq %rax, %rax
        leaq string(%rip), %rdi
        /* movb $'x', %al */
        /* repne scasb */
        /* addl %edi, %r11d */
        repnz scasb
        decl %edi
        movl %edi, %eax
        /* movl %r11d, %eax */
        ret
