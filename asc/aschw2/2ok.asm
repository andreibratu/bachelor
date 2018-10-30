bits 32

global start        


extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 78
    b dw 12
    c dw 56
    d dw 3
    res dw 0
    
segment code use32 class=code
    start:
        ; b+a-(4-d+2)+c+(a-b)
        mov ax, [a]
        mov bx, [b]
        mov cx, [c]
        mov dx, [d]
        
        add bx, ax ; b + a
       
        sub bx, 6 ; b + a - 6
        add bx, dx ; b + a - 6 + d
        
        add bx, cx ; b + a - 6 + d + c
        add bx, ax ; b + a - 6 + d + c + a
        sub bx, [b] ; b + a - 6 + d - b, bx was overriden
        
        mov [res], bx
        
        push    dword 0
        call    [exit]
