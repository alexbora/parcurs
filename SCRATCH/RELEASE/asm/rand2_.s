        .text
        .globl _main
_main:
LFB4:
        pushq	%rbp
LCFI0:
        movq	%rsp, %rbp
LCFI1:
        subq	$32, %rsp
        movl	%edi, -20(%rbp)
        movq	%rsi, -32(%rbp)
        call	*_random@GOTPCREL(%rip)
        movq	%rax, %rdx
        movq	%rdx, %rax
        sarq	$63, %rax
        shrq	$63, %rax
        addq	%rax, %rdx
        andl	$1, %edx
        subq	%rax, %rdx
        movq	%rdx, %rax
        movl	%eax, -4(%rbp)
        movl	$0, %eax
        leave
LCFI2:
        ret
LFE4:
        .section __TEXT, __eh_frame, coalesced, no_toc+strip_static_syms+live_support
EH_frame1:
        .set L$set$0, LECIE1-LSCIE1
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
        .set L$set$1, LEFDE1-LASFDE1
        .long L$set$1
LASFDE1:
        .long	LASFDE1-EH_frame1
        .quad	LFB4-.
        .set L$set$2, LFE4-LFB4
        .quad L$set$2
        .uleb128 0
        .byte	0x4
        .set L$set$3, LCFI0-LFB4
        .long L$set$3
        .byte	0xe
        .uleb128 0x10
        .byte	0x86
        .uleb128 0x2
        .byte	0x4
        .set L$set$4, LCFI1-LCFI0
        .long L$set$4
        .byte	0xd
        .uleb128 0x6
        .byte	0x4
        .set L$set$5, LCFI2-LCFI1
        .long L$set$5
        .byte	0xc
        .uleb128 0x7
        .uleb128 0x8
        .align 3
LEFDE1:
        .ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
        .subsections_via_symbols
