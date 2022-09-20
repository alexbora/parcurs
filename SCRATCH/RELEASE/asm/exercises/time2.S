        .globl _ride, _start

        .data
format:
        .ascii "%ld\12\0"

        .text
_ride:
        /* enter $16, $0 */
        pushq	%rbp
        movq	%rsp, %rbp
        /* subq $16, %rsp */

        /* subq $24, %rsp */
        subq $32, %rsp

        xorq %rdi, %rdi
        /* pushq %rbx */
        call _time
        /* popq %rbx */

        movq %rax, %rdx
        leaq format(%rip), %rsi
        movq	___stderrp@GOTPCREL(%rip), %rax
        movq	(%rax), %rdi
        xorl %eax, %eax

        /* pushq %rbx */
        call _fprintf
        /* popq %rbx */

        /* addq $24, %rsp */
        addq $32, %rsp

        xorl %eax, %eax
        leave
        ret
_start:
        pushq %rbx
        call _ride
        popq %rbx
        ret
