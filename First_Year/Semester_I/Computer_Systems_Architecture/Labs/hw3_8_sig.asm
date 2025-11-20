; a, b - word, c, d - byte, e - doubleword, x - qword
; 1 / a + 200 * b - c / (d + 1) + x / a - e
; signed representation

bits 32 
global start        
extern exit              
import exit msvcrt.dll   

segment data use32 class=data
    a dw -1
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
        cwd ; DX:AX = 1
        idiv word [a] ; AX = 1 / a = 1 / -1 = -1
        
        ; AX -> EAX -> ECX
        cwde ; EAX = 1 / a = -1
        mov ECX, EAX ; ECX = 1 / a = -1
        
        ; 200 * b 
        mov AX, 200 ; AX = 200
        imul word [b] ; DX:AX = 200 * b = 200 * 5 = 1000
        
        ; DX:AX -> EAX
        push DX
        push AX
        pop EAX ; EAX = DX:AX = 1000

        ; 1 / a + 200 * b
        add ECX, EAX ; ECX = -1 + 1000 = 999
        
        ; AL -> AX = c
        mov AL, [c]
        cbw ; AX = c = 24
        
        ; BL = d + 1
        mov BL, [d] ; BL = 11
        add BL, 1 ; BL = d + 1 = 12
        
        ; c / (d + 1) and place it in EAX
        idiv BL ; AL = AX / BL = 24 / 12 = 2
        cbw ; AX = c / (d + 1) = 2
        cwde ; EAX = c / (d + 1) = 2
        
        ; 1 / a + 200 * b - c / (d + 1)
        sub ECX, EAX ; ECX = 1 / a + 200 * b - c / (d + 1) = 999 - 2 = 997
        
        ; a = -1 in EBX
        mov AX, [a] ; AX = a = -1
        cwde ; EAX = a = -1
        mov EBX, EAX ; EBX = a = -1
        
        ; x = 9 in EDX:EAX 
        mov EAX, [x]
        mov EDX, [x+4]
        
        ; x / a
        idiv EBX ; EAX = EDX:EAX / EAX = x / a = 9 / -1 = -9
        
        ; 1 / a + 200 * b - c / (d + 1) + x / a
        add ECX, EAX ; ECX = 1 / a + 200 * b - c / (d + 1) + x / a = 997 + -9 = 988
        
        ; 1 / a + 200 * b - c / (d + 1) + x / a - e
        sub ECX, dword [e] ; ECX = 1 / a + 200 * b - c / (d + 1) + x / a - e = 988 - 30 = 958
        
        ; Final result in ECX = 958
        
        push    dword 0      
        call    [exit]       
