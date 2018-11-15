; Given a character string S, obtain the string D containing all special characters (!@#$%^&*) of the string S. 
bits 32

global start        

extern exit
import exit msvcrt.dll


segment data use32 class=data
    s db 'A', 'b', '?', '=', '7', '@'
    l equ ($-s)
    d times l db 0


segment code use32 class=code
    start:
        mov ecx, l
        mov ebx, 0
        mov edx, 0
        cmp ecx, 1
        
        js sfarsit
        
        repeta:
            mov al, [s+ebx]
            
            cmp al, 'A'
            js cond_true ; < 'A'
            jmp end_if
            
            cond_true:
                cmp al, ':'     ; >= ':'
                js end_if
                
                mov [d+edx], al
                inc edx
            
            end_if:
                inc ebx
                loop repeta             
            
        sfarsit:
        
        push    dword 0
        call    [exit]
