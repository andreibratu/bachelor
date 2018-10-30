bits 32
; c-(b+d)+(a+d)

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 10
    b dw 345
    c dd 50000
    d dq 10000000000

segment code use32 class=code
    start:
        mov eax,  [d]
        mov edx, [d+4]
        ; edx:eax -> d
        
        mov ebx, 0
        mov bx, [b]
        ; ebx -> b
        
        add eax, ebx
        ; b+d        
          
        mov ebx, dword [d]
        mov ecx, dword [d+4]
        ; d into ecx:ebx
        
        add eax, ebx
        adc edx, ecx
        ; b+d+d
        
        mov ebx, eax
        mov ecx, edx
        mov al, [a]
        cbw
        cwde
        add eax, ebx
        adc edx, ecx
        mov ecx, 0 ; cleanup
        ; b+d+d+a
        
        mov ebx, [c]
        
        sub ebx, eax
        sbb ecx, edx
        ; c-(b+d)+(a+d)
        
        mov eax, ebx
        mov edx, ecx 
        ; result in edx:eax
        
        push    dword 0
        call    [exit]
