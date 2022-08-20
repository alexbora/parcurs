        .global _main, _print

        .data
myval:
        .double 4

format:
        .ascii "%f\12\0"

        .text

        .p2align 4
_main:
        /* movq $5, %rax */
        /* cvtsi2sd %rax, %xmm0 */
        /* movq %xmm0, %rax */
        call _print
        ret

        .p2align 4
_print:
        /* pushq	%rbp */
        /* movq	%rsp, %rbp */
        /* subq	$16, %rsp */

        /* movq ___stderrp@GOTPCREL(%rip), %rdi */

        movq	___stderrp@GOTPCREL(%rip), %rax
        /* movq (%rdi), %rdi */
        movq (%rax), %rdi
        leaq format(%rip), %rsi
        movsd myval(%rip), %xmm0

        /* %rax 0, %rdi stderr, %rsi format, %rcx value */
        /* %rax 1, %rdi stderr, %rsi format, %xmm0 value */
        /* movq $6, %rdx */

        movl $1, %eax
        /* xorb %al, %al */
        /* call *_fprintf@GOTPCREL(%rip) */
        call _fprintf
        xorq %rax, %rax

        /* addq $16, %rsp */
        /* leave */
        ret

