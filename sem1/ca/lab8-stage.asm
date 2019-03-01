bits 32

global start        

extern exit, fopen, fread, printf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    file_descriptor dd -1
    file_name db "cool.txt", 0
    read_mode db "r", 0
    len equ 100
    buffer resb len

segment code use32 class=code
    start:
        push dword read_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je finale
        mov [file_descriptor], eax
        
        read_loop:
            ; fread(buffer, size_elem, how_many, FILE*)
            push dword [file_descriptor]
            push  dword len
            push dword 1
            push buffer
            call [fread]
            add esp, 4*4
            
            cmp eax, 0
            je finale
            
            push buffer
            call [printf]
            add esp, 4
            
            jmp read_loop
        
        push buffer
        call [printf]
        add esp, 4

        push dword [file_descriptor]
        call [fclose]
        
        finale:
            push dword 0
            call [exit]
