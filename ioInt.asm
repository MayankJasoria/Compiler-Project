
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
	
	sub rsp, 12
	mov ax, [var1]
	mov word [rsp], ax
	;sub rsp, 4
	;add rsp, 2

	push rbp
	mov rdi, fmt
	mov rsi, var1
	mov rdx, var2
	call scanf
	pop rbp
	add rsp, 16



	;push rbp
	;mov rdi, p_fmt
	;mov si, word [var1]
	;mov dx, word [var2]
	;call printf
	;pop rbp
	ret