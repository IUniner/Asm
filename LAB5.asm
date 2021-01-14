model small
.data

    endl db 0dh, 0ah, '$'
    er db 'Bad input','$'
    matrix0 dw 100 dup('$')
    matrix1 dw 100 dup('$')
    rows dw ?
    elem_size dw 2

.code
init proc
    mov ax, @data
    mov ds, ax
    mov es, ax
ret
init endp

Input proc
    mov bx, 10
    xor dx, dx

    Lab:
    mov ah, 01h
    int 21h
    xor ah, ah
    cmp al, 0dh
    jz Final
    cmp al,0ah
    jz Final
    cmp al,20h
    jz Final
    cmp al, '0'
    jb Error
    cmp al, '9'
    ja Error
    mov cl, al
    sub cl, '0'
    mov ax, dx
    mul bx
    add ax, cx
    mov dx, ax
    jmp Lab

    Error:
    call errror
    
    Final:
    mov ax, dx
    ret
Input endp

decPrint proc 
      
                    push cx         ;сохраняем регистры
                    push dx
                    push bx
                    push ax

                    
                    ;cmp sign,1
                    ;jnz print
                    ;neg ax
                    xor dx,dx                                   ; перевод из ax в строку буфера приёма es:di                    
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

    mov dx,' '
    mov ah,02h
    int 21h

                    pop ax
                    pop bx          ;восстанавливаем регистры
                    pop dx
                    pop cx
                    ret
decPrint endp

Output proc
     mov bx, 10
    mov cx, 0

    cyc:
    mov dx, 0
    div bx
    push dx
    inc cx
    cmp ax, 0
    jnz cyc    

    mov ah, 02h
    print:
    pop dx
    add dl, '0'
    int 21h
    loop print

    mov dx,' '
    mov ah,02h
    int 21h

    xor dx, dx
    xor ax,ax
    xor bx,bx
    xor cx,cx

    ret
Output endp

errror:
    lea dx,endl
    mov ah,09h
    int 21h
    lea dx, er
    mov ah,09h
    int 21h
    call exit
ret
exit:
    mov ax, 4c00h
    int 21h
ret

main:
    call init

    call Input
    mov rows, ax

    mul ax
    mov si, ax

input_cycle:

    call Input
    mov matrix0[di],ax
    mov matrix1[di],ax
    add di, 2
    dec si
    cmp si, 0

    jnz input_cycle

    xor si,si

; mov bx, 0
; mov di, rows
; sub di, 1
; external:
; xor bx,bx
; intern:

; mov di,rows
; dec di
; sub di,si
; mov ax,matrix1[si][bx]
; mov matrix0[bx][di],ax
; mov ax, matrix0[si][bx]
; push bx
;     call decPrint
;     pop bx
; inc bx
; cmp bx,rows
; jl intern

;  mov ah, 09h
; mov dx, offset endl
; int 21h
; inc si
; cmp si,rows
; jl external

    mov bx, 0
    mov di, rows
    sub di, 1

external:

    push bx
    iternal:
        mov ax, rows
        mul di
        mov bx,2
        mul bx
        mov bx,ax

        mov cx,bx

        pop bx
        mov ax, bx    
        push bx

        mov bx,2
        mul bx
        mov si,ax

        mov bx,cx

        mov ax, matrix0[bx][si]
        call Output

        dec di
        mov cx, di
        and di, 8000h
        mov di,cx
    jns iternal
    pop bx

    lea dx, endl
    mov ah, 09h  
    int 21h

    mov di, rows
    sub di, 1
    inc bx
    cmp bx, rows
    jc external

    call exit
end main