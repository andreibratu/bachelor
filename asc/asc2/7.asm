bits 32
; [(e+f-g}+(b+c)*3]/5

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    b db 45
    c db 23
    e dw 100
    f dw 37
    g dw 147
    ct1 db 3
    ct2 db 5
    quotient db 0
    remainder db 0

segment code use32 class=code
    start:
        mov al, [b]
        add al, [c]
        mul byte [ct1]
        add ax, [e]
        add ax, [f]
        sub ax, [g]
        
        div byte [ct2]
        mov [quotient], al
        mov [remainder], ah
        
        push    dword 0
        call    [exit]
