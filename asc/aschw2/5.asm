bits 32
; d/[(a+b)-(c+c)]

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 32
    b db 14
    c db 7
    d dw 78
    res db 0
    
segment code use32 class=code
    start:
        mov ax, [d]
        
        mov bl, [a]
        add bl, [b]
        
        mov bh, [c]
        add bh, [c]
        
        sub bl, bh
        
        div byte bl
        mov [res], al        
        
        push dword 0
        call    [exit]
