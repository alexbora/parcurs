	.text
	.p2align 4
	.globl _res
_res:
LFB3:
	movslq	%edi, %rax
	movl	%edi, %edx
	imulq	$715827883, %rax, %rax
	sarl	$31, %edx
	shrq	$32, %rax
	subl	%edx, %eax
	leal	(%rax,%rax,2), %edx
	movl	%edi, %eax
	addl	%edx, %edx
	subl	%edx, %eax
	ret
LFE3:
	.p2align 4
	.globl _res2
_res2:
LFB4:
	leal	-1(%rdi), %eax
	cmpl	$4, %eax
	movl	$0, %eax
	cmovbe	%edi, %eax
	ret
LFE4:
	.section __TEXT,__text_startup,regular,pure_instructions
	.p2align 4
	.globl _main
_main:
LFB5:
	xorl	%eax, %eax
	ret
LFE5:
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
	.quad	LFB3-.
	.set L$set$2,LFE3-LFB3
	.quad L$set$2
	.uleb128 0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB4-.
	.set L$set$4,LFE4-LFB4
	.quad L$set$4
	.uleb128 0
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$5,LEFDE5-LASFDE5
	.long L$set$5
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB5-.
	.set L$set$6,LFE5-LFB5
	.quad L$set$6
	.uleb128 0
	.align 3
LEFDE5:
	.ident	"GCC: (Homebrew GCC 11.3.0_2) 11.3.0"
	.subsections_via_symbols
