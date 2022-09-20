        .globl _main
        .data

promptformat:
        .ascii "Enter two numbers separated by spaces, then press return.\n\0"
scanformat:
        .ascii "%d %d\0"
resultformat:
        .ascii "The result is %d.\n\0"

        .text
        .equ LOCAL_NUMBER, -8
        .equ LOCAL_EXPONENT, -16

_main:
        # Allocate space for two local variables
        enter $16, $0
        # Show the prompt to stdout
        movq stdout(%rip), %rdi
        movq promptformat(%rip), %rsi
        movq $0, %rax
        call _fprintf
        # Request the data
        movq stdin(%rip), %rdi

        movq scanformat(%rip), %rsi
        leaq LOCAL_NUMBER(%rbp), %rdx
        leaq LOCAL_EXPONENT(%rbp), %rcx
        movq $0, %rax
        call fscanf
        movq LOCAL_NUMBER(%rbp), %rdi
        movq LOCAL_EXPONENT(%rbp), %rsi
        call exponent
        movq stdout(%rip), %rdi
        movq resultformat(%rip), %rsi
        movq %rax, %rdx
        movq $0, %rax
        call _fprintf
        leave
        ret

