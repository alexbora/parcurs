.global _test, _asmfunc, _mask 

.data
  format: .asciz "%d\n"
  msg: .asciz "a very inspired message!\n"

.text
_test:
  jmp _mask
  push %rbx
  leaq format(%rip), %rdi

  lahf
  movb %ah, %al  
  movb %al, %sil
  mov $0b111, %esi           # Writing to ESI zero extends to RSI.
  xorq %rax, %rax          # Zeroing EAX is efficient way to clear AL.
  call _printf
  pop %rbx
  jmp _asmfunc
  ret

_asmfunc:
  leaq msg(%rip), %rdi
  xorq %rax,%rax
  call _printf
  retq 

_mask: 
jmp .mask2
  //movq $(0b10000 | %rdi), %rax
  //shrq $4, %rdi   
  //andq $0b10000, %rdi
  //testq $0b10000, %rdi 
  //jnz .mask2
  //xorq %rax, %rax  
  //retq 
.mask2:   
//movq %rdi, %rax
movq $-1, %rcx
//xorq %rcx, %rcx
movq msg(%rip), %rdi 
movb $'a', %al 
repne scasb 
subq msg(%rip), %rdi 
decq %rdi 
//decq %rcx
mov %rdi, %rax
retq 
