; Write a program in the assembly language that computes the following arithmetic 
; expression, considering the following data types for the variables:
; a, b, c, d - byte, e, f, g, h - word (unsigned)
; 2 * (a + b) - e

bits 32 
global start        
extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a db 24
    b db 30
    e dw 73

segment code use32 class=code
    ; 2 * (a + b) - e
    start:
        ; a + b
        mov BL, byte [a] ; BL = a = 24
        add BL, byte [b] ; BL = BL + b = a + b = 24 + 30 = 54
        
        ; 2 * (a + b)
        mov AL, 2 ; AL = 2
        mul BL ; AX = AL * BL = 2 * 54 = 108
        
        ; 2 * (a + b) - e
        sub AX, word [e] ; AX = AX - e = 108 - 73 = 35
        
        push    dword 0      
        call    [exit]       
