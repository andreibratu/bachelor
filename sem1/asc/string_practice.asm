bits 32

global start        

extern exit
import exit msvcrt.dll


segment data use32 class=data
    a dd 127F5678h, 0ABCDABCDh
    dwords equ ($-a) / 4
    b dd 0, 0
    odd_mask equ 0FF00FF00h
    even_mask equ 000FF00FFh
    odd_sum dw 0
    even_sum dw 0
    aux dd 0
    
segment code use32 class=code
    start:
        mov ecx, dwords
        mov esi, a
        mov edi, b
        loop_dwords:
            mov [odd_sum], dword 0
            mov [even_sum], dword 0
            
            lodsd
            mov [aux], eax
            and eax, odd_mask
            
            odd_bits:
                add [odd_sum], ax
                sar eax, 16
                cmp eax, 0
                jg odd_bits
                
            mov eax, [aux]
            and eax, even_mask
            
            even_bits:
                add [even_sum], ax
                sar eax, 16
                cmp eax, 0
                jg even_bits
            
            mov eax, [odd_sum]
            mov eax, [even_sum]
            
            mov ax, [odd_sum]
            shl eax, 16
            mov ax, [even_sum]
            
            stosd
            
            loop loop_dwords
        
        push    dword 0
        call    [exit]
