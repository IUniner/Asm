.model small
.stack 100h
.data
a dw ?
b dw ?
ost dw ?
first db "a=$"
second db "b=$"
solve db "a/b=$"
ostatok db "a%b=$"
deci dw ?
stat dw 10
over dw ?
x dw ?
minus1 dw ?
minuses dw ?
m1 dw ?
m2 dw ?
.code
.386

input proc
                    ;Число помещается в регистр bX
        push ax
        push cx
        push dx
        mov bx,0000 ;введенное число
        mov cx,0000 ;количество помещений в стек
        mov deci,0001    ;множитель
	mov over, 0 ;ячейка для создания числа
	mov minus1, 0
	mov x, 0
read:    
	mov ah, 08h 
        int 21h ;    
	cmp al, 13 ;если введен символ enter и в al код 13
	je processing ;переход на обработку числа.

	cmp al, 8 ;если введен символ back_space и в al код 8
	je back_space

	cmp al, 27 ;если введен символ else и в al код 27
	je delete

	cmp al, 45 ;если введен символ - и в al код 45
	je minus
        
        sub al, '0'
	jc read ;если после вычитания кода 0 осталась цифра(число) меньшее 0, то число введено неверно
	cmp al, 10
	jnc read

	;cmp al, 0
	;jnz c3
	;cmp cx, 0
	;jnz c3
	;mov x, 0
	;jmp read

	mov ah,0 ;проверяем переполнение при умножении
	push ax 
	mov dx, 0
	mov ax, over
        mul stat
	cmp dx,0 ;если произошло переполнение
	jne warning

	mov dx, 0 ;проверяем переполнение при сложении
	pop bx
	add ax, bx
	jc warning

	mov over, ax
	mov ax, bx
	mov bx, 0
	
	mov ah,0
        push ax     ;поместить цифру в стек.
        inc cx      ;увеличить счетчик на 1.

	mov dl, al
	add dl, '0' ;преобразуем цифру в код для вывода символа
	mov ah, 02h
	int 21h ;выводим новую цифру на экран
        jmp read     ;переход на ввод новой цифры.

;------------------ получение числа --------------------
	mov bx, 0
processing:    
	mov ax, 0
	pop ax           ;достать цифру из стека.
	mul deci
        add bx, ax       ;прибавить произведение к результату.
        jc delete
	mov ax, deci
	mov deci, 10
        mul deci
        mov deci, ax     ;поместить новый множитель в deci.
        dec cx
	jnz processing  ;извлечь очередную цифру. 
	jmp ended
minus:
	cmp minus1, 1
	je read
	cmp cx, 0
	jne read
	mov minus1, 1
	mov dl, '-'
	mov ah, 02h
	int 21h
	jmp read
warning:
	mov dx,0
	mov over, 0
	jmp delete
delete:
	cmp cx, 0
	jne c4
	cmp minus1, 0
	je read
	mov minus1, 0

	mov dl, 8
	mov ah, 02h
	int 21h
	mov dl, ' '
	int 21h
	mov dl, 8
	int 21h ;
	jmp delete

	c4:
	pop ax
	mov dl, 8
	mov ah, 02h
	int 21h
	mov dl, ' '
	int 21h
	mov dl, 8
	int 21h ;перемещаем курсор выводим пробел и опять перемещаем курсор, "стирая символ"
	dec cx
	jmp delete
back_space:
	cmp cx, 0 
	je read ;Если в стеке нет числа, то нельзя удалить символ
	dec cx
	pop ax
	mov dl, 8
	mov ah, 02h
	int 21h
	mov dl, ' '
	int 21h
	mov dl, 8
	int 21h ;перемещаем курсор выводим пробeл и опять перемещаем курсор, "стирая символ"
	jmp read
ended:
        pop dx
        pop cx
        pop ax
ret
input endp

output proc
                    ;Число находится в регистре BX. 
        push ax
	push cx
	push dx    
        mov ax, bx
        mov bx, 0
        mov cx, 0;
process:    
	mov dx, 0
	div stat
	inc cx
	push dx
	cmp ax, 0
	jne process    ;Получение следующей цифры.
vyvod:    
	pop dx
	add dl, '0'
	mov ah, 02
        int 21h
	loop vyvod
        pop dx
        pop cx
        pop ax
ret
output endp

main:
	mov ax, @data
	mov ds, ax
	mov minuses, 0
	mov m1, 0
	mov m2, 0
firstnumb:
	lea dx, first
	mov ah, 09h
	int 21h
	call input
	mov a, bx ;помещаем в а первое число
	mov ax, minus1
	mov m1, ax ;есть ли у первого числа знак

	cmp minus1, 1
	jne secondnumb
	add minuses, 1
	;call output
	
secondnumb:

	nenull:
		mov dl, 10
		mov ah, 02h
		int 21h
		mov dl, 13
		int 21h
		lea dx, second
		mov ah, 09h
		int 21h
		call input
		mov b, bx
		cmp b, 0
		je nenull
	
	mov ax, minus1
	mov m2, ax
	cmp minus1, 1
	jne solving
	add minuses, 1
	;call output
	
solving:
	mov dl, 10
	mov ah, 02h
	int 21h
	mov dl, 13
	int 21h

	lea dx, solve ;вывод частного
	mov ah, 09h
	int 21h
	mov dx, 0
	mov ax, a
	div b
	mov ost, dx
	mov bx, ax ;частное
	;mov bx, a

	cmp minuses,1 ;если один минус
	jne case3
	mov dl, '-'
	mov ah, 02h
	int 21h
	cmp ost, 0 ;если один минус и остаток 0, то выводим как положительное
	je plus
	cmp m1, 1 ;если было отрицательным первое, то все ок, а если нет, то обрабатываем остаток
	jne case2 
	add bx, 1 ;к частному прибавляем 1 и моифицируем остаток
	mov ax, b
	sub ax, ost
	mov ost, ax
	jmp plus
case2:
	
case3:
	cmp minuses, 2 ;если 2 минуса
	jne plus
	cmp ost, 0 ;если один минус и остаток 0, то выводим как положительное
	je plus
	add bx, 1
	mov ax, b
	sub ax, ost
	mov ost, ax
plus:
	call output ;выводим результат деления
	mov dl, 10
	mov ah, 02h
	int 21h
	mov dl, 13
	int 21h

	lea dx, ostatok
	mov ah, 09h
	int 21h
	mov bx, ost
	call output

	mov dl, 10
	mov ah, 02h
	int 21h
	mov dl, 13
	int 21h

	mov ax, 4c00h
	int 21h

end main