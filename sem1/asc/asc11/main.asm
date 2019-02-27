; Multiple numbers in base 2 are read from the keyboard. Display these numbers in the base 16.
bits 32

global start        

extern exit, scanf
import exit msvcrt.dll
import scanf msvcrt.dll
%include "print.asm"

segment data use32 class=data
    nr_format db "%b", 0
    nr dd 0
    
segment code use32 class=code
    start:
        .read_loop:
            push nr
            push nr_format
            call [scanf]
            add esp, 4*2
            
            push dword [nr]
            call print
            add esp, 4
            
            cmp eax, 0
            je final
            
            jmp .read_loop
       
        final:
            push dword 0
            call [exit]
