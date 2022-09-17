        .global _main

_main:

        movl	$1, %eax
        rolw	$8, %ax
        /* shrw $1, %ax */
        ret

        /* movl %ebx, %ecx */
        /* shrl $8, %ebx */
        /* orl %ebx, %ecx */
        /* movl %ecx, %eax */
        /* ret */

