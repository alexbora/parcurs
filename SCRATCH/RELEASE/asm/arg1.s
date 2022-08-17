        .globl _main, _fprintf

        .data
txt:
        .ascii "txt\n\0"
        .p2align 4
        .text
_main:
        jmp print
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

_fprintf:
print:
        enter $0, $0
        movq ___stderrp@GOTPCREL(%rip), %rdi
        movq (%rdi), %rdi
        leaq txt(%rip), %rsi
        call *_fprintf@GOTPCREL(%rip)
        /* call _fprintf */
        /* xorq %rax, %rax */
        leave
        ret
