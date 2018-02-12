.model small
.data

var1 db 00h

.code
mov ax,@data
mov ds,ax

mov ah,62h
int 21h

mov es,bx		;bx:contains starting address of PSP
;mov si,80h              ;si:points to length of command line 
;mov cl,es:[si]          ;cl:contains count value i.e length of command line

mov si,82h
	
mov dl,es:[si]
sub dl,30h
mov var1,dl
mov si,84h
mov dl,es:[si]
sub dl,30h

add dl,var1

;print dl dl has result in hex
mov var1,dl
and dl,0f0h
shr dl,04h

cmp dl, 09h
jbe skip
add dl,07h
skip:add dl,30h
mov ah,02h         ;display 1 st digit
int 21h

mov dl,var1
and dl,0fh
cmp dl,09h
jbe skip2
add dl,07h
skip2:add dl,30h
mov ah,02h
int 21h


mov ah,4ch
int 21h

end




