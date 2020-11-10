.model small
.stack 200h
.data
                    strMLen  =  128
                    newStr   db 10,13,'$' 
                    initStr  db strMLen, strMLen dup ('$') 
                    str1    db 13," Enter first number: $"     ;13 - space, 10-enter
                    str2    db " Enter second number: $"

                    eachr    db 0

                    n2      dw 0
                    buf1     db 13,10,24 dup('$')
                    buf      db 8,10 dup(0)

                    strLen   db ?
                    blockLen db ?
                    blockNum db ?
.code
decPrint proc                       ; перевод из ax в строку буфера приёма es:di
                    push cx         ;сохраняем регистры
                    push dx
                    push bx
                    push ax
                                    ;es:di - адрес буфера приемника
                    mov bx,10       ; основание системы
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
start:
	                mov ax,@data	;настраиваем сегментные регистры
                	mov ds,ax
                    mov es,ax

                    xor dl,dl
                    lea cx, initStr
                    mov si, cx

                    xor cx,cx;!

charEnteringStr:
                    mov ah,01h
                    int 21h
                    push ax
                    cmp al,10
                    jz finish
                    cmp al,13
                    jz finish
                    mov [si+1],al
                    inc dl
                    inc si
                    inc cx ;!
                    jmp charEnteringStr
finish:
                    mov cx,dx;!
                    xor dx,dx;!
                    ;!lea dx,si
                    mov ax,cx
writeStr:
                    pop dx
                    ;add dl,'1'
                    ; SI:DI <- full str
                    mov ah,02h
                    int 21h
                    loop writeStr



count:
                    inc eachr
                    xor ax,ax
                    mov al,strLen
                    div eachr
                    cmp ah,0            ;test ah,ah
                    jnz count

                    mov blockLen,al
                    mov al,strLen
                    cmp eachr,al
                    jz exit

                    mov blockNum,0
exchng:
                    inc blockNum
                    mov al,blockLen
                    cmp blockNum,al
                    jz exit
                    lea si, initStr+2
                    lea di, initStr+2
                    mov al,eachr
                    mul blockNum
                    add di,ax
                    xor cx,cx
                    mov cl,eachr
                    repe cmpsb          ; cmp ES:SI and ES:DI (byte)
                    jnz count
                    jmp exchng
exit: 
                    xor ax,ax
                    mov al,eachr

                    call decPrint
                    mov ax,4c00h
                    int 21h
end start                    
