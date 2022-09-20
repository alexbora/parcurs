        .global _main

        .data
mystring:
        .ascii "aAa\0"

        .text
_main:
        leaq mystring(%rip), %rdi
        movb $0, %al
        repne scasb
        movq $'\1', (%rdi) // (rdi) now points at the end of the string
        movq $1, %rcx
        movq -4(%rdi, %rcx, 2), %rax // rcx is 1, otherwise 0. 2 x 1 -4 = -16, second char.
        /* movq %rdi, %rax */
        ret

