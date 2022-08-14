        .global _start

        .text
_start:
        pushq %rbp
        movq %rsp, %rbp

        xorq %rax, %rax
        movb $3, %bl
        testb $0b00000010, %bl
        jnz bitwasset
        leave
        ret

bitwasset:
        movq $1, %rax
        leave
        ret
