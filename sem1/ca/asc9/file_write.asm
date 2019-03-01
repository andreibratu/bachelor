bits 32

global start        

extern exit, fprintf, fclose, fopen
import exit msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data
    filename db "dimitri.txt", 0
    mode db "w", 0
    file_descriptor dd 0
    text  db "Cheeki breeki", 0


segment code use32 class=code
    start:
        push mode
        push filename
        call [fopen]
        
        mov [file_descriptor], eax
        
        push text
        push file_descriptor
        call [fprintf]
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4        
        
        push    dword 0
        call    [exit]
