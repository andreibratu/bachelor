bits 32
; a*b-c
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db -2
    b db -3
    c  db -4

segment code use32 class=code
    start:
        mov al, [a]
        imul byte [b]
        
        mov bx, ax
        mov al, [c]
        cbw
        
        sub bx, ax
        
        push    dword 0
        call    [exit]

; endians 
