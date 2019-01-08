bits 32

global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    hexa_format db "%x", 0
    a_msg db "a = ", 0
    b_msg db "b = ", 0
    low_sum dd 0
    high_diff dd 0
    print_format db "%s%x\n", 0
    sum_msg db "sum = ", 0
    diff_msg db "diff = ", 0
    
segment code use32 class=code
    start:
        push a_msg
        call [printf]
        add esp, 4
        
        push a
        push hexa_format
        call [scanf]
        add esp, 4*2
        
        push b_msg
        call [printf]
        add esp, 4
        
        push b
        push hexa_format
        call [scanf]
        add esp, 4*2
        
        mov eax, 0
        mov ebx, 0
        mov ax, word [a]
        mov bx, word [a]
        add ax, bx
        mov [low_sum], eax
        
        mov eax, 0
        mov ebx, 0
        mov ax, word [a+2]
        mov bx, word [b+2]
        sub ax, bx
        mov  [high_diff], eax
        
        push dword [low_sum]
        push dword sum_msg
        push dword print_format
        call [printf]
        add esp, 4*3
        
        push dword [high_diff]
        push dword diff_msg
        push dword print_format
        call [printf]
        add esp, 4*3
        
        push dword 0
        call [exit]
