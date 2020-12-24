.model small
.stack 200h
.data
                    strMLen         =  100
                    initStr         db strMLen, strMLen dup ('$') 
                    newStr          db 10,13,'$' 
                    str1            db 0Dh,'Enter string: ',0Ah,'$'
                    message         db 'NO','$'
                    YES             db 'YES','$'
                    vectorInt       dw 79 dup (0)
                    testInt            dw 'a','c','a',' ','a','b','a','f','d','f','a','c','a','a','b','a','$'
                    strSize         dw 0
                    part            dw 0
                    string          dw 79 dup ('$')
                    msgPressAnyKey  db 0Ah,'Press any key to exit...', '$'
.code               ; -32768..32767 
charInput PROC
                    push bx
                    push cx         ;сохраняем регистры
                    push dx
                    push ax
                    push si
                    mov strSize,0
                    mov si, cx                    
                    xor dx,dx
                    xor cx,cx
    resetLen:    
                    mov bx,79
                    jmp charEnteringStr
    escape:
                    jcxz resetLen      ;
                    dec si
                    dec strSize
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
                    ;mov strInt,cx               
                    xor dx,dx
                    xor cx,cx
                    jmp resetLen
    backspace:
                    jcxz resetLen
                    dec cx                
                    dec si   
                    dec strSize      
                    mov byte ptr es:[si],' '
                    push si
                    mov si,strSize
                    mov word ptr string[si],' '
                    pop si
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
                    int 21h           ;
                    cmp al,8
                    jz backspace
                    cmp al, 27
                    jz escape
                    cmp al,10
                    jz exit
                    cmp al,13
                    jz exit
                    cmp cx,bx
                    jge charEnteringStr                    
                    mov [si],al
                    push si
                    mov si,strSize
                    mov string[si],ax                                   
                    mov ax,string[si]
                    pop si
                    inc strSize
                    inc si
                    inc cx
                    mov dx,ax
                    mov ah,02h
                    int 21h                                                      
                    
                    jmp charEnteringStr
                        BESC:
                    jmp escape
    exit:
                    pop si
                    pop ax
                    pop dx
                    pop cx
                    pop bx          ;восстанавливаем регистры
                    ret                
charInput ENDP
charOut PROC
                    push dx
                    push si
                    push cx
                    push ax

                    xor dx,dx;
                    xor si,si
                    mov si,0
                    mov cx,strSize
    print0:
                    mov dx,string[si]
                    inc si
                    mov ah,02h
                    int 21h
                    loop print0
                    
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h

                    pop ax
                    pop cx
                    pop si
                    pop dx
                    ret    
charOut ENDP
vectorOut PROC
                    push dx
                    push si
                    push ax

                    xor dx,dx;
                    xor si,si
                    mov si,0
                    mov cx,strSize
    print1:
                    mov dx,vectorInt[si]
                    add dx,'0'
                    inc si
                    mov ah,02h
                    int 21h
                    loop print1
                    
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h

                    pop ax
                    pop si
                    pop dx
                    ret
vectorOut ENDP
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
                    add dx,'0'
                    mov ah,02h
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
kmp proc
                    xor bx,bx
                    xor si,si
                    mov si,1

                    while_ft:
                    cmp si,strSize
                    jge return

                    mov bx,vectorInt[si-1]
                    
                    while_sc:
                        cmp bl,0
                        jle continue
                        xor ax,ax
                        xor cx,cx
                        mov ax,string[bx]
                        mov cx,string[si]
                        cmp al,cl
                        jz continue

                        mov bx, vectorInt[bx-1]
                    jmp while_sc
                    continue:

                    if_ft:
                        xor ax,ax
                        xor cx,cx
                        mov ax,string[bx]
                        mov cx,string[si]
                        cmp al,cl
                        jnz if_exit
                        inc bx
                    if_exit:
                    mov vectorInt[si],bx
                    inc si
                    
                    jmp while_ft
                    return:
                    ret

kmp endp
start:
	                mov ax,@data	;настраиваем сегментные регистры
                	mov ds,ax
                    mov es,ax

                    mov     ah,     09h             ;input number 1
                    lea     dx,     [str1]
                    int 21h 
                    lea cx, initStr
                    call charInput
                    mov     ah,     09h
                    lea     dx,     [newStr]
                    int 21h  

                    call kmp
                    
                    lea     dx,     [message]
                    mov si,0
                    mov ax, strSize
                    mov part,ax
    while_td:
                    mov ax,strSize
                    cmp si,strSize
                    jge while_td_exit
        if_sd:
                    mov ax,string[si]
                    mov bl,' '
                    cmp al,bl
                    jnz if_sd_exit
                    mov part, si
        if_sd_exit:
        if_td:
                    mov ax,vectorInt[si]
                    mov bx,part
                    cmp al,bl                                        
                    jnz if_td_exit 
                    lea     dx,     [YES]
        if_td_exit:
                    inc si
                    jmp while_td
    while_td_exit:
                    call vectorOut

                    mov     ah,     09h
                    int     21h
                    
                    mov     ah,     09h
                    lea     dx,     [msgPressAnyKey]
                    int     21h
                    mov     ah,     00h             ; ожидание ввода пользователя
                    int     16h  

                    mov ax,4c00h
                    int 21h
end start                    
