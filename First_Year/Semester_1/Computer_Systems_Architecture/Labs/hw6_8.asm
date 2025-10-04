; 8. A list of doublewords is given. Obtain the list made out of the low bytes of the high words 
; of each doubleword from the given list with the property that these bytes are palindromes in base 10.

bits 32 
global start        
extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    s dd 12345678h, 1A2C3C4Dh, 98FCDC76h
    len equ ($ - s) / 4
    d times len db 0
    ten db 10
    
segment code use32 class=code
    start:
        mov ESI, s 
        mov EDI, d 
        mov ECX, len 
        jecxz end_loop
        string_repeat:
            lodsw ; AX = the low word of the current number and inc ESI with 2  
            lodsw ; AX = the high word of the current number and inc ESI with 1 
            ; AL contains the low byte of the high word of the current number
            
            mov DL, AL ; save in DL the current number
            mov BL, 0 ; create the reverse of the current number in BL (the reverse is also a byte)
            reverse_loop:
                push EAX
                mov AL, BL ; AL = BL
                mul byte [ten] ; AX = AL * 10
                mov BX, AX ; BX = AX <--> BL = AL
                pop EAX

                mov AH, 0 ; AX = AL
                div byte [ten] ; AL = AX / 10 ; AH = AX % 10
                add BL, AH 
                
                cmp AL, 0
                je out_of_loop
            jmp reverse_loop
            out_of_loop:
            
            mov AL, DL ; place the value of the current number in AL
            cmp AL, BL
            jne dont_add_term_to_d
                stosb ; put the content of AL (the current number)in d and EDI += 1
            dont_add_term_to_d:
        loop string_repeat
        end_loop:
        
        push    dword 0     
        call    [exit]       
