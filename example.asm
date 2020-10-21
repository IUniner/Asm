.model small
.stack 100h
.data
a dw 5
b dw 6
.code

main:
mov ax,@data
mov ds,ax

mov ax,a
add ax,b

mov ax,4c00h
int 21h
end main