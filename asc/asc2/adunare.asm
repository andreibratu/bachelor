bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dd 0X10
    b dd 0X10
    c dd 3
    res dd 0

segment code use32 class=code
    start:
        mov eax, [a]
        add eax,  [b]
        sub eax, [c]
        mov [res], eax
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
