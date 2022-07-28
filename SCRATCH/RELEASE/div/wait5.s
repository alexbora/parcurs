.globl main

.data 

tim: 
.quad 0 


main:
movq $0xc9, %rax 
syscall
enter $0, $0
//call printf
leave

retq
