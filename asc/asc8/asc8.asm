; An array with doublewords containing packed data
; (4 bytes written as a single doubleword) is given.
; Write an asm program in order to obtain a new array of doublewords,
; where each doubleword will be composed by the rule: the sum of the bytes
; from an odd position will be written on the word from the odd position and
; the sum of the bytes from an even position will be written on the word from
; the even position. The bytes are considered to represent signed
; numbers, thus the extension of the sum on a word will be performed
; according to the signed arithmetic.

bits 32

global start        

extern exit
import exit msvcrt.dll


segment data use32 class=data
    a dd 127F5678h,  0ABCDABCDh
    len equ ($-a)/4
    b times len dd 0
    even_mask dd 0x55555555
    odd_mask dd 0xaaaaaaaa
    s_odd dw 0
    s_even dw 0
    pow_2 dd 0
    i db 0


segment code use32 class=code
    start:
        mov esi, a
        mov edi, b
        mov ecx, len
        
        jecxz sfarsit
        
        cld
        
        dword_for:
            mov [i], byte 0
            mov [pow_2], dword 1
            mov [s_odd], word 0
            mov [s_even], word 0
            
            lodsd
            
            mov edx, eax
            mov ebx, eax
            and ebx, [even_mask] ;ebx->even
            and edx, [odd_mask] ;edx->odd
            
            mov [i],  byte 0
            mov eax, 1
            
            bit_for:
                odd_label:
                    shr edx, 1
                    jnc  even_label
                    
                    add [s_odd], eax
                    
                even_label:
                    shr ebx, 1
                    jnc end_label
                    
                    add [s_even], eax
                    
                end_label:
                    shl eax, 1
                    
                    inc byte [i]
                    cmp [i], byte 32
                    js bit_for
        
        mov ax, [s_odd]
        shl ax, 16
        mov ax, [s_even]
        stosd
        
        loop dword_for
                    
        sfarsit:
            push    dword 0
            call    [exit]
