bits 32
; (a*d+e)/[c+h/(c-b)]

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 24
    b db 13
    c db 51
    d db 16
    e dw 32
    h dw 64
    divisor db 0
    quot db 0
    rem db 0
    
segment code use32 class=code
    start:
        mov ax, [h]
        mov bl, [c]
        sub bl, [b]
        div byte bl
        add al, [c]
        mov [divisor], al
        
        mov al, [a]
        mul byte [d]
        add ax, [e]
        
        div byte [divisor]
        mov [quot], al
        mov [rem], ah
        
        push    dword 0
        call    [exit]
