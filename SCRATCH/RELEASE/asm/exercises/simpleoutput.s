        .globl _main

        .data
mystring:
        .ascii "Hello there!\n"

mystring_end:
        .equ mystring_length, mystring_end - mystring

        .text
_main:
        ### Display the string
        # System call number
        movq $1, %rax
        # File descriptor
        movq $2, %rdi
        # Pointer to the data
        movq mystring(%rip), %rsi
        # Length of the data
        movq $mystring_length, %rdx
        syscall
        ### Exit
        retq
        movq $0x3c, %rax
        movq $0, %rdi
        syscall

/* vim:
ft=gas:
        */
