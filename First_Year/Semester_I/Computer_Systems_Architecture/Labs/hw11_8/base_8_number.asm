bits 32                         
segment code use32 public code
global base_8_number

; base_8_number(int) : int
;   - 1 parameter N : integer
;   - calculates the value of N in base 8 : integer
;   - return value in EAX : integer
;   - uses/modifies EAX, EDX, ECX, EBX
;   - frees stack parameters
base_8_number:
    mov EAX, [ESP + 4]
    mov EBX, 8
    mov ECX, 0
    xor EDX, EDX
    
    digits_of_the_conversion_into_base_8_loop:
        xor EDX, EDX
        div EBX ; EDX:EAX / 8 -> quotient in EAX, remainder in EDX
        
        push EDX
        inc ECX

        cmp EAX, 0
        jne digits_of_the_conversion_into_base_8_loop
        
    ; now, the digits of the result are on the stack in correct order and their number is contained by ECX 
    ; we will obtain the number in EAX
    
    mov EAX, 0
    jecxz final
    obtaining_number_in_base_8_loop:
        mov EDX, 10
        mul EDX ; EDX:EAX = 10 * EAX, but EDX = 0, because the numbers used in our program are not that big
        pop EBX ; the last digit from the stack
        add EAX, EBX 
        loop obtaining_number_in_base_8_loop
    
    final:
    
    ; the conversion into base 8 is in EAX
    ret 4