

.globl test 
.extern printf 




test:
xorb %al, %al
//test $0b10000, %rdi
//movb %dil, %alleaq format(%rip), %rdleaq format(%rip), %rdi
andq $0b10000, %rdi 
movq %rdi, %rsi
leaq .LC1(%rip), %rdi
pushq %rbx
call printf
popq %rbx
retq

.data
    .LC1: .string "%d\n"

