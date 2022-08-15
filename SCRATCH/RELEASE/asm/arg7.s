        .global _start

        .p2align 4
        .text
_start:
        pushq %rbp
        movq %rsp, %rbp

        xorq %rax, %rax
        movb $0, %bl
        testb $0b00000010, %bl
        jnz bitwasset

        movb $3, %bl
        andb $0b0000011, %bl
        movb %bl, %al
        leave
        ret

bitwasset:
        movq $1, %rax

        leave
        ret
