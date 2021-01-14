   .286
    .model small
    .code
    org 100h
main:   jmp beg
 
; переменные удобнее размещать в cseg, хотя код немного длиннее
; потому что не приходится загружать DS в подпрограмме прерывания
 
old21   label dword ; именно dword, а не word
old21ip dw 0
old21cs dw 0
str2 db "Hi$"
 
New21: 
        pushf      ; вызов old21, не надо делать popf
        call cs:old21
    pushf      ; сохраняем регистры
    push ds
    push es
    pusha
    call mysub ; выполняем свою подпрограмму
    popa       ; восстанавливаем регистры
    pop  es
    pop  ds
    popf
        retf 2     ; завершение retf 2, а не iret
                   ; т к int 21h возвращает Carry Flag
 
mysub: mov ax,0E07h ; bell - пискнуть динамиком
       int 10h
       ret
 
beg:   push cs
       pop  ds
 
       ;save
       mov      ax,3521h
       int      21h
       mov      word ptr old21ip, bx
       mov      word ptr old21cs, es
       ;install
       mov      ax,2521h
       mov      dx,offset New21
       int      21h
       ;use
       mov      ah,09h
       mov      dx,offset str2
       int      21h
       ;restore
       lds      dx,old21 ; спец короткая команда грузит ds и dx
       mov      ax,2521h
       int      21h
       MOV      ax, 4C00h ; программа возвращает код ошибки 0
       INT      21h
end main