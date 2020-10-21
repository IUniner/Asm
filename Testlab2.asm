.model small
.data
str1	db 13,10,"введите первое число: $"
str2	db 13,10,"введите второе число: $"
n1	dw 0
n2	dw 0
buf1	db 13,10,10 dup('$')
.stack 200h
.code
start:
	mov ax,@data	;настраиваем сегментные регистры
	mov ds,ax
	mov es,ax
	mov dx, offset str1
	call InputNumber
	mov n1,ax
	mov dx, offset str2
	call InputNumber
	mov n2,ax
	add ax,n1
	lea di,buf1+2
	call printdec
	lea dx,buf1+2
	mov ah,9
	int 21h
	
ex:	mov ax,4c00h	;выход из программы
	int 21h


str2dw	proc ;Преобразование строки в число
			
			;на входе ds:si ссылается на ASCIIZ строку, которую нужно преобразовать
			; на выходе в ax - число.
	push bx
	push dx
	push si
	xor bx,bx
	xor dx,dx	;сумма
@lp1:	xor ax,ax
	lodsb		;берем чимвол
	test al,al	;если это нулей байт, то заканчиваем
	jz @ex
	cmp al,'-'	;если минус, то устанавливаем признак минуса
	jnz @m1
	mov bx,1
	jmp @lp1
@m1:	cmp al,'9'	;Если это не цифра, то пропускаем
	jnbe @lp1
	cmp al,'0'      ;Если это не цифра, то пропускаем
	jb @lp1
	sub ax,'0'	;получаем цифровое значение
	shl dx,1	;умножаем сумму на 10
	add ax, dx
	shl dx, 2
	add dx, ax	;прибавляем текущее значение
	jmp @lp1
@ex:	test bx,bx	;если установлен признак отрицательного числа
	jz @ex1
	neg dx		;то меняем знак
@ex1:	mov ax,dx
	pop si
	pop dx
	pop bx
	ret
str2dw	endp

InputNumber	proc	; функция выводит на экран сообщение и ожидает ввода числа
			; ds:dx - сообщение, которое следует вывести
			; возвращает:
			; ax - введенное число
	push dx		; сохраняем регистры
	push si
	push di
	mov ah,9
	
	int 21h
	mov ah,0ah	
	mov dx,offset buf
	int 21h		;пользователь вводит в текстовом виде в buf значение элемента массива
	mov di,offset buf+1
	mov al,[di]	;берем длину введенной строки
	mov ah,0	;ах=длине
	inc di	;начало введенной строки в памяти
	mov si,di		;сохраняем это значение
	add di,ax               ;конец введенной строки в памяти                 
	mov [di],byte ptr 0     ;ставим нулевой байт за последним символом строки
	call str2dw		;преобразовываем строку в значение
	pop di		;восстанавливаем регистры
	pop si
	pop dx
	ret
buf 	db 8, 10 dup(0)	;принимает строку, введенную с клавиатуры
InputNumber	endp



printdec proc	;преобразование числа из ах в десятичную строку по адресу es:di
		;ax - число
		;es:di - адрес буфера приемника
	push cx	;сохраняем регистры
	push dx
	push bx
	mov bx,10	;основание системы
	XOR CX,CX	;в сх будет количество цифр в десятичном числе
@@m1:	
	XOR dx,dx
	DIV bx		;делим число на степени 10
	PUSH DX		;и сохраняем остаток от деления(коэффициенты при степенях) в стек
	INC CX
	TEST AX,AX
	JNZ @@m1
@@m2:	
	POP AX
	ADD AL,'0'	;преобразовываем число в ASCII символ
	STOSb		;сохраняем в буфер
	LOOP @@m2		;все цифры
	pop bx		;восстанавливаем регистры
	POP dx
	POP cx
	RET
printdec endp


end start

