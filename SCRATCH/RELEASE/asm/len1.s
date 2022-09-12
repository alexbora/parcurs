        .global _main

        .data
string:
        .ascii "text\0"

        .text
_main:
        leaq string(%rip), %rdi
        xorq %rax, %rax
        /* movb $'x', %al */
        /* repne scasb */
        repnz scasb
        decl %edi
        movl %edi, %eax
        ret
