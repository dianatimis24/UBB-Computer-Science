; 8. Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code.
bits 32
global start

import printf msvcrt.dll
import exit msvcrt.dll
extern printf, exit

; base_8_number function is defined in the file base_8_number.asm
extern base_8_number
; base_8_number(int) : int
;   - 1 parameter N : integer
;   - calculates the value of N in base 8 : integer
;   - return value in EAX : integer
;   - uses/modifies EAX, EDX, ECX, EBX
;   - frees stack parameters

segment data use32
	format_string db "For the number %d, we have: base 8 for = %d and ascii code = %c", 10, 13, 0

segment code use32 public code
start:
    mov ECX, 32
    print_loop:
        push ECX 
        
        mov EBX, ECX
        push EBX
        call base_8_number
        ; EAX = base_8_number(ECX)
        
        pop ECX
        mov EDX, ECX
        push ECX
        
        push EDX
        push EAX
        push EDX 
        push format_string
        call [printf]
        add ESP, 4*4
        
        pop ECX
        inc ECX
        cmp ECX, 127
        jb print_loop  
    
	push 0
	call [exit]