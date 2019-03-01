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
       
        not dx
        add dx, 1 ; -d
        add dx,  4 ; 4-d
        add dx, 2 ; 4-d+2
        
        add bx, dx ; b+a-(4-d+2)
        add bx, cx ; b+a-(4-d+2)+c
        
        sub ax, [b] ; a-b
        
        add bx, ax ; b+a-(4-d+2)+c+(a-b)
        
        mov [res], bx
        
        push    dword 0
        call    [exit]
