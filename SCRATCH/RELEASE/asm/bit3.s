        .global _main

_main:

        movl $4, %eax
        andl $0b100, %eax
        shrl $2, %eax
        ret

