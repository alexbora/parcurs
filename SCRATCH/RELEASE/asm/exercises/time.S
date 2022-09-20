bits 64
section .text
global _ti 


%DEFINE SYS_TIME 0x2000074

_ti:
  mov     rax, SYS_TIME ;201         ; system call 0xC9(201) = sys_time
  xor     rdi, rdi         ; address of long long (qword) set to zero
  syscall                  ; make Linux system call

        ; Do something useful with time
        ; Seconds since 1970-01-01 00:00:00 +0000 (UTC)

        ; Exit with the time
  mov     rdi, rax         ; return least sig byte of time as return code
  ; mov     rax, 60          ; system call 0x3C(60) is exit
  syscall                  ; make Linux system 
  ret
