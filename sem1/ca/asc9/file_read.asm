bits 32

global start        

extern exit, fprintf, fclose, fopen
import exit msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll


segment data use32 class=data
    filename db "cool.txt", 0
    mode db "r", 0
    file_descriptor dd 0
    

segment code use32 class=code
    start:
        push mode
        push filename
        call [fopen]
        
        mov [file_descriptor], eax
        cmp eax, 0
        
        je end_label
        
        mov [file_descriptor], eax
        
        end_label:
            push    dword 0
            call    [exit]
