
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
	sub rsp, 8
	add rsp, 8
	ret