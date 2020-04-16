
section .data
	fmt: db "%hd %hd", 0
	p_fmt: db "%hd %hd", 0xA, 0

section .bss
	var1: resb 2
	var2: resb 2

section .text
	global main
	extern printf, scanf

main:
	mov rdx, -2
	cmp al, 0
	jz l2
l2:	
	ret