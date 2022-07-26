.globl test, len, value, index1, index2
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

mystring: .ascii "bxai\7\0"




len:
movq $-1, %rcx
xorb %al, %al 
movq %rdi, %r11
repne scasb
subq %r11, %rdi
dec %rdi
movq %rdi, %rax
ret

index1:
movq $0b00010, %rax
movq $0b00010, %rdi
repne scasq
decq %rdi
movq %rdi, %rax
retq

index2:
//movq $-1, %rcx 
movq $4, %rcx
movq $mystring, %rdi 
movb $'a', %al 
repne scasb 
subq $mystring, %rdi 
decq %rdi 
movq %rdi, %rax
ret
