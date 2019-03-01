bits 32
; f+(c-2)*(3+a)/(d-4)

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 34
    c db 78
    d db 24
    f dw 500
    res dw 0

segment code use32 class=code
    start:
        mov al, [c]
        sub al, byte 2
        
        mov bl, [a]
        add bl, byte 3
        
        mul byte bl
        
        mov bl, [d]
        sub bl, 4
        
        div byte bl
        mov ah, 0
        add ax, [f]
        
        mov [res], ax
        
        push    dword 0
        call    [exit]
