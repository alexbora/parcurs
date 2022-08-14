        .global _start
        .data
txt:
        .ascii "This x\0"

        .text
_start:
        enter $16, $0

        movq $-1, %rcx
        leaq txt(%rip), %rdi
        movb $'x', %al

        repne scasb

        decq %rdi

        xorq %rax, %rax
        movq %rdi, %rax

        leave
        ret
