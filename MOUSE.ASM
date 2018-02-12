.model small
.data
msg1 db 0ah,0dh,"Mouse initialized$"
msg2 db 0ah,0dh,"Mouse not found$"

.code
start:
mov ax,@data
mov ds,ax

mov ax,0000h
int 33h
cmp ax,0000h
jne equal

lea dx,msg2
mov ah,09h
int 21h

equal:
lea dx,msg1
mov ah,09h
int 21h

mov ah,4ch
int 21h
end start
