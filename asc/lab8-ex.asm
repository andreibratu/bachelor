bits 32

global start        

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    msg db "Input your number: ", 0
    read_f db "%d", 0
    msg2 db "Your number is: %d", 0
    n dw 0

segment code use32 class=code
    start:
        push dword msg
        call [printf]
        add esp, 4
        
        push dword n
        push dword read_f
        call [scanf]
        add esp, 4*2
        
        mov eax, 0
        mov eax, [n]
        pushad
        
        push eax
        push dword msg2
        call [printf]
        add esp, 4*2
        
        popad
        
        push dword 0
        call [exit]
