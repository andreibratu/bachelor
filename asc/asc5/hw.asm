bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 456
    b dw 15678
    c dd 0

segment code use32 class=code
    start:
        mov ecx, 0
        mov eax, 0
        
        mov ax, [b]
        and ax, 000001e0h
        ; bits 5-8 of b
        
        shr ax, 5
        or cl, al
        ; set bits 0-3 of ecx to bits 5-8 of b
        
        mov eax, 0
        mov ax, [a]
        and ax,  0000001fh
        ; get bits 0-4 of a
        
        shr ax, 5
        or edx, eax
        ; set bits 4-8 of ecx
        
        mov eax, 0
        mov ax, [a]
        and eax, 00001fc0h
        ; bits 3-9 of a
        shr eax, 3
        or ecx, eax
        ; set bits 9-15 of ecx
        
        mov eax, 0
        mov ax, [a]
        shr eax, 16
        or ecx, eax
        ; bits 16-31 of C are the same as the bits of A
        
        mov [c], ecx
        
        push    dword 0
        call    [exit]
