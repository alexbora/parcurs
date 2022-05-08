	.file	"date_ex.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Usage: <mon> <year> <km>\ne.g. iun 22 80000\n"
	.align 8
.LC1:
	.string	"/usr/share/zoneinfo/Europe/Bucharest"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"TZ"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"ian feb mar apr mai iun iul aug sep oct noi dec"
	.section	.rodata.str1.1
.LC5:
	.string	"%02d.%02d.%d"
.LC6:
	.string	"Today is           %s"
	.section	.rodata
	.align 8
.LC7:
	.string	"ianuarie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"februarie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"martie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"aprilie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"mai"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"iunie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"iulie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"august"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"septembrie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"octombrie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"noiembrie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"decembrie"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.section	.rodata.str1.8
	.align 8
.LC20:
	.string	"current: %s\t last month: %s\t days of last mo: %d\n"
	.section	.rodata.str1.1
.LC21:
	.string	"past: %d\n"
.LC22:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$96, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	cmpl	$1, %edi
	jle	.L2
	movq	8(%rsi), %rax
	movq	%rsi, %r12
	movzbl	(%rax), %edx
	cmpb	$104, %dl
	je	.L3
	movl	%edi, %ebx
	cmpb	$45, %dl
	jne	.L4
	movzbl	1(%rax), %edx
	cmpl	$104, %edx
	je	.L50
	cmpl	$45, %edx
	jne	.L4
	cmpb	$104, 2(%rax)
	jne	.L4
	cmpb	$0, 3(%rax)
	je	.L3
	.p2align 4,,10
	.p2align 3
.L4:
	movl	$1, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	setenv
	xorl	%edi, %edi
	call	time
	movq	%rax, ti(%rip)
	cmpl	$2, %ebx
	jne	.L51
.L6:
	xorl	%edi, %edi
	call	time
	leaq	16(%rsp), %rdi
	movq	%rax, 16(%rsp)
	leaq	32(%rsp), %r12
	call	localtime
	movq	%rax, %rsi
	movl	$14, %ecx
	movq	%r12, %rdi
	rep movsl
	xorl	%edi, %edi
	call	time
	leaq	24(%rsp), %rdi
	movq	%rax, 24(%rsp)
	call	localtime
	movq	%rax, %rdi
	call	asctime
	movq	%rax, %rsi
	movl	$.LC6, %edi
	xorl	%eax, %eax
	call	printf
	movl	48(%rsp), %eax
	movl	44(%rsp), %edx
	leal	1(%rax), %ecx
	movl	52(%rsp), %eax
	movl	$.LC5, %esi
	leal	1900(%rax), %r8d
	movl	$longdate, %edi
	xorl	%eax, %eax
	call	sprintf
	movl	48(%rsp), %eax
	movl	$1, 44(%rsp)
	decl	%eax
	cmpl	$11, %eax
	movl	%eax, 48(%rsp)
	movl	52(%rsp), %eax
	je	.L12
.L13:
	movq	%r12, %rdi
	movl	%eax, 52(%rsp)
	call	mktime
	movq	ti(%rip), %rax
	movl	$TM, %edi
	movl	$14, %ecx
	movq	%r12, %rsi
	rep movsl
	cqto
	movl	$86400, %ecx
	idivq	%rcx
	movl	%eax, days_past(%rip)
.L11:
	movl	TM+16(%rip), %edx
	movl	TM+20(%rip), %ecx
	movl	%edx, %r9d
	sall	$4, %r9d
	movslq	%r9d, %r9
	addq	$.LC7, %r9
	movq	%r9, luna(%rip)
	leal	1(%rdx), %eax
	cmpl	$1, %edx
	je	.L14
	movl	%eax, %r8d
	sarl	$3, %r8d
	xorl	%eax, %r8d
	orl	$30, %r8d
	movl	%r8d, dayz(%rip)
	jle	.L16
	movl	days_past(%rip), %esi
	movl	%r8d, %edx
	cmpl	$7, %r8d
	jle	.L27
	vmovd	%esi, %xmm1
	vpbroadcastd	%xmm1, %ymm1
	vpaddd	.LC8(%rip), %ymm1, %ymm6
	vmovdqa	.LC9(%rip), %ymm2
	vpsrlq	$32, %ymm6, %ymm5
	vpmuldq	%ymm2, %ymm6, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm5
	vmovdqa	.LC10(%rip), %ymm3
	vmovdqa	.LC11(%rip), %ymm4
	movl	%r8d, %eax
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm5, %ymm5
	vpor	%ymm5, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm6, %ymm0
	vpsrad	$31, %ymm6, %ymm5
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm5
	vpsubd	%ymm0, %ymm5, %ymm5
	vpsubd	%ymm5, %ymm6, %ymm0
	shrl	$3, %eax
	vmovdqa	%ymm0, arr(%rip)
	cmpl	$1, %eax
	je	.L22
	vpaddd	.LC12(%rip), %ymm1, %ymm6
	vpsrlq	$32, %ymm6, %ymm5
	vpmuldq	%ymm2, %ymm6, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm5
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm5, %ymm5
	vpor	%ymm5, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm6, %ymm0
	vpsrad	$31, %ymm6, %ymm5
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm5
	vpsubd	%ymm0, %ymm5, %ymm0
	vpsubd	%ymm0, %ymm6, %ymm0
	vmovdqa	%ymm0, arr+32(%rip)
	cmpl	$2, %eax
	jne	.L26
	.p2align 4,,10
	.p2align 3
.L22:
	sall	$3, %eax
	movl	%eax, %ecx
	cmpl	%edx, %eax
	je	.L52
	vzeroupper
.L21:
	subl	%eax, %edx
	leal	-1(%rdx), %edi
	cmpl	$2, %edi
	jbe	.L24
	vmovd	%ecx, %xmm7
	vpshufd	$0, %xmm7, %xmm0
	vpaddd	.LC15(%rip), %xmm0, %xmm0
	vmovd	%esi, %xmm7
	vpshufd	$0, %xmm7, %xmm1
	vpaddd	%xmm1, %xmm0, %xmm0
	vpaddd	.LC16(%rip), %xmm0, %xmm0
	vmovdqa	.LC17(%rip), %xmm3
	vpsrlq	$32, %xmm0, %xmm2
	vpmuldq	%xmm3, %xmm0, %xmm1
	vpmuldq	%xmm3, %xmm2, %xmm2
	vpshufb	.LC18(%rip), %xmm1, %xmm1
	vpshufb	.LC19(%rip), %xmm2, %xmm2
	vpor	%xmm2, %xmm1, %xmm1
	vpaddd	%xmm1, %xmm0, %xmm1
	vpsrad	$31, %xmm0, %xmm2
	vpsrad	$2, %xmm1, %xmm1
	vpsubd	%xmm2, %xmm1, %xmm1
	vpslld	$3, %xmm1, %xmm2
	vpsubd	%xmm1, %xmm2, %xmm1
	vpsubd	%xmm1, %xmm0, %xmm0
	vmovdqa	%xmm0, arr(,%rax,4)
	movl	%edx, %eax
	andl	$-4, %eax
	addl	%eax, %ecx
	cmpl	%eax, %edx
	je	.L16
.L24:
	leal	4(%rsi,%rcx), %eax
	movl	$7, %edi
	cltd
	idivl	%edi
	movslq	%ecx, %r10
	leal	1(%rcx), %eax
	movl	%edx, arr(,%r10,4)
	cmpl	%r8d, %eax
	jge	.L16
	movslq	%eax, %r10
	leal	4(%rsi,%rax), %eax
	cltd
	idivl	%edi
	addl	$2, %ecx
	movl	%edx, arr(,%r10,4)
	cmpl	%r8d, %ecx
	jge	.L16
	leal	4(%rsi,%rcx), %eax
	cltd
	idivl	%edi
	movslq	%ecx, %r10
	movl	%edx, arr(,%r10,4)
.L16:
	movl	%r8d, %ecx
	movq	%r9, %rdx
	movl	$longdate, %esi
	movl	$.LC20, %edi
	xorl	%eax, %eax
	call	printf
	movl	days_past(%rip), %esi
	movl	$.LC21, %edi
	xorl	%eax, %eax
	call	printf
	movl	arr(%rip), %esi
	movl	$.LC22, %edi
	xorl	%eax, %eax
	call	printf
	movl	arr+4(%rip), %esi
	movl	$.LC22, %edi
	xorl	%eax, %eax
	call	printf
	movl	arr+8(%rip), %esi
	movl	$.LC22, %edi
	xorl	%eax, %eax
	call	printf
	leaq	-24(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	xorl	%eax, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L51:
	.cfi_restore_state
	movq	8(%r12), %rsi
	movl	$.LC3, %edi
	call	strstr
	subq	$.LC3, %rax
	movl	$4, %ecx
	cqto
	idivq	%rcx
	movq	16(%r12), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	leaq	32(%rsp), %r13
	movq	%rax, %rbx
	call	strtol
	leal	2000(%rax), %r12d
	leaq	56(%rsp), %rdi
	xorl	%eax, %eax
	movl	$8, %ecx
	rep stosl
	vmovdqa	.LC4(%rip), %xmm0
	vmovd	%ebx, %xmm4
	vmovdqa	%xmm0, 32(%rsp)
	movq	%r13, %rdi
	vpinsrd	$1, %r12d, %xmm4, %xmm0
	vmovq	%xmm0, 48(%rsp)
	call	mktime
	movl	48(%rsp), %eax
	movl	52(%rsp), %r8d
	movl	44(%rsp), %edx
	leal	1(%rax), %ecx
	movl	$.LC5, %esi
	movl	$longdate, %edi
	xorl	%eax, %eax
	call	sprintf
	movl	$TM, %edi
	movl	$14, %ecx
	movq	%r13, %rsi
	rep movsl
	leal	1(%rbx), %esi
	xorl	%eax, %eax
	cmpl	$2, %esi
	setle	%al
	subl	%eax, %r12d
	js	.L53
	movl	%r12d, %eax
	movl	$400, %edi
	cltd
	idivl	%edi
	movl	%eax, %edi
.L8:
	imull	$-400, %edi, %eax
	leal	(%rax,%r12), %r8d
	cmpl	$2, %esi
	jg	.L54
	leal	10(%rbx), %ecx
	imull	$153, %ecx, %ecx
	movl	$5, %esi
	addl	$2, %ecx
	movl	%ecx, %eax
	cltd
	idivl	%esi
	movl	%eax, %ecx
.L10:
	movl	%r8d, %eax
	movl	$4, %r9d
	cltd
	idivl	%r9d
	imull	$365, %r8d, %esi
	movl	$-100, %r9d
	imull	$146097, %edi, %edi
	addl	%eax, %esi
	movl	%r8d, %eax
	cltd
	idivl	%r9d
	addl	%eax, %esi
	addl	%ecx, %esi
	leal	-719468(%rsi,%rdi), %eax
	movl	%eax, days_past(%rip)
	jmp	.L11
.L12:
	decl	%eax
	jmp	.L13
.L14:
	addl	$16000, %ecx
	movl	%ecx, %eax
	movl	$100, %esi
	cltd
	idivl	%esi
	testl	%edx, %edx
	jne	.L55
	andb	$15, %cl
	je	.L20
.L18:
	movl	$28, dayz(%rip)
	movl	days_past(%rip), %esi
	movl	$28, %edx
	movl	$28, %r8d
.L19:
	vmovd	%esi, %xmm1
	vpbroadcastd	%xmm1, %ymm1
	vpaddd	.LC8(%rip), %ymm1, %ymm6
	vmovdqa	.LC9(%rip), %ymm2
	vpsrlq	$32, %ymm6, %ymm5
	vpmuldq	%ymm2, %ymm6, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm5
	vmovdqa	.LC10(%rip), %ymm3
	vmovdqa	.LC11(%rip), %ymm4
	movl	$3, %eax
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm5, %ymm5
	vpor	%ymm5, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm6, %ymm0
	vpsrad	$31, %ymm6, %ymm5
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm5
	vpsubd	%ymm0, %ymm5, %ymm5
	vpsubd	%ymm5, %ymm6, %ymm0
	vpaddd	.LC12(%rip), %ymm1, %ymm6
	vmovdqa	%ymm0, arr(%rip)
	vpsrlq	$32, %ymm6, %ymm5
	vpmuldq	%ymm2, %ymm6, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm5
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm5, %ymm5
	vpor	%ymm5, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm6, %ymm0
	vpsrad	$31, %ymm6, %ymm5
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm5
	vpsubd	%ymm0, %ymm5, %ymm5
	vpsubd	%ymm5, %ymm6, %ymm0
	vmovdqa	%ymm0, arr+32(%rip)
.L26:
	vpaddd	.LC13(%rip), %ymm1, %ymm6
	vpsrlq	$32, %ymm6, %ymm5
	vpmuldq	%ymm2, %ymm6, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm5
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm5, %ymm5
	vpor	%ymm5, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm6, %ymm0
	vpsrad	$31, %ymm6, %ymm5
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm5
	vpsubd	%ymm0, %ymm5, %ymm5
	vpsubd	%ymm5, %ymm6, %ymm0
	vmovdqa	%ymm0, arr+64(%rip)
	cmpl	$3, %eax
	je	.L22
	vpaddd	.LC14(%rip), %ymm1, %ymm1
	vpsrlq	$32, %ymm1, %ymm5
	vpmuldq	%ymm2, %ymm1, %ymm0
	vpmuldq	%ymm2, %ymm5, %ymm2
	vpshufb	%ymm3, %ymm0, %ymm0
	vpshufb	%ymm4, %ymm2, %ymm2
	vpor	%ymm2, %ymm0, %ymm0
	vpaddd	%ymm0, %ymm1, %ymm0
	vpsrad	$31, %ymm1, %ymm2
	vpsrad	$2, %ymm0, %ymm0
	vpsubd	%ymm2, %ymm0, %ymm0
	vpslld	$3, %ymm0, %ymm2
	vpsubd	%ymm0, %ymm2, %ymm0
	vpsubd	%ymm0, %ymm1, %ymm1
	vmovdqa	%ymm1, arr+96(%rip)
	jmp	.L22
.L2:
	movl	$1, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	setenv
	xorl	%edi, %edi
	call	time
	movq	%rax, ti(%rip)
	jmp	.L6
.L50:
	cmpb	$0, 2(%rax)
	jne	.L4
.L3:
	movl	$.LC0, %edi
	call	puts
	xorl	%edi, %edi
	call	exit
.L55:
	andb	$3, %cl
	jne	.L18
.L20:
	movl	$29, dayz(%rip)
	movl	days_past(%rip), %esi
	movl	$29, %edx
	movl	$29, %r8d
	jmp	.L19
.L54:
	leal	-2(%rbx), %eax
	imull	$153, %eax, %eax
	movl	$5, %ecx
	addl	$2, %eax
	cltd
	idivl	%ecx
	movl	%eax, %ecx
	jmp	.L10
.L27:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	jmp	.L21
.L53:
	leal	-399(%r12), %eax
	movl	$400, %r8d
	cltd
	idivl	%r8d
	movl	%eax, %edi
	jmp	.L8
.L52:
	vzeroupper
	jmp	.L16
	.cfi_endproc
.LFE35:
	.size	main, .-main
	.local	days_past
	.comm	days_past,4,4
	.local	TM
	.comm	TM,56,32
	.local	dayz
	.comm	dayz,4,4
	.local	luna
	.comm	luna,8,8
	.local	longdate
	.comm	longdate,128,32
	.local	arr
	.comm	arr,128,32
	.local	ti
	.comm	ti,8,8
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC4:
	.long	50
	.long	50
	.long	12
	.long	1
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
.LC8:
	.long	4
	.long	5
	.long	6
	.long	7
	.long	8
	.long	9
	.long	10
	.long	11
	.align 32
.LC9:
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.long	-1840700269
	.align 32
.LC10:
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.align 32
.LC11:
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.align 32
.LC12:
	.long	12
	.long	13
	.long	14
	.long	15
	.long	16
	.long	17
	.long	18
	.long	19
	.align 32
.LC13:
	.long	20
	.long	21
	.long	22
	.long	23
	.long	24
	.long	25
	.long	26
	.long	27
	.align 32
.LC14:
	.long	28
	.long	29
	.long	30
	.long	31
	.long	32
	.long	33
	.long	34
	.long	35
	.section	.rodata.cst16
	.align 16
.LC15:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC16:
	.long	4
	.long	4
	.long	4
	.long	4
	.set	.LC17,.LC9
	.set	.LC18,.LC10
	.set	.LC19,.LC11
	.ident	"GCC: (Homebrew GCC 11.3.0) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
