        .global _main

_main:
        movl $2, %eax
        movq %rax, %xmm5
_shitft:
        pslldq $8, %xmm5
        movq $3, %rax
        movq %rax, %xmm5

_exit:
        lock incq (%rcx)
        xorq %rax, %rax
        lock incq (%rcx)
        addq (%rcx), %rax
        movq %xmm5, %rax
        ret

