model small
.data

endl db 0dh, 0ah, '$'
er db 'Bad input$'
strMlen = 100
initStr         db strMLen, strMLen dup ('$') 

matrix0 dw 100 dup('$')
matrix1 dw 100 dup('$')
i dw 0
j dw 0
rows dw ?
elem_size dw 2


.code

init proc
mov ax,@data
mov ds,ax
mov es,ax
init endp

Input proc


    mov bx, 10
    xor dx, dx

 resetLen:    
                    ;mov bx,5
                    jmp Lab
escape:
                    jcxz resetLen       ;
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
    Lab:
    xor ax,ax
                    mov ah, 08h 
                    int 21h          ;
                    cmp al,8
                    jz backspace
                    cmp al, 27
                    jz escape
                    cmp al, 0dh
    jz final
    cmp al,0ah
    jz final
    cmp al,20h
    jz final
                    cmp al,57
                    jg Lab
                    cmp al,48
                    jl Lab
                    ;cmp cx,bx
                    ;jz charEnteringStr                    
                    ; mov [si],al
                     ; inc si
                    ; inc cx
                    ; mov dx,ax
                    ; inc cx
                    ; inc si
;                     push cx
 push ax
; push dx
                    mov cl, al
    sub cl, '0'
    mov ax, dx
    mul bx
    add ax, cx
    mov cx,ax
       ;mov dx, cx 
    pop dx         
                    mov ah,02h
                    int 21h   
                    mov dx,cx      
                    ;pop cx                                          
                    jmp Lab
    ; mov cl, al
    ; sub cl, '0'
    ; mov ax, dx
    ; mul bx
    ; add ax, cx
    ; mov dx, ax
    ; jmp Lab


    ; Error:
    ; mov ah, 09h
    ; mov dx, offset endl
    ; int 21h
    ; mov ah, 09h
    ; mov dx, offset er
    ; int 21h
    ; mov al, 0
    ; mov ah, 4ch
    ; int 21h
    
    final:
    mov ax, dx
    
    ret
Input endp

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

; start:
;     call init
;     push offset matrix
;     call matrix_input
;     pop dx
    
;     push offset matrix
;     call matrix_sort
;     pop dx
    
;     push offset matrix
;     call matrix_output
;     pop dx

;     call exit
; end start

main:

mov ax,@data
mov ds,ax

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

;si,bx,di

; si = i, bx = j, di = n -1 -i

; external:
; xor bx,bx
; intern:

; mov di,rows
; dec di
; sub di,si
; mov ax,matrix1[si][bx]
; mov matrix0[bx][di],ax
; mov ax, matrix0[si][bx]
;     call Output
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

mov ah, 09h
mov dx, offset endl
int 21h

mov di, rows
sub di, 1
inc bx
cmp bx, rows
jc external

xor  ax, ax
mov  ah,4ch
int 21h

end main