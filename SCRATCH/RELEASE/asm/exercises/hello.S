; .section __TEXT,__text

.globl _hello

_hello:
    movl $0x2000001, %eax
    movl $42, %edi
    syscall
