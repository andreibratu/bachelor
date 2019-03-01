bits 32

global start        

extern exit, fopen, fclose, fread, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    file_name db "cool.txt", 0
    file_mode db "r", 0
    file_descriptor dd -1
    len equ 100
    q times len db 0

segment code use32 class=code
    start:
        push file_mode
        push file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je finale
        mov [file_descriptor], eax
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push q
        call [fread]
        add esp, 4*4
        
        push q
        call [printf]
        add esp, 4*1
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
                
        finale:
            push dword 0
            call [exit]
