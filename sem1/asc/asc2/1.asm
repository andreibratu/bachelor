bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ; a, b, c, d bytes
    d db 100
    a db 15
    b db 34
    c db 5
    res db 0

segment code use32 class=code
    start:
        ; d - (a+b)  - (c+c)
        mov ah, [d]
        mov al, [a]
        mov bh, [c]
        add al, [b]  ; a + b
        add bh, [c]  ; c + c
        sub ah, al  ; d - (a+b)
        sub ah, bh ; d - (c+c)
        mov [res], ah
        
    
        push    dword 0
        call    [exit] 
