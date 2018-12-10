; A file name is given (defined in the data segment). Create a file with the given name, then 
; read words from the keyboard and write those words in the file, until character '$' is read from the keyboard
bits 32

global start        

extern exit, scanf, printf, fprintf, fopen, fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    filename db "cool.txt", 0
    message db "Please input a number ", 0
    write_mode db "w", 0
    string_mode db "%s", 0
    descriptor dd 0
    var db 0
    

segment code use32 class=code
    start:
        push dword write_mode
        push dword filename
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        jz final
        mov [descriptor], eax
        
        input_loop:
            push dword message
            push dword string_mode
            call [printf]
            add esp, 4*2
            
            push dword var
            push dword string_mode
            call [scanf]
            add esp, 4*2
            
            cmp byte [var], '$'
            jz close_file
            
            push dword var
            push dword [descriptor]
            call [fprintf]
            add esp, 4*2
            
            push dword ' '
            push dword [descriptor]
            call [fprintf]
            add esp, 4*2
            
            jmp input_loop
        
        close_file:
            push dword [descriptor]
            call [fclose]
        
        final:
            push    dword 0
            call    [exit]
