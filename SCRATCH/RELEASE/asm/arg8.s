        .file "arg8.s"
        .global _start
        .data
txt:
        .ascii "abcx\0"

        .text
_start:
        enter $16, $0
        subq $8, %rsp

        movq $-1, %rcx
        leaq txt(%rip), %rdi
        movb $'x', %al
        repne scasb

        decq %rdi
        /* movq %rdi, -8(%rbp) */
        /* movq -8(%rbp), %rax */

        /* xorq %rax, %rax */
        movq %rdi, %rax

        leave
        ret

