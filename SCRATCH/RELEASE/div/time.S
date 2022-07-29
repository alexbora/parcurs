.globl main, tim 

.data 
format: .ascii "%s = %d\n\0"
timex: .quad 0
name: .ascii "AAA"

.text
main:
movq $0xc9, %rax 
//xorq %rdi, %rdi
movq $timex, %rdi 
syscall 

//movq %rdi, %rcx 
movq stdout, %rdi
movq $format, %rsi 
movq $name, %rdx
movq timex, %rcx
movq $0, %rax
call fprintf

ret 
