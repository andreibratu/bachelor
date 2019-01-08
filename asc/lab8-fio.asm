bits 32

global start        

extern exit, fopen, fprintf, fclose

import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    file_mode db 'w', 0
    file_name db "cool.txt", 0
    file_descriptor dd 0
    msg db "I miss her", 0

segment code use32 class=code
    start:
        push file_mode
        push file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je q
        mov [file_descriptor], eax
        
        push msg
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        q:
            push dword 0
            call [exit]
