#define BUFFERSIZE 2046

.globl _my_func 

_my_func:
rdrand 
mov %rdi, %rax 
mov $1, %cl
shl %cl, %rax
cmp $4, %rax 
neg %rax


.jmp1:
inc %rax
//test %rax, %rax 
jnz .jmp1

.jmp2:
xor $1, %rax
// setl %al
ret

