 $mod51
row0 equ p2.0
row1 equ p2.1
row2 equ p2.2
col0 equ p2.5
col1 equ p2.6
col2 equ p2.7
org 00h
	mov p2,#07h
ag1:	clr col0
	setb col1
	setb col2
	jb row0,r11
	mov p1,#01h
	sjmp ag
r11:	jb row1,r22
	mov p1,#04h
	sjmp ag
r22:	jb row2,r33
	mov p1,#07h
	sjmp ag
r33:	setb col0
	clr col1
	setb col2
	jb row0,r44
	mov p1,#02h
	sjmp ag
r44:	jb row1,r55
	mov p1,#05h
	sjmp ag
r55:	jb row2,r66
	mov p1,#08h
	sjmp ag
r66:	setb col0
	setb col1
	clr col2
	jb row0,r77
	mov p1,#03h
	sjmp ag
r77:	jb row1,r88
	mov p1,#06h
	sjmp ag
r88:	jb row2,ag1
	mov p1,#09h
	sjmp ag
ag:	sjmp ag1
	end