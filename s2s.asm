.686
.model flat, c
option casemap: none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\kernel32.lib

.data
  str     db 256 dup(0)
  hStdIn  dd 0
  hStdOut dd 0
  slength dd 0
  .const
  sConsoleTitle db 'Input and Output',0		; Заголовок окна консоли. Заканчивается нулём
  prompt db 'Input a string', 13,10		; Приглашение для ввода. Символы с кодами 13 и 10 
						; обеспечивают перевод курсора на следующую строку
  
STD_INPUT_HANDLE  equ -10d			; Определяем символические имена для констант,
STD_OUTPUT_HANDLE equ -11d			; указывающих требуемое устройство

.code
program:
printdec proc	;преобразование числа из ах в десятичную строку по адресу es:di
		;ax - число ; es:di - адрес буфера приемника
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
  ; Вывод заголовка консоли
      push  offset sConsoleTitle		; Кладём в стек адрес начала строки заголовка консоли
      call  SetConsoleTitle			; Вызываем функцию

   ; Получаем идентификатор устройства ввода
      push  STD_INPUT_HANDLE			; Кладём в стек параметр функции GetStdHandle
      call  GetStdHandle			; Вызываем функцию
      mov   hStdIn, eax				; Сохраняем полученный идентификатор

 ; Получаем идентификатор устройства вывода
      push  STD_OUTPUT_HANDLE
      call  GetStdHandle
      mov   hStdOut, eax

  ; Выводим приглашение
      push  0					; Зарезервированный параметр, в стек кладём 0
      push  0					; Указатель на переменную для записи количества выведенных символов,
						; в данном случае не нужен, поэтому в стек кладём 0
      push  10h					; Количество выводимых символов
      push  offset prompt			; Адрес выводимой строки
      push  hStdOut				; Идентификатор устройства вывода
      call  WriteConsole			; Вызываем функцию

  ; Вводим строку
      push  0					; Зарезервированный параметр, в стек кладём 0
      push  offset slength			; Адрес переменной, куда будет записано количество введённых символов
      push  256					; Максимальное количество вводимых символов
      push  offset str				; Адрес для записи введённой строки
      push  hStdIn				; Идентификатор устройства ввода
      call  ReadConsole				; Вызываем функцию

  ; Выводим строку
      push  0
      push  0
      push  slength
      push  offset str
      push  hStdOut
      call  WriteConsole

  ; Задержка
      push  1800h
      call  Sleep
      
      push  0
      call  ExitProcess
end program