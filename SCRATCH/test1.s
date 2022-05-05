	.text
	.p2align 4
	.globl _f
_f:
LFB585:
	movq	8(%rdi), %rdi
	jmp	_puts
LFE585:
	.p2align 4
	.globl _is_multiple_of_100_ex
_is_multiple_of_100_ex:
LFB587:
	imull	$42949673, %edi, %edi
	addl	$21474832, %edi
	cmpl	$42949668, %edi
	setbe	%al
	ret
LFE587:
	.p2align 4
	.globl _is_multiple_100
_is_multiple_100:
LFB588:
	imull	$-1030792151, %edi, %edi
	addl	$85899344, %edi
	rorl	$2, %edi
	cmpl	$42949672, %edi
	setbe	%al
	ret
LFE588:
	.p2align 4
	.globl _is_leap
_is_leap:
LFB589:
	imull	$42949673, %edi, %eax
	addl	$21474832, %eax
	cmpl	$42949669, %eax
	sbbl	%eax, %eax
	andl	$12, %eax
	addl	$3, %eax
	testl	%edi, %eax
	sete	%al
	ret
LFE589:
	.p2align 4
	.globl _last_day_of_mon
_last_day_of_mon:
LFB590:
	cmpl	$2, %esi
	je	L9
	movl	%esi, %eax
	sarl	$3, %eax
	xorl	%esi, %eax
	orl	$30, %eax
	ret
	.p2align 4,,10
	.p2align 3
L9:
	imull	$42949673, %edi, %eax
	addl	$21474832, %eax
	cmpl	$42949669, %eax
	sbbl	%eax, %eax
	andl	$12, %eax
	addl	$3, %eax
	andl	%edi, %eax
	cmpl	$1, %eax
	movl	$28, %eax
	adcl	$0, %eax
	ret
LFE590:
	.cstring
lC0:
	.ascii "%d\12\0"
lC1:
	.ascii "t %d\12\0"
lC2:
	.ascii "tx %d\12\0"
lC3:
	.ascii "test\0"
lC4:
	.ascii "1\0"
lC5:
	.ascii "0\0"
	.section __TEXT,__text_startup,regular,pure_instructions
	.p2align 4
	.globl _main
_main:
LFB591:
	pushq	%rbp
LCFI0:
	leaq	lC0(%rip), %rdi
	movl	$31, %esi
	xorl	%eax, %eax
	leaq	lC1(%rip), %rbp
	subq	$32, %rsp
LCFI1:
	call	_printf
	movq	%rbp, %rdi
	movl	$1, %esi
	xorl	%eax, %eax
	call	_printf
	movq	%rbp, %rdi
	movl	$9, %esi
	xorl	%eax, %eax
	call	_printf
	movq	%rbp, %rdi
	movl	$30, %esi
	xorl	%eax, %eax
	call	_printf
	movl	$3, %esi
	xorl	%eax, %eax
	leaq	lC2(%rip), %rdi
	call	_printf
	leaq	lC3(%rip), %rdi
	call	_puts
	leaq	_f(%rip), %rax
	movq	%rax, (%rsp)
	leaq	lC4(%rip), %rdi
	movq	%rax, 16(%rsp)
	leaq	lC5(%rip), %rax
	movq	%rdi, 8(%rsp)
	movq	%rax, 24(%rsp)
	call	_puts
	leaq	16(%rsp), %rdi
	call	*16(%rsp)
	addq	$32, %rsp
LCFI2:
	xorl	%eax, %eax
	popq	%rbp
LCFI3:
	ret
LFE591:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB585-.
	.set L$set$2,LFE585-LFB585
	.quad L$set$2
	.uleb128 0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB587-.
	.set L$set$4,LFE587-LFB587
	.quad L$set$4
	.uleb128 0
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$5,LEFDE5-LASFDE5
	.long L$set$5
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB588-.
	.set L$set$6,LFE588-LFB588
	.quad L$set$6
	.uleb128 0
	.align 3
LEFDE5:
LSFDE7:
	.set L$set$7,LEFDE7-LASFDE7
	.long L$set$7
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB589-.
	.set L$set$8,LFE589-LFB589
	.quad L$set$8
	.uleb128 0
	.align 3
LEFDE7:
LSFDE9:
	.set L$set$9,LEFDE9-LASFDE9
	.long L$set$9
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB590-.
	.set L$set$10,LFE590-LFB590
	.quad L$set$10
	.uleb128 0
	.align 3
LEFDE9:
LSFDE11:
	.set L$set$11,LEFDE11-LASFDE11
	.long L$set$11
LASFDE11:
	.long	LASFDE11-EH_frame1
	.quad	LFB591-.
	.set L$set$12,LFE591-LFB591
	.quad L$set$12
	.uleb128 0
	.byte	0x4
	.set L$set$13,LCFI0-LFB591
	.long L$set$13
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$14,LCFI1-LCFI0
	.long L$set$14
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.set L$set$15,LCFI2-LCFI1
	.long L$set$15
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$16,LCFI3-LCFI2
	.long L$set$16
	.byte	0xe
	.uleb128 0x8
	.align 3
LEFDE11:
	.ident	"GCC: (Homebrew GCC 11.3.0) 11.3.0"
	.subsections_via_symbols
