        .global _cat_new, _dog_new, _cat_destroy, _main, _doThings

        .data
speak_text:
        .ascii "cat\n\0"
speak_verb:
        .ascii "verb\n\0"

cat_vtable_animal:
        .quad _dog_speak
        .quad _cat_speak

dog_vtable_animal:
        .quad _cat_speak
        .quad _dog_speak

        .text
        .p2align 4

_cat_new:
        enter $0, $0
        movq $64, %rdi
        call _malloc
        leave
        ret

_cat_destroy:
        enter $0, $0
        # %rdi already has the address
        call _free
        leave
        ret

_cat_speak:
        enter $0, $0
        movq ___stderrp@GOTPCREL(%rip), %rdi
        movq (%rdi), %rdi
        leaq speak_text(%rip), %rsi
        call _fprintf
        leave
        ret
_dog_speak:
        enter $0, $0
        movq ___stderrp@GOTPCREL(%rip), %rdi
        movq (%rdi), %rdi
        leaq speak_verb(%rip), %rsi
        call _fprintf
        leave
        ret

_dog_new:
        enter $0, $0
        movq $64, %rdi
        call _malloc
        leave
        ret

_doThings:
        enter $16, $0
        movq %rdi, -8(%rbp)
        movq %rsi, -16(%rbp)
        call *0(%rsi)
        leave
        ret

_main:
        enter $128, $0

        call _cat_new
        movq %rax, -8(%rbp)
        movq -8(%rbp), %rdi
        /* leaq cat_vtable_animal+0(%rip), %rsi */
        leaq dog_vtable_animal+0(%rip), %rsi
        call _doThings

        call _dog_new
        movq %rax, -16(%rbp)

        /* call _cat_speak */
        /* call _doThings */
        /* call _cat_destroy */
        leave
        ret
