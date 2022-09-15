        .global _main
        .data
        .incbin "logo.png"
        .text

_main:
        enter $0, $0
        pushq $0
        pushq _square(%rip)
        call *_square@GOTPCREL(%rip)
        leave
        ret
        movl $2, %eax
        movq %rax, %xmm5
_shift:
        pslldq $8, %xmm5
        movq $3, %rax
        movq %rax, %xmm5

_cmp:
        cmpq $3, %rax
        jne _exit1
        je _exit1
        jg _exit

_exit1:
        incq %rax
        ret

_exit:
        lock incq (%rcx)
        xorq %rax, %rax
        lock incq (%rcx)
        addq (%rcx), %rax
        movq %xmm5, %rax
        ret

_square:
        movl $7, %eax
        ret
