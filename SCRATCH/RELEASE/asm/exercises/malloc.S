        .globl _main

_main:
        enter $16, $0
        movq $500, %rdi
        call _malloc

        movq %rax, -8(%rbp)

        movq -8(%rbp), %rdi
        call _free

        xorl %eax, %eax
        leave
        ret

