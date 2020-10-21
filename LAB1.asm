.model small ;lab1
.stack 100h
.data
a dw 1
b dw 2
c dw 3
d dw 4

.code
outint proc
	add ax,3030h
	mov dl,ah
	mov dh,al
	mov ah,02h
	int 21h
	mov dl,dh
	int 21h
	ret
outint endp

main:
mov ax,@data	; ah -> ax, al -> cx
mov ds,ax	; bh -> bx, bl -> dx

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
	
	mov ax, a ; ah or ax
	add ax,b
	add ax,c
	add ax,d
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

		mov ax,a
		xor ax,b
		mov cx,c ; al or cx
		and cx ,d
		xor ax,cx
		jmp if_end
	else_sd:
		mov ax,a
		xor ax,b
		mov cx,c
		and cx,d
		add ax,cx
if_end:

call outint
exit:
mov ax,4c00h ; mov ah,4ch
int 21h
end main
