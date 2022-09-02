        .data

        .text

        .global main

main:
        movl $1, %eax
        cpuid
        shrl $30, %ecx
        andl $1, %ecx
        movl %ecx, %eax

        rdrand %rax
        ret
