.global _days

_days:
    mov     %rdi, %rax
    mov     %al, %ah
    shr     $3, %ah
    xor     %al, %ah 
    and     $1, %ah 
    or      $28, %ah 
    dec     %al    
    dec     %al
    or      $0xF0, %al
    dec     %al  
    shr     $3, %al 
    and     $2, %al 
    or      %al, %ah
    shr     $8, %ax 
    ret 
