.global _test

_test:
  xor %rax, %rax 
  mov $0x2000004, %rax
  mov $1, %rsi 
  ret 
