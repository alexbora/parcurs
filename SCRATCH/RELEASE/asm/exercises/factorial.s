        .globl _factorial

        .equ LOCAL, -8

_factorial:
        enter $16, $0
        cmpq $1, %rdi
        jne _continue
        movq $1, %rax
        leave
        ret
_continue:
        movq %rdi, LOCAL(%rbp)
        decq %rdi
        call _factorial
        mulq LOCAL(%rbp)

        leave
        ret
