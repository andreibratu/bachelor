bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 5, 25,  55,  127
    len_s equ $-s
    d db 0, 0, 0, 0, 0
    set_bits db 0
    counter db 0

segment code use32 class=code
    start:
        mov esi, s
        mov edi, d
        mov ecx, len_s
        
        super_cool:
            mov [counter], byte 8
            mov [set_bits], byte 0
            lodsb
            
            extract_bits:
                shr al,  1
                jnc loop_end
                
                inc byte [set_bits]
                
                loop_end:
                    dec byte [counter]
                    cmp [counter], byte 0
                    jg extract_bits
            
            mov al, [set_bits]
            stosb
            loop super_cool
        
        push dword 0
        call [exit]
