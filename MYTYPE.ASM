.model small
.data
msg1 db 0Ah,0Dh,"File found$"
msg2 db 0Ah,0Dh,"File not found$"
msg3 db 0Ah,0Dh,"b.txt: $"
buff db 100 dup('$')
buff2 db 100 dup('$')
fname db 'a.txt',0
fname2 db 'b.txt',0
fhandle dw ?
fhandle2 dw ?

.code
START:
mov ax,@data
mov ds,ax

mov ah,3dh    ;opening the file - fname
mov al,2
lea dx,fname    ;required by code, no logic here
int 21h
jc error
mov fhandle,ax
lea dx,msg1
mov ah,09h
int 21h

mov ah,3dh
mov al,2
lea dx,fname2
int 21h
jc error
mov fhandle2,ax
lea dx,msg1
mov ah,09h
int 21h

mov ah,3fh      ;reading file
lea dx,buff     ;code - no logic
mov bx,fhandle    ;fhandle was generated when we opened the file
mov cx,100
int 21h         ;read 100 bytes were stored in buff (some file pointer stuff)
jc error

lea dx,buff
mov ah,09h
int 21h
            ;so we read the file a.txt, and displayed its contents

;writing the read file from a.txt to b.txt via buffer
mov ah,40h
lea dx,buff
mov bx,fhandle2
mov cx,100
int 21h

;reading file b.txt
mov ah,3fh
lea dx,buff
mov bx,fhandle2
mov cx,100
int 21h
jc error
lea dx,msg3
mov ah,09h
int 21h
lea dx,buff
mov ah,09h
int 21h


exit:
mov ah,4ch
int 21h

error:
lea dx,msg2
mov ah,09h
int 21h
jmp exit

end start
