        .global _start

txt:
        .byte 97
endtxt:

_start:
        pushq %rbp
        movq %rsp, %rbp

        movb $1, %ah
        movb $3, %al
        movb $0, %al
        subb $1, %al

        movq $(endtxt-txt), %rdi
        popq %rbp

        movb $4, %ah
        movb $3, %al
        rorl $8, %eax
        movq %rax, %rdi

        movq $60, %rax
        syscall

