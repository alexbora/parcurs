	.text
_mul:
LFB507:
	pushq	%rbp
LCFI0:
	movq	%rsp, %rbp
LCFI1:
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movdqa	(%rax), %xmm0
	movaps	%xmm0, -16(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -24(%rbp)
	movdqa	-16(%rbp), %xmm0
	movaps	%xmm0, -48(%rbp)
	movq	-24(%rbp), %rax
	movdqa	-48(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	nop
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	popq	%rbp
LCFI2:
	ret
LFE507:
_mul2:
LFB508:
	pushq	%rbp
LCFI3:
	movq	%rsp, %rbp
LCFI4:
	movdqa	lC0(%rip), %xmm0
	movaps	%xmm0, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movdqa	(%rax), %xmm0
	movaps	%xmm0, -16(%rbp)
	nop
	popq	%rbp
LCFI5:
	ret
LFE508:
	.cstring
lC1:
	.ascii "%lld\12\0"
	.text
	.globl _main
_main:
LFB509:
	pushq	%rbp
LCFI6:
	movq	%rsp, %rbp
LCFI7:
	subq	$32, %rsp
	leaq	-32(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_mul
	movq	-32(%rbp), %rdx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	leaq	lC1(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	_fprintf
	movl	$0, %eax
	leave
LCFI8:
	ret
LFE509:
	.literal16
	.align 4
lC0:
	.quad	9
	.quad	1
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
	.quad	LFB507-.
	.set L$set$2,LFE507-LFB507
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB507
	.long L$set$3
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$6,LEFDE3-LASFDE3
	.long L$set$6
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB508-.
	.set L$set$7,LFE508-LFB508
	.quad L$set$7
	.uleb128 0
	.byte	0x4
	.set L$set$8,LCFI3-LFB508
	.long L$set$8
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$9,LCFI4-LCFI3
	.long L$set$9
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$10,LCFI5-LCFI4
	.long L$set$10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$11,LEFDE5-LASFDE5
	.long L$set$11
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB509-.
	.set L$set$12,LFE509-LFB509
	.quad L$set$12
	.uleb128 0
	.byte	0x4
	.set L$set$13,LCFI6-LFB509
	.long L$set$13
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$14,LCFI7-LCFI6
	.long L$set$14
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$15,LCFI8-LCFI7
	.long L$set$15
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE5:
	.ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
	.subsections_via_symbols
