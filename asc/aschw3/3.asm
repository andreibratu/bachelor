bits 32
; (a+b/c-1)/(b+2)-x
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dd 90
    b db -35
    c dw -456
    x dq -945
    
segment code use32 class=code
    start:
        mov ax, [b]
        cbw
        cwd
        ; dx:ax -> b
        
        idiv word [c]
        ; b/c in ax
        
        cwde ; eax -> b/c
        cdq ; edx:eax -> b/c
        add eax, [a]
        adc edx, 0
        sub eax, 1
        sbb edx, 0
        ; edx:eax -> a+b/c-1
        
        mov ecx, edx
        mov ebx, eax
        ; ecx:ebx -> a+b/c-1
        
        mov al, [b]
        cbw
        cwde
        ; eax -> b
        add eax, 2
        ; eax -> b+2
        
        mov edx, eax
        mov eax, ebx
        mov ebx, edx
        mov edx, ecx
        ; edx:eax -> (a+b/c-1)
        ; ebx -> (b+2)
        
        idiv ebx
        ; eax -> (a+b/c-1)/(b+2)
        cdq ; edx:eax -> (a+b/c-1)/(b+2)
        sub eax, [x]
        sbb edx, [x+4]
        ; result in edx:eax
        
        push    dword 0
        call    [exit]
