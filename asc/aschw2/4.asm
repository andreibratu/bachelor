bits 32
; 200-[3*(c+b-d/a)-300]

global start        

extern exit
import exit msvcrt.dll
; 200-[3*(c+b-d/a)-300]

segment data use32 class=data
    a db 14
    b db 7
    c db 4
    d dw 17
    ct db 0
    res dw 0

segment code use32 class=code
    start:
        ; d/a
        mov ax, [d]
        div byte [a]
        
        ; (c+b-d/a)
        mov ah, [c]
        add ah, [b]
        sub ah, al
        
        ; 3*(c+b-d/a)
        mov al, ah
        mov [ct], byte 3
        mul byte [ct]
        
        ; 200-[3*(c+b-d/a)-300]
        sub ax, 300
        mov [ct], byte 200
        sub [ct], ax
        
        mov ax, [ct]
        mov [res], ax
        
        push dword 0      
        call    [exit]
