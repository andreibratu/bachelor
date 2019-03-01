bits 32 ; assembling for the 32 bits architecture

global start        

extern exit
import exit msvcrt.dll


segment data use32 class=data
    a dd 1, 2, 3, 4
    len equ ($-a)/4


segment code use32 class=code
    start:
        mov ecx, len
        mov esi, a
        mov ebx, 0
        cld
        
        bucla:
            lodsb
            add ebx, eax
            loop bucla
        
        push    dword 0
        call    [exit]
