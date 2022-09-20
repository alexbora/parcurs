//#ifndef VAR
  //  .abort "You must define VAR to assemble this file."
//#endif

.align 4 
.global _main 

.equ WEIGHT_OFFSET, 0
.equ HAIR_OFFSET, 8
.equ HEIGHT_OFFSET, 16
.equ AGE_OFFSET, 24

one:    
.quad 4
mynumbers:
    .quad 5, 20, 33, 80, 52, 10, 1

.asciz "%s has changes.\tSave them?"
//.section __TEXT,__text,regular,pure_instructions

.equ KNOWS_PROGRAMMING, 0b1
.equ KNOWS_CHEMISTRY, 0b10
.equ KNOWS_PHYSICS, 0b100

.text


_main: 
//movq %mynumbers, %rbx
xorb %al, %al
orb $0b00000001, %al
andb $0b11111110, %al
testb $0b0000001, %al
movq $(KNOWS_PROGRAMMING|KNOWS_PHYSICS), %rax
jz _bitwasset

movb $'a', %al
xchgb %al, %ah
movb $'a', %al
movq $60, %rax
movq $2, %rdi 
addq %rdi, %rax
mulq %rdi
syscall
retq

_bitwasset: 
retq 
