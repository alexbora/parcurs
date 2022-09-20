        .globl _main
        .balign 8
        .data
myvar:
        .asciz "txt"
myvarend:
        .equ len, myvarend-myvar

var:
        .8byte

        .p2align 4
        .text
_main:
        movq %rdi, %rax
        movq $len-1, %rax
        /* movq 0(%rsp), %rax */
        movb $0, var(%rip)
        subb $1, var(%rip)
        movb var(%rip), %al
        movq $1, %rdi
        ret

