        .globl _main, HAIR_OFFSET

        .data
format:
        .ascii "%d\12\0"
txt:
        .ascii "txt\n\0"

        .equ HAIR_OFFSET, 0

        .text
_main:
        /* enter $16, $0 */

        pushq %rbp
        movq %rsp, %rbp
        subq $16, %rsp

        xorq %rax, %rax
        movb $1, %al
        movb $1, %ah
        movq %rax, %rdx
        leaq format(%rip), %rsi
        movq	___stderrp@GOTPCREL(%rip), %rax
        movq	(%rax), %rdi
        /* xorl %eax, %eax */
        call _fprintf

        movb $1, %dl
        cmpb $0, %dl
        jne continue
        addq $16, %rsp
        leave
        ret

continue:
        movq $7, %rax
        addq $16, %rsp
        leave

        ret

