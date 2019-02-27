bits 32
; (a*d+e)/[c+h/(c-b)]

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 13
    b db 7
    c db 17
    d db 5
    e dw 134
    h dw 78
    divisor db 0
    dividend dw 0
    quotient db 0
    remainder db 0


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
        mov [quotient], ax
        mov [remainder], dx

        
        push    dword 0
        call    [exit]