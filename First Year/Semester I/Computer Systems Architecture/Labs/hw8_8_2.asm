; 8. A text file is given. Read the content of the file, determine the uppercase letter with the highest frequency 
; and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.

bits 32 
global start        
extern exit, fopen, fread, fclose, printf                
import exit msvcrt.dll 
import fopen msvcrt.dll 
import fread msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll  

segment data use32 class=data
    file_name db "input_file.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    print_format db "%c %d", 0
    char resd 1
    max_char dd 0
    fr resb 256
    max_fr dd 0
    
segment code use32 class=code
    start:
        push dword access_mode 
        push dword file_name 
        call [fopen]
        add ESP, 4 * 2
        
        cmp EAX, 0
        je final
        mov [file_descriptor], EAX
        
        mov ESI, fr 
        reading_loop:
            push dword [file_descriptor]
            push dword 1 ; read 1 element
            push dword 1 ; the element has 1 byte
            push dword char ; store the byte in char 
            call [fread]
            add ESP, 4 * 4
            
            cmp EAX, 0 ; the function returns 0 in EAX in case of an end-of-file character
            je stop_reading
            
            xor EAX, EAX
            mov AL, [char] ; AL = read character 
            cmp AL, 'A'
            jb next_character
            cmp AL, 'Z'
            ja next_character 
            
            ; if uppercase
            xor EBX, EBX
            mov BL,  [char]
            inc byte [ESI + EBX] ; fr[char]++
            xor ECX, ECX
            mov CL, [ESI + EBX]  ; ECX = the frequency of char character
            cmp ECX, [max_fr]    
            jle next_character   ; if (fr > max_fr) max_fr = fr, max_char = char
            mov [max_fr], ECX  ; max_freq = fr
            
            xor EAX, EAX
            mov AL, [char]
            mov [max_char], AL   ; max_char = char
            
            next_character:
        jmp reading_loop
        
        stop_reading:
        
        push dword [file_descriptor]
        call [fclose]
        add ESP, 1 * 4
        
        xor EAX, EAX
        mov AL, [max_char]
        mov EDX, [max_fr]
        push dword EDX
        push dword EAX
        push print_format
        call [printf]
        add ESP, 4 * 4
        
        final:
        push    dword 0      
        call    [exit]       
