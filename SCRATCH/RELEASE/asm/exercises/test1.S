.global _test1 

_test1: 
; xor %rax, %rax 
mov $3, %rax
mov $4, %r10 
add %r10, %rax
mov %rdi, %rax
shl %rax
add $100, %rax
mov $3, %ax
; addq $1, %rax
; dec %rax 
; repnz
retq 
