        .globl main

        .data
file:
        .ascii "myfile.txt\0"
mode:
        .ascii "w++\0"

txt:
        .ascii "txt\0"
format:
        .ascii "%s\n\0"

        .text
main:
        pushq %rbp
        movq %rsp, %rbp
        subq $16, %rsp

        // enter $16, $0
        movq $file, %rdi
        movq $mode, %rsi
        call fopen
        movq %rax, -8(%rbp)
        movq -8(%rbp), %rdi
        movq $format, %rsi
        movq $txt, %rdx

        movq $0, %rax
        call fprintf

        movq -8(%rbp), %rdi
        call fclose

        leave
        ret
