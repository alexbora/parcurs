        .globl main, tim

        .data
format:
        .ascii "%s = %d\n\0"
timex:
        .quad 0
name:
        .ascii "AAA"

        .text
main:
        enter $16, $0
        //movq $0xc9, %rax
        movq $201, %rax
        movq $timex, %rdi
        syscall

        movq stdout, %rdi
        movq $format, %rsi
        movq $name, %rdx
        movq timex, %rcx
        movq $0, %rax

        pushq %rbx
        call fprintf
        popq %rbx

        leave
        ret

/* vim:
        ft=gas:*/
