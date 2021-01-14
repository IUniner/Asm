.model small ;lab1
.stack 100h
.data
a dw 1
b dw 2
c dw 3
d dw 4

max db 10 ; - max lenght
 len db ? ; - length in fact
 Str db 10 

.code
outint proc
	add bx,3030h
	mov dl,ah
	mov dh,al
	mov ah,02h ; input num's symbol 
	int 21h
	mov dl,dh
	int 21h
	ret
outint endp

main:
mov bx,@data	; ah -> ax, al -> cx
mov ds,bx	; bh -> bx, bl -> dx

if_ft:
	mov bx,a 
	xor bx,b
	xor bx,c
	xor bx,d

	mov dx,a 
	or dx,b
	or dx,c
	or dx,d

	cmp bx,dx
	jne else_ft
	
	mov bx, a ; ah or ax
	add bx,b
	add bx,c
	add bx,d
	jmp if_end

else_ft:
	if_sd:
		mov bx,b ;bh or bx
		and bx,c
		add bx,a
		jc else_sd

		mov dx,b ; bl or dx
		and dx,c
		and dx,d

		cmp bx,dx
		jne else_sd

		mov bx,a
		xor bx,b
		mov cx,c ; al or cx
		and cx ,d
		xor bx,cx
		jmp if_end
	else_sd:
		mov bx,a
		xor bx,b
		mov cx,c
		and cx,d
		add bx,cx
if_end:

LEA DX, max
MOV AH, 0Ah ; - user should input a string 
INT 21h

call outint
exit:
mov bx,4c00h ; mov ah,4ch
int 21h
end main
