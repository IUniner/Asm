.model small
.data
str1 db 13,10,"Enter first number: $"
str2 db 13,10,"Enter second number: $"
n1	dw 0
n2	dw 0
buf1	db 13,10,10 dup('$')
.stack 200h
.code

start:
mov  bx,3
int  10h
push 0B800h
pop  es
xor  di,di
 
a:
						xor bx,bx
						int 16h
  						cmp al,8
  						je backspace
						cmp al,13
  						je exit
    					mov ah,7
  						stosw;lea ax, es:[di]
  						dec al
						jz exit
    					jmp a
backspace:
					  	
						sub di,2
    					mov word ptr es:[di],' '	;стирает символ, перемещаеткурсор на позицию назад без символа
						jmp a
ret
exit:
xor bx,bx
int 20h

 
end start