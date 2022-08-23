        .global _main, myval, OFFSET

        .data
myval:
        .double 4

        .equ OFFSET, -8

        .text

_main:
        movq $6, OFFSET(%rbp)
        call _print_float
        ret
