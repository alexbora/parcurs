bits 64 

global _timex

section .data
timeval:
    tv_sec  dq 0
    tv_usec dq 0

timestr db "Secs: %ld and microsecs: %ld", 10, 0

string: db "Connected"
.len: equ-$string

extern _printf

section .text

_timex:
    mov         rax, 0x2000074
    lea         rdi, [rel timeval]
    mov         rsi, 0          
    syscall

    lea         rdi, [rel timestr]     
    mov         rsi, [rel tv_sec]
    mov         rdx, [rel tv_usec]
    call        _printf 
