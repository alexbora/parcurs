        .globl _main, _fprintf

        .bss
        .skip 16

        .data
mytext:
        .ascii "Haha! I intercepted you!\n"
mytextend:

        .incbin "logo.png"

        .zero 1000

        .text
        .balign 16
_main:
        enter $0, $0
        movq $2, %rax
        call *_nop@GOTPCREL(%rip)
        leave
        ret
_nop:
        leaq mytext(%rip), %rsi
        movq $(mytextend - mytext), %rdx
        movq %rdx, %rax
        leave
        ret
