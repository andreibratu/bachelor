bits 32
; d*(d+2*a)/(b*c)

global start        

extern exit               
import exit msvcrt.dll

segment data use32 class=data
    a db 15
    b db 24
    c db 7
    d dw 14
    w dw 0 ; divisor
    res db 0 ; quotient
    rem db 0 ; remainder
    

segment code use32 class=code
    start:
        
        ; b*c
        mov al, [b]
        mul byte [c]
        mov [w], ax
        
        ; d*(d+2*a)
        mov al,  [a]
        mov cl, 2 ; mul by constant not supported
        mul byte cl
        add ax, [d]
        mul word [d]
        
        ; divison
        div word [w]
        mov [res], ax
        mov [rem], dx
        
        push dword 0      
        call    [exit]
