        .data

number:
        .byte 0b00000011

        .text

        .globl _start

_start:
        mov $0, %cx
        mov number(, %rcx, 1), %di
        movq $number, %rbx
        // test $4, %bx
        // je mod

        bt $2, %rbx
        lahf
        movb %al, %dil

mod:
        // xorq %rdi, %rdi
        // mov $1, %di
        mov $60, %al
        syscall
exit:
        mov $0, %di
        mov $60, %al
        syscall
