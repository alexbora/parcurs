	.file	"test2.c"
	.text
	.section	.rodata
.LC0:
	.string	"%lu\n"
.LC1:
	.string	"provide args"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movl	%edi, -164(%rbp)
	movq	%rsi, -176(%rbp)
	nop
	movl	$4096, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	cmpl	$1, -164(%rbp)
	jg	.L2
	movl	$.LC1, %edi
	call	puts
	movl	$0, %eax
	jmp	.L4
.L2:
	movq	-176(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -4(%rbp)
	leaq	-160(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fstat
	movl	$0, %eax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
