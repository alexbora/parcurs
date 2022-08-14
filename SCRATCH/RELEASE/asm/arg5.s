        .global _start

_start:
        movb $1, %ah
        movb $3, %al
        movb $0, %al
        subb $1, %al

        movq $60, %rax
        syscall

