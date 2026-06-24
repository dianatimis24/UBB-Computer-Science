; 8. A character string S is given. Obtain the string D that contains all capital letters of the string S.
;    Example:
;    S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
;    D: 'A', 'B', 'M'


bits 32 
global start  
extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    s db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    len equ $-s 
    d times len db 0
    
segment code use32 class=code
    start: ; A character string S is given. Obtain the string D that contains all capital letters of the string S.
        mov ESI, 0
        mov EDI, 0
        mov ECX, len 
        jecxz end_loop
        my_repeat:
            mov AL, [s + ESI]
            cmp AL, 'A'     ; we compare the ASCII value of the current character with the ASCII value of 'A'
            jb skip_smaller ; if the value is smaller ("below") than 'A', then we jump
                cmp AL, 'Z'     ; we compare the ASCII value of the current character with the ASCII value of 'Z'
                ja skip_larger  ; if the value is larger ("above") than 'Z', then we jump
                    mov [d + EDI], AL
                    inc EDI
                skip_larger:
            skip_smaller:
            inc ESI
        loop my_repeat
        end_loop:
        
        push    dword 0      
        call    [exit]       
