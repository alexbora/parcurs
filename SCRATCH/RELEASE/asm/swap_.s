        .text
        .p2align 4
        .globl _SwapSHORT
_SwapSHORT:
LFB4:
        movl	%edi, %eax
        rolw	$8, %ax
        ret
LFE4:
        .section __TEXT, __text_startup, regular, pure_instructions
        .p2align 4
        .globl _main
_main:
LFB5:
        xorl	%eax, %eax
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
        .align 3
LEFDE3:
        .ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
        .subsections_via_symbols
