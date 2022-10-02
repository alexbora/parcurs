        .global _main

_main:
        jmp _test2
        pushf
        /* orq $0b10000, (%rsp) */
        /* movq $1, %rax */
        /* shl $18, %rax */
        /* movq $0x40000, %rax */
        orq $0x40000, (%rsp)
        /* andq (%rsp), %rax */
        shrq $18, (%rsp)
        movq (%rsp), %rax
        /* movq (%rsp), %rax */
        popf
        /* jmp _test */
        ret

_test:
        /* lahf */
        pushf
        movq $0x40000, %rax
        orq $0x40000, (%rsp)
        andq (%rsp), %rax
        /* andq $1, %rax */
        popf
        ret

_test2:
        pushq %rax
        lahf
        orl $0x4, %eax
        movq %rax, %rbx
        sahf
        popq %rax
        movq %rbx, %rax
        andq $1, %rax
        ret
