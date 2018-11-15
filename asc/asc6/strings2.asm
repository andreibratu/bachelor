bits 32 ; assembling for the 32 bits architecture

global start        

extern exit
import exit msvcrt.dll

; b[i] <- a[i]

segment data use32 class=data
    a dd 1, 2, 3, 4
    len equ ($-a)/4
    b times len dd 0
    


segment code use32 class=code
    start:
        cld
        mov esi, a
        mov edi, b
        mov ecx, len
        
        qw:
            ; lodsd ; eax <- [esi]
            ; stosd ; [edi] <- eax
            movsdbits 32 ; assembling for the 32 bits architecture

global start        

extern exit
import exit msvcrt.dll


segment data use32 class=data



segment code use32 class=code
    start:
    
        push    dword 0
        call    [exit]

            loop qw
        
        push    dword 0
        call    [exit]
