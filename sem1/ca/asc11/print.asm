bits 32

global print   

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    print_format db "%x", 0
    
segment code use32 class=code
    print:       
        mov ebx, [esp+4]
        push ebx
        push print_format
        call [printf]
        add esp, 4*2
        ret
