.model small
.stack 200h
.data
                    strMLen         =  128
                    newStr          db 10,13,'$' 
                    initStr         db strMLen, strMLen dup ('$') 
                    str1            db 0Dh,'Enter first number: ',0Ah,'$'     ;13 - return carriage, 10-enter / newLine
                    str2            db 0Dh,'Enter second number: ',0Ah,'$'
                    divStr          db ' / ','$'
                    remStr           db ' % ','$'
                    msgPressAnyKey  db 0Ah,'Press any key to exit...', '$'
                    dividend        dw ?
                    divisor         dw ?
                    private         dw ?
                    remnant         dw ?
.code
charInput PROC 
                    push bx
                    push cx         ;сохраняем регистры
                    push dx

                    mov si, cx                    
                    xor dx,dx
                    xor cx,cx
    escape:
                    jcxz charEnteringStr
                    dec si
                    mov dl,8
                    mov ah,02h
                    int 21h
                    mov dl,' '
                    int 21h
                    mov dl,8
                    int 21h
                    loop escape
                    lea cx, initStr
                    mov si, cx                    
                    xor dx,dx
                    xor cx,cx
                    jmp charEnteringStr
    backspace:
                    jcxz charEnteringStr
                    dec cx                
                    dec si     
                    mov byte ptr es:[si],' '
                    mov dl,8
                    mov ah,02h
                    int 21h
                    mov dl,' '
                    int 21h
                    mov dl,8
                    int 21h
    charEnteringStr:
                    xor bx,bx
                    mov ah, 08h 
                    int 21h 
                    cmp al,8
                    jz backspace
                    cmp al, 27
                    jz escape
                    cmp al,10
                    jz finish
                    cmp al,13
                    jz finish
                    cmp al,57
                    jg charEnteringStr
                    cmp al,48
                    jl charEnteringStr
                    cmp cx,5                 
                    jz charEnteringStr                                               
                    mov [si],al
                    inc si
                    inc cx                     
                    mov dx,bx
                    mov ah,02h
                    int 21h                                                      
                    jmp charEnteringStr
                    BESC:
                    jmp escape
    numberValue:
                    xor dx,dx
                    xor bx,bx
                    xor bx,bx
                    cmp cx,5
                    jne charEnteringStr
                    mov bl,[si-5]
                    cmp bl,'6'
                    jl recAX
                    jg BESC
                    mov bl,[si-4]
                    cmp bl,'5'
                    jl recAX
                    jg BESC                    
                    mov bl,[si-3]
                    cmp bl,'5'
                    jl recAX
                    jg BESC
                    mov bl,[si-2]
                    cmp bl,'3'
                    jl recAX
                    jg BESC
                    mov bl,[si-1]
                    cmp bl,'5'
                    jl recAX                    
                    jg BESC
                    jmp recAX
    CES:
                    jmp charEnteringStr
    chares:
                    push dx
                    xor bx,bx
                    cmp dx,1
                    jz BESC
                    jnz exit
    finish:
                    xor bx,bx
                    test cx,cx
                    jz CES                   
                    cmp cx,5                 
                    jz numberValue
    recAX:
                    xor bx,bx
                    xor bx,bx
                    xor dx,dx
                    mov bx,10
                    push cx
    recChar:
                    xor bx,bx
                    sub si,cx 
                    mov al, [si]
                    sub al, '0'
                    push cx
                    dec cx 
                    push dx
                    jcxz ready                    
    multiply:
                    mul bx
                    loop multiply
    ready:                 
                    pop dx
                    add dx,bx
                    pop cx
                    add si,cx
                    loop recChar  
                    pop cx
                    mov bx,dx
                    xor dx,dx                    
                    pop dx                    
                    cmp bx,0
                    jz chares     
                    pop cx   
                    pop bx          ;восстанавливаем регистры                       
                    ret 
    exit:
                    pop dx
                    pop cx
                    pop bx          ;восстанавливаем регистры
                    ret                   
charInput ENDP
decPrint proc                                       ; перевод из ax в строку буфера приёма es:di
                    push cx         ;сохраняем регистры
                    push dx
                    push bx
                    push bx
                    xor bx,bx       ;es:di - адрес буфера приемника
                    mov bx,10       ; основание системы
                    xor cx,cx       ; длина числа
    divNum:
                    xor dx,dx       ; dx = 0
                    div bx          ; dx = mod(ax, bx)
                    push dx         ; сохраняем dx в стек
                    inc cx          ; for LOOP
                    cmp bx,0        ;test ax,ax      ; ax and ax = 0? : ZF = 1
                    jnz divNum
    printNum:
                    pop dx
                    add dl,'0'
                    mov AH,02h
                    int 21h
                    ;pop ax          ; берём число из стека от начала
                    ;add al,'0'      ; число в ASCII
                    ;stosb           ; ES:[DI] = AL DF=0 (флаг направления) => DI = DI+1 , если 1 =>DI= DI - 1      or POP DX|ADD DL,'0'|MOV AH,02h|INT 21h 
                    loop printNum
                    ; mov     ah,     09h
                    ; lea     dx,     [newStr]
                    ; int 21h
                    pop bx
                    pop bx          ;восстанавливаем регистры
                    pop dx
                    pop cx
                    ret
decPrint endp
start:
	                mov bx,@data	                ;настраиваем сегментные регистры
                	mov ds,bx
                    mov es,bx

                    mov     ah,     09h             ;input number 1
                    lea     dx,     [str1]
                    int 21h
                    lea cx, initStr  
                    call charInput                  
                    mov dividend,bx 
                    mov remnant,bx                       ;save number 1
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h  
                    mov     ah,     09h             ;input number 2
                    lea     dx,     [str2]
                    int 21h
                    lea cx, initStr
                    mov dx,1
                    call charInput
                    mov divisor ,bx                        ;save number 2
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h

                    mov bx,dividend
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [divStr]
                    int 21h
                    mov bx,divisor
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    mov bx,dividend
                    div divisor
                    call decPrint 

                    mov private,bx
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    mov bx,private
                    mul divisor
                    sub remnant,bx
                    mov bx,dividend
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [remStr]
                    int 21h
                    mov bx,divisor
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    mov bx,remnant
                    call decPrint 

                    mov     ah,     09h
                    lea     dx,     [msgPressAnyKey]
                    int     21h
                    mov     ah,     00h             ; ожидание ввода пользователя
                    int     16h 

                    mov bx,4c00h
                    int 21h
end start                    
