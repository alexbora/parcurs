        .globl _main

_main:
        movl $1, %eax
        cpuid
        /* andb $0b11000000000000000000000000000, %ecx */
        andl $0x18000000, %ecx
        /* testl $0x18000000, %ecx */
        cmpl $0x18000000, %ecx
        jne exit

        /* jz exit */

        movq $1, %rax
        ret

exit:
        movq $0, %rax
        ret

