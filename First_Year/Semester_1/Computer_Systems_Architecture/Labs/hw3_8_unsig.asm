; a, b - word, c, d - byte, e - doubleword, x - qword
; 1 / a + 200 * b - c / (d + 1) + x / a - e
; unsigned representation

bits 32
global start        
extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dw 1
    b dw 5
    c db 24
    d db 11
    e dd 30
    x dq 9

segment code use32 class=code
    ; 1 / a + 200 * b - c / (d + 1) + x / a - e
    start:
        ; 1 / a
        mov AX, 1 ; AX = 1
        mov DX, 0 ; DX:AX = 1
        div word [a] ; AX = 1 / a = 1 / 1 = 1
        
        ; AX -> DX:AX -> EAX -> ECX
        mov DX, 0 ; DX:AX = 1 / a = 1
        push DX
        push AX
        pop EAX ; EAX = DX:AX = 1/ a = 1 
        mov ECX, EAX ; ECX = 1 / a = 1
        
        ; 200 * b 
        mov AX, 200 ; AX = 200
        mul word [b] ; DX:AX = 200 * b = 200 * 5 = 1000
        
        ; DX:AX -> EAX
        push DX
        push AX
        pop EAX ; EAX = DX:AX = 1000

        ; 1 / a + 200 * b
        add ECX, EAX ; ECX = 1 + 1000 = 1001
        
         ; AL -> AX = c
        mov AL, [c]
        mov AH, 0 ; AX = c = 24
        
        ; BL = d + 1
        mov BL, [d] ; BL = 11
        add BL, 1 ; BL = d + 1 = 12
        
        ; c / (d + 1) and place it in AX
        div BL ; AL = AX / BL = 24 / 12 = 2
        mov AH, 0 ; AX = c / (d + 1) = 2
        
        ; AX -> DX:AX -> EAX
        mov DX, 0 ; DX:AX = c / (d + 1) = 2
        push DX
        push AX
        pop EAX ; EAX = c / (d + 1) = 2
        
        ; 1 / a + 200 * b - c / (d + 1)
        sub ECX, EAX ; ECX = 1 / a + 200 * b - c / (d + 1) = 1001 - 2 = 999
        
        ; a = 1 in EBX
        mov AX, [a] ; AX = a = 1
        mov DX, 0 ; DX:AX = a = 1
        push DX
        push AX
        pop EAX ; EAX = a = 1
        mov EBX, EAX ; EBX = a = 1
        
        ; x = 9 in EDX:EAX 
        mov EAX, [x]
        mov EDX, [x+4]
        
        ; x / a
        div EBX ; EAX = EDX:EAX / EAX = x / a = 9 / 1 = 9
        
        ; 1 / a + 200 * b - c / (d + 1) + x / a
        add ECX, EAX ; ECX = 1 / a + 200 * b - c / (d + 1) + x / a = 999 + 9 = 1008
        
        ; 1 / a + 200 * b - c / (d + 1) + x / a - e
        sub ECX, dword [e] ; ECX = 1 / a + 200 * b - c / (d + 1) + x / a - e = 1008 - 30 = 978
        
        ; Final result in ECX = 978
        
        push    dword 0      
        call    [exit]       
