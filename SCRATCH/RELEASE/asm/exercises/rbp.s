        .global _main
.data 
path: .ascii "/Users/alex/dev/git/\n\0"

.text
_main:
        enter $16, $0
        subq $16, %rsp
        movq $5, -8(%rbp)
        movq -8(%rbp), %rax
call _ch
popq %rbx    
leave
        ret

_ch:
movq $0x0200000c, %rax 
leaq path(%rip), %rdi 
syscall 
ret 
