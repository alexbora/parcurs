
.global _leapyear

_leapyear:
    push	%rbx 
    push	%rcx
    push	%rdx
    mov		%rdi, %rax
    xor		%rcx, %rcx 
    test	$3, %rax  
    jnz		.loop      
    inc		%rcx    
    xor		%rdx, %rdx
    mov		$100, %rbx
    div		%rbx
    and		%rdx, %rdx
    jnz		.loop      
    test	$3, %rax
    jz		.loop     
    dec		%rcx   
.loop:
    mov		%rcx, %rax
    pop		%rdx
    pop		%rcx
    pop		%rbx
    ret
