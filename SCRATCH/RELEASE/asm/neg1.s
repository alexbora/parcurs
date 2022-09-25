	.text
	.p2align 4
	.globl _a
_a:
LFB4:
	xorl	%eax, %eax
	cmpl	$5, %edi
	seta	%al
	leal	-1(%rax), %edx
	negl	%eax
	andl	%edi, %edx
	andl	$5, %eax
	orl	%edx, %eax
	ret
LFE4:
	.p2align 4
	.globl _b
_b:
LFB5:
	movl	$5, %eax
	cmpl	%eax, %edi
	cmovbe	%edi, %eax
	ret
LFE5:
	.p2align 4
	.globl _c
_c:
LFB6:
	xorl	%eax, %eax
	cmpl	$5, %edi
	movl	%edi, -8(%rsp)
	seta	%al
	movl	$5, -4(%rsp)
	movl	-8(%rsp,%rax,4), %eax
	ret
LFE6:
	.p2align 4
	.globl _d
_d:
LFB11:
	movl	$5, %eax
	cmpl	%eax, %edi
	cmovbe	%edi, %eax
	ret
LFE11:
	.p2align 4
	.globl _e
_e:
LFB8:
	movl	%edi, %eax
	andl	$31, %eax
	ret
LFE8:
	.cstring
lC0:
	.ascii "%d\12\0"
	.section __TEXT,__text_startup,regular,pure_instructions
	.p2align 4
	.globl _main
_main:
LFB9:
	subq	$8, %rsp
LCFI0:
	movl	$5, %esi
	xorl	%eax, %eax
	leaq	lC0(%rip), %rdi
	call	_printf
	xorl	%eax, %eax
	addq	$8, %rsp
LCFI1:
	ret
LFE9:
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
	.quad	LFB4-.
	.set L$set$2,LFE4-LFB4
	.quad L$set$2
	.uleb128 0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB5-.
	.set L$set$4,LFE5-LFB5
	.quad L$set$4
	.uleb128 0
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$5,LEFDE5-LASFDE5
	.long L$set$5
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB6-.
	.set L$set$6,LFE6-LFB6
	.quad L$set$6
	.uleb128 0
	.align 3
LEFDE5:
LSFDE7:
	.set L$set$7,LEFDE7-LASFDE7
	.long L$set$7
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB11-.
	.set L$set$8,LFE11-LFB11
	.quad L$set$8
	.uleb128 0
	.align 3
LEFDE7:
LSFDE9:
	.set L$set$9,LEFDE9-LASFDE9
	.long L$set$9
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB8-.
	.set L$set$10,LFE8-LFB8
	.quad L$set$10
	.uleb128 0
	.align 3
LEFDE9:
LSFDE11:
	.set L$set$11,LEFDE11-LASFDE11
	.long L$set$11
LASFDE11:
	.long	LASFDE11-EH_frame1
	.quad	LFB9-.
	.set L$set$12,LFE9-LFB9
	.quad L$set$12
	.uleb128 0
	.byte	0x4
	.set L$set$13,LCFI0-LFB9
	.long L$set$13
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$14,LCFI1-LCFI0
	.long L$set$14
	.byte	0xe
	.uleb128 0x8
	.align 3
LEFDE11:
	.ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
	.subsections_via_symbols
