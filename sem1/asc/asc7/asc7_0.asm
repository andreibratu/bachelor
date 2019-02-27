; Given a byte string S of length l, obtain the string D of length l-1 as
; D(i) = S(i) * S(i+1)
; (each element of D is the product of two consecutive elements of S).
bits 32

global start

extern exit
import exit msvcrt.dll


segment data use32 class=data
    s db 2
    l equ ($-s)
    d times l dw 0


segment code use32 class=code
    start:
        mov ecx, l-1
        mov ebx, 0

        jecxz sfarsit

        repeta:
            mov al, [s+ebx+1]
            imul byte [s+ebx]
            mov [d+ebx], ax
            inc ebx
            loop repeta

        sfarsit:
          push    dword 0
          call    [exit]
