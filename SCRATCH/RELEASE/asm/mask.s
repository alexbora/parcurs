
        .text
        .p2align 4
        .globl _xx
_xx:
LFB4:
        cmpl	$6, %edi
        sbbl	%eax, %eax
        orl	$2, %eax
        andl	%edi, %eax
        ret
LFE4:
        .cstring
lC0:
        .ascii "%d %s\12\0"
        .section __TEXT, __text_startup, regular, pure_instructions
        .p2align 4
        .globl _main
_main:
LFB5:
        subq	$280, %rsp
LCFI0:
        movl	$16, %edi
        call	_malloc
        movl	$16, %ecx
        xorl	%edx, %edx
        movl	$16, %esi
        movq	%rax, %rdi
        call	_memset_s
        leaq	16(%rsp), %rdx
        movq	_memset@GOTPCREL(%rip), %rax
        movl	$97, %esi
        leaq	lC0(%rip), %rdi
        movb	$97, 18(%rsp)
        movq	%rax, 8(%rsp)
        movl	$24929, %eax
        movw	%ax, 16(%rsp)
        xorl	%eax, %eax
        call	_printf
        xorl	%eax, %eax
        addq	$280, %rsp
LCFI1:
        ret
LFE5:
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
        .align 3
LEFDE1:
LSFDE3:
        .set L$set$3, LEFDE3-LASFDE3
        .long L$set$3
LASFDE3:
        .long	LASFDE3-EH_frame1
        .quad	LFB5-.
        .set L$set$4, LFE5-LFB5
        .quad L$set$4
        .uleb128 0
        .byte	0x4
        .set L$set$5, LCFI0-LFB5
        .long L$set$5
        .byte	0xe
        .uleb128 0x120
        .byte	0x4
        .set L$set$6, LCFI1-LCFI0
        .long L$set$6
        .byte	0xe
        .uleb128 0x8
        .align 3
LEFDE3:
        .ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
        .subsections_via_symbols