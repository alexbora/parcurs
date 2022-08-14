        .global _start
        .data

people:
        .quad 0, 1, 2, 3
        .quad 3, 2, 1, 0
people_end:

        .equ size, (people_end - people)

persons:
        .ascii "abc\0"
        .quad 5
        .ascii "baa\0"
        .quad 7

        .text

_start:
        leaq people(%rip), %rbx
        addq $32, %rbx
        movq 16(%rbx), %rax
        incq (%rbx)
        movq (%rbx), %rax
        leaq size(%rip), %rax

        movq $0, %rcx
        leaq persons(%rip), %rbx
        movb 4(%rbx, %rcx, 1), %al
        movb 12(%rbx, %rcx, 1), %al
        movb 13(%rbx, %rcx, 1), %al
        movb 16(%rbx, %rcx, 1), %al

        movb 4(%rbx), %ah
        rorb $16, %al

        xorb %al, %al

        movb $1, %al
        rolb $1, %al

        movb $4, %ah
        rorl $1, %eax
        ret

_x:
        ret
