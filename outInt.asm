
section .data
	fmt: db "%hd %hd", 0
	p_fmt: db "%hd", 0xA, 0

section .bss
	var1: resb 2
	var2: resb 2

section .text
	global main
	extern printf, scanf

main:
	;push rbp
	;mov rdi, fmt
	;mov rsi, var1
	;mov rdx, var2
	;call scanf
	;pop rbp

	push rbp
	mov rdi, p_fmt
	mov rsi, 24
	;mov dx, word [var2]
	call printf
	pop rbp
	ret