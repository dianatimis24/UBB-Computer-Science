; 8. Given the words A and B, compute the byte C as follows:
;     - the bits 0-5 are the same as the bits 5-10 of A
;     - the bits 6-7 are the same as the bits 1-2 of B.
;
;    Compute the doubleword D as follows:
;     - the bits 8-15 are the same as the bits of C
;     - the bits 0-7 are the same as the bits 8-15 of B
;     - the bits 24-31 are the same as the bits 0-7 of A
;     - the bits 16-23 are the same as the bits 8-15 of A.

;   Example:
;     A = 1101011101010101b = D755h
;     B = 1001101010100100b = 9AA4h
;   Correct results:
;     C = 10111010b = BAh
;     D = 01010101110101111011101010011010b = 55D7BA9Ah

bits 32 
global start        
extern exit              
import exit msvcrt.dll    

segment data use32 class=data
    A dw 1101011101010101b
    B dw 1001101010100100b
    C db 0
    D dd 0
    
segment code use32 class=code
    start:
        ; we place the result in BX and from here we will obtain the byte C
        ; by placing the wanted bits in the lower part of BX (BL) and then memorizing only those bits
        mov BX, 0
        
        ; we isolate the bits 5-10 from A in AX
        mov AX, word [A]
        and AX, 0000011111100000b
        mov CL, 5
        ror AX, CL ; we rotate 5 positions to the right
        or BX, AX ; BX = 0000000000111010b
        
        ; we isolate the bits 1-2 from B in AX
        mov AX, word [B]
        and AX, 0000000000000110b
        mov CL, 5
        rol AX, CL ; rotate 5 positions to the left
        or BX, AX ; BX = 0000000010111010b
        
        ; because the bits we are interested in are placed in the lower part of BX (BL)
        ; we can keep only BL, clear BH and save them in the variable C 
        mov BH, 0
        mov [C], BL ; we move the final result in the variable C 
                    ; C = 10111010b = BAh
        
        
        
        ; we place the result in EBX and from here we will obtain the doubleword D
        mov EBX, 0
        
        ; we place C as follows: AL -> AX -> DX:AX -> EAX
        mov AL, byte [C] ; AL = C 
        mov AH, 0 ; AX = C
        mov DX, 0 ; DX:AX = C
        push DX 
        push AX
        pop EAX ; EAX = C 
        
        ; we place the bits from C (already found at positions 0-7 in EAX) in the positions 8-15
        mov CL, 8
        rol EAX, CL ; we rotate 8 positions to the left
        or EBX, EAX
        
        ; we place B as follows: AX -> DX:AX -> EAX
        mov AX, word [B] ; AX = B
        mov DX, 0        ; DX:AX = B
        push DX 
        push AX
        pop EAX ; EAX = B 
        
        ; we isolate the bits 8-15 from B in EAX
        and EAX, 0xFF00
        mov CL, 8
        ror EAX, CL ; we rotate 8 positions to the right
        or EBX, EAX
        
        ; we place A as follows: AX -> DX:AX -> EAX
        mov AX, word [A] ; AX = A 
        mov DX, 0        ; DX:AX = A 
        push DX 
        push AX
        pop EAX ; EAX = A

        ; we isolate the bits 0-7 from A in EAX
        and EAX, 0xFF
        mov CL, 24
        rol EAX, CL ; we rotate 24 positions to the left
        or EBX, EAX
        
        ; we place A as follows: AX -> DX:AX -> EAX
        mov AX, word [A] ; AX = A 
        mov DX, 0        ; DX:AX = A 
        push DX 
        push AX
        pop EAX ; EAX = A

        ; we isolate the bits 8-15 from A in EAX
        and EAX, 0xFF00
        mov CL, 8
        rol EAX, CL ; we rotate 8 positions to the left
        or EBX, EAX
        
        mov [D], EBX ; we move the final result in the variable D 
                     ; D = 01010101110101111011101010011010b = 55D7BA9Ah
        
        push    dword 0     
        call    [exit]       
