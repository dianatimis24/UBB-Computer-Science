; 8. A natural number a (a: dword, defined in the data segment) is given. 
; Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. 
; The values will be displayed in decimal format (base 10) with sign.

bits 32 
global start        
extern exit, scanf, printf                
import exit msvcrt.dll 
import printf msvcrt.dll     
import scanf msvcrt.dll   

segment data use32 class=data
    a dd 240
    b dd 0
    format db "%d", 0
    message db "The result of the operation 240 + 240 / %d = %d", 0
    
segment code use32 class=code
    start:
        push dword b 
        push dword format 
        call [scanf]
        add ESP, 4 * 2
        
        mov EAX, [a]
        mov EDX, 0     ; EDX:EAX = a
        idiv dword [b] ; EAX = a / b 
        add EAX, [a]   ; EAX = a + a / b 
        
        push dword EAX
        push dword [b] 
        push dword message
        call [printf]
        add ESP, 4 * 3
        
        push    dword 0      
        call    [exit]       
