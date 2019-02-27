; Two natural numbers a and b (a, b: dword, defined in the data segment) are given. 
; Calculate a/b and display the quotient and the remainder in the following format: 
; "Quotient = <quotient>, remainder = <remainder>". 
; Example: for a = 23, b = 10 it will display: "Quotient = 2, remainder = 3".
; The values will be displayed in decimal format (base 10) with sign

bits 32

global start        

extern printf, exit
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dq 47676869565
    b dd 238
    format db "Quotient = %d, Remainder = %d", 0
    input db 0


segment code use32 class=code
    start:
        push dword [a]
        push dword [a+4]
        pop edx
        pop eax
        idiv dword [b]
        
        push edx
        push eax
        push format   
        call [printf]
        add esp, 4*3
        
        push    dword 0
        call    [exit]
