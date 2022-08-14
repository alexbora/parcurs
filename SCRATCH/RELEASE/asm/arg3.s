        .globl _start

        .data
numbers:
        .quad 1, 2, 3, 4, 0

        .text

_start:
loopstart:
        enter $16, $0
        movq $0, %rcx
        incq %rcx
        movq numbers(, %rcx, 8), %rax
        cmpq $2, %rax
        je continueloop

continueloop:
        incq %rcx
        movq numbers(, %rcx, 8), %rax
endloop:
        movb %al, %dil
        leave

        movq $60, %rax
        syscall
        ret
        hlt

