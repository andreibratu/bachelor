bits 32
; (100+a+b*c)/(a-100)+e+x/a
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 47
    b db 130
    c dw 179
    e dd 17893
    x dq -13129
    aux1 dd 0

segment code use32 class=code
    start:
        mov al, [a]
        cbw
        cwde
        mov ebx, eax
        ; ebx -> a
        
        mov eax, [x]
        mov edx, [x+4]
        ; edx:eax -> x
        
        idiv ebx
        mov [aux], eax ; aux -> x/a
        mov edx, 0 ; cleanup
        
        mov ax, [c]
        cwde ; eax -> c
        mov ebx, eax ; ebx -> c
        mov al, [b]
        cbw ; ax -> b
        cwde ; eax -> b
        imul ebx ; edx:eax -> b*c
        
        add eax, 100
        adc edx, 0
        ; edx:eax -> b*c+100
        
        mov ebx, eax
        mov ecx, edx
        ; ecx:ebx ->  b*c+100
        mov al, [a]
        cbw
        mov edx, 0
        add eax, ebx
        adc edx, ecx
        adc edx, 0
        ; edx:eax -> b*c+100+a
        
        mov ebx, eax
        mov ecx, edx
        ; ecx:ebx -> b*c+100+a 
        
        mov al, [a]
        cbw
        cwde
        ; eax -> a
        sub eax, 100
        ; eax -> a-100
        
        mov edx, ebx
        mov ebx, eax
        mov ebx, edx
        mov edx, ecx
        ; edx:eax -> b*c+100+a
        ; ebx -> a-100
        
        idiv ebx
        ; eax -> (100+a+b*c)/(a-100)
        
        add eax, [aux1]
        ; eax -> (100+a+b*c)/(a-100)+x/a
        mov edx, 0 ; cleanup
        
        add eax, [x]
        adc edx, dword [x+4]
        ; edx:eax -> (100+a+b*c)/(a-100) + x/a + e
        
        push    dword 0
        call    [exit]
