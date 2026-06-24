; Write a program in the assembly language that computes the following 
; arithmetic expression, considering the following data types for the variables:
; a, b, c - byte, d - word (unsigned)
; (100 * a + d + 5 - 75 * b) / (c - 5)

bits 32 
global start        
extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a db 10
    b db 13
    c db 20
    d dw 85

segment code use32 class=code
    ; (100 * a + d + 5 - 75 * b) / (c - 5)
    start:
        ; 100 * a
        mov AL, 100 ; AL = 100
        mul byte [a] ; AX = AL * a = 100 * a = 100 * 10 = 1000
        ; 100 * a + d + 5
        add AX, word [d] ; AX = AX + d = AX + 85 = 1000 + 85 = 1085
        add AX, 5 ; AX = AX + 5 = 1085 + 5 = 1090
        
        mov BX, AX ; BX = AX = 1090
        
        ; 75 * b 
        mov AL, 75 ; AL = 75
        mul byte [b] ; AX = AL * b = 75 * b = 75 * 13 = 975
        
        ; (100 * a + d + 5 - 75 * b)
        sub BX, AX ; BX = BX - AX = 1090 - 975 = 115
        mov AX, BX ; AX = BX = 115
        
        ; c - 15
        mov BL, byte [c] ; BL = c = 20
        sub BL, 5 ; BL = BL - 5 = 20 - 5 = 15
        
        ;(100 * a + d + 5 - 75 * b) / (c - 5)
        div BL ; AL = AX / BL = 115 / 15 = 7
               ; AH = AX % BL = 115 % 15 = 10
    
        push    dword 0      
        call    [exit]       
