        .global _main
        .data
format:
        .ascii "%s\n\0"
name:
        .ascii "a\0"

name2:
        .ascii "test"
name2end:

        .text
_main:
        movq $2, %rdi
        leaq format(%rip), %rsi
        leaq name(%rip), %rdx
        xorq %rax, %rax
        pushq %rbx
        movq $(name2end - name2), %rax
        call _fprintf
        popq %rbx
        ret

_nop:
        pushq %rbx
        call _ti
        popq %rbx
        ret

_ti:
        movq $0x2000000116, %rax
        syscall
        movq %rdx, %rax
        ret

// vim:
        ft=asm
