        .globl _main

var:
        .int 1

_main:
        xorq %rax, %rax
        movb $0b00000001, %al
        orb $0b00000011, %al
        movb $0b00000001, %ah
        xchgb %ah, %al
        movb $7, %ah
        shlb $7, %al
        movq $2, %r11
        mulq %r11
        movq %r11, %rax
        incq %rax
        /* lock cmpxchg %r11, %rax */
        /* lock incq %rax */
        ret
