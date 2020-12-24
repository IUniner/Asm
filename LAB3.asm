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
                    minS           db '-','$'
                    msgPressAnyKey  db 0Ah,'Press any key to exit...', '$'
                    dividend        dw ?
                    divisor         dw ?
                    private         dw ?
                    remnant         dw ?
.code               ; -32768..32767 
                    sign            db 0
                    isNegVal1       db 0
                    isNegVal2       db 0
charInput PROC
                    mov sign,0
                    push bx
                    push cx         ;сохраняем регистры
                    push dx
                    mov si, cx                    
                    xor dx,dx
                    xor cx,cx
    resetLen:    
                    mov bx,5
                    jmp charEnteringStr
    minus:          
                    cmp cx,1            ;negativ nums
                    jz resetLen
                    cmp cx,0
                    jnz resetLen
                    mov bx,6
                    mov [si],al
                    inc si
                    inc cx
                    mov dx,ax   
                    mov ah,02h
                    int 21h
                    jmp charEnteringStr
    escape:
                    jcxz resetLen
                    mov al,[si-1]       ;negativ nums
                    cmp al,'-'          ;
                    jz backspace        ;
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
                    jmp resetLen
    backspace:
                    jcxz resetLen
                    ;mov al,[si-1]       ;negativ nums
                    ;cmp al,'-'          ;
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
                    jmp resetLen
    charEnteringStr:
                    xor ax,ax
                    mov ah, 08h 
                    int 21h 
                    cmp al,'-'          ;negativ nums
                    jz minus            ;
                    cmp al,8
                    jz backspace
                    cmp al, 27
                    jz escape
                    cmp al,10
                    jz final
                    cmp al,13
                    jz final
                    cmp al,57
                    jg charEnteringStr
                    cmp al,48
                    jl charEnteringStr
                    cmp cx,bx
                    jz charEnteringStr                    
                    mov [si],al
                    inc si
                    inc cx
                    mov dx,ax
                    mov ah,02h
                    int 21h                                                      
                    jmp charEnteringStr
                        BESC:
                    jmp escape
    negValue:
                    cmp cx,6
                    jne BESC
                    mov bl,[si-6]
                    cmp bl,'-'
                    jne BESC
                    mov bl,[si-1]
                    cmp bl,'8'
                    jl recAX                    
                    jg BESC
                    jmp final
    numberValue:
                    cmp cx,5
                    jne BESC
                    mov bl,[si-1]
                    cmp bl,'7'
                    jl recAX                    
                    jg BESC
	final:
					jmp finish
    check:
					xor dx,dx
                    xor bx,bx
                    xor ax,ax
                    mov bl,[si-5]
                    cmp bl,'3'
                    jl recAX
                    jg BESC
                    mov bl,[si-4]
                    cmp bl,'2'
                    jl recAX
                    jg BESC                    
                    mov bl,[si-3]
                    cmp bl,'7'
                    jl recAX
                    jg BESC
                    mov bl,[si-2]
                    cmp bl,'6'
                    jl recAX
                    jg BESC
                    cmp cx,5
                    jz numberValue
                    ja negValue
                    jmp BESC
    negNumber:
                    mov sign,1
                    dec cx
                    jmp negNum
	nV:
					jmp negValue
    CES:
                    jmp charEnteringStr
    chares:
                    push dx
                    xor bx,bx
                    cmp dx,1
                    jz BESC
                    jnz exit
    finish:
                    jcxz BESC
                    ;jz BESC
                    mov al,[si-1]       ;negativ nums
                    cmp al,'-'          ;
                    jz CES  ;negativ nums
                    cmp cx,5                 
                    jae check

    recAX:
                    push si
                    sub si,cx
                    mov al,[si]
                    cmp al,'-' 
                    pop si
                    jz negNumber
    negNum:                    
                    xor ax,ax
                    xor bx,bx
                    xor dx,dx
                    mov bx,10
                    push cx    
	 recChar:
                    xor ax,ax
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
                    add dx,ax
                    pop cx
                    add si,cx
                    loop recChar  
                    pop cx
                    mov ax,dx
                    xor dx,dx                    
                    cmp sign,1
                    jz recNegValue
                    pop dx                  
                    cmp ax,0
                    jz chares                    
                    pop cx   
                    pop bx          ;восстанавливаем регистры                       
                    ret 
    recNegValue:
                    ;neg ax
                    pop dx
                    cmp ax,0
                    jz chares
                    push dx
    exit:
                    pop dx
                    pop cx
                    pop bx          ;восстанавливаем регистры
                    ret                
charInput ENDP
printChar proc
                    xor dx,dx;
                    mov bx,cx
    reverse:
                    dec si
                    push [si]
                    loop reverse
                    mov cx,bx
                    mov si,bx
                    xor dx,dx
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
    writeStr:
                    pop dx
                    mov ah,02h
                    int 21h
                    loop writeStr
                    ret
printChar endp
decPrint proc       
                    push cx         ;сохраняем регистры
                    push dx
                    push bx
                    push ax

                    
                    cmp sign,1
                    jnz print
                    ;neg ax
                    xor dx,dx                                   ; перевод из ax в строку буфера приёма es:di                   
                    print: 
                                    ;es:di - адрес буфера приемника
                    mov bx,10          ; основание системы
                    xor cx,cx       ; длина числа
    divNum:
                    xor dx,dx       ; dx = 0
                    div bx          ; dx = mod(ax, bx)
                    push dx         ; сохраняем dx в стек
                    inc cx          ; for LOOP
                    cmp ax,0        ;test ax,ax      ; ax and ax = 0? : ZF = 1
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

                    pop ax
                    pop bx          ;восстанавливаем регистры
                    pop dx
                    pop cx
                    ret
decPrint endp
signer proc
signer endp
start:
	                mov ax,@data	;настраиваем сегментные регистры
                	mov ds,ax
                    mov es,ax

                    mov     ah,     09h             ;input number 1
                    lea     dx,     [str1]
                    int 21h
                    lea cx, initStr
                    call charInput 
                    cmp sign,1
                    jnz Num1
                    mov isNegVal1,1
                    Num1: 
                                      
                    mov dividend,ax                    ;save number 1
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h  
                    mov     ah,     09h             ;input number 2
                    lea     dx,     [str2]
                    int 21h
                    lea cx, initStr
                    mov dx,1
                    call charInput
                    cmp sign,1
                    jnz Num2
                    mov isNegVal2,1
                    Num2:                    
                    mov divisor ,ax                        ;save number 2
                    mov     ah,     09h
                    lea     dx,     [newStr] ;-
                    int 21h 
                    mov bl,isNegVal1
                    mov sign,bl 
                    cmp bl,1
                    jnz print0
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    print0:
                    mov ax,dividend
                    call decPrint                   ;1num
                    mov     ah,     09h
                    lea     dx,     [divStr]
                    int 21h
                    
                    mov bl,isNegVal2
                    mov sign,bl
                    cmp bl,1 
                    jnz print1
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    print1:
                    mov ax,divisor
                    call decPrint                   ;2num
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    xor dx,dx
                    mov ax,dividend
                    div divisor
                    mov remnant,dx
                    xor bx,bx
                    xor cx,cx
                    mov bl,isNegVal1
                    mov cl,isNegVal2

                    cmp bl,cl
                    jz print2
                    xor cx,cx
                    push ax
                    mov cx,ax
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    
                    mov ax,cx
                    pop ax
                    print2:call decPrint                   ;1num / 2num

                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    
                    mov bl,isNegVal1
                    mov sign,bl 
                    cmp bl ,1
                    jnz print3
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    print3:
                    mov ax,dividend
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [remStr]
                    int 21h
                    
                    mov bl,isNegVal2
                    mov sign,bl
                    cmp bl ,1 
                    jnz print4
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    print4:
                    mov ax,divisor
                    call decPrint
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h
                    
                    mov bl,isNegVal1
                    mov sign,bl 
                    cmp bl ,1
                    jnz print5
                    mov     ah,     09h             ;input number 1
                    lea     dx,     [minS];-
                    int 21h
                    print5:
                    mov ax,remnant
                    call decPrint 

                    mov     ah,     09h
                    lea     dx,     [msgPressAnyKey]
                    int     21h
                    mov     ah,     00h             ; ожидание ввода пользователя
                    int     16h  

                    mov ax,4c00h
                    int 21h
end start                    
