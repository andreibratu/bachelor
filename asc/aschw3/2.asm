bits 32
; d+d-a-b-c

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    d dq 10000000
    a db 10
    b dw 2567
    c dd 1290

segment code use32 class=code
    start:
        
        mov eax, [d]
        mov edx, [d+4]
        
        mov ebx, [d]
        mov ecx, [d+4]
        
        add eax, ebx
        adc edx, ecx
        ; d+d
        
        mov ebx, 0
        mov bl, [a]
        mov ecx, 0
        sub eax, ebx
        ; d+d-a
        
        mov ebx, 0
        mov bx, [b]
        sub eax, ebx
        ; d+d-a-b
        
        mov ebx, [c]
        mov ecx, 0
        sub eax, ebx
        sbb edx, 0
        ; d+d-a-b-c
        
        push    dword 0
        call    [exit]
