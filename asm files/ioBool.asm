
section .data
	fmt: db "%c %c", 0
	p_fmt: db "%c %c", 0xA, 0

section .bss
	var1: resb 1
	var2: resb 1

section .text
	global main
	extern printf, scanf

main:
	push rbp
	mov rdi, fmt
	mov rsi, var1
	mov rdx, var2
	call scanf
	pop rbp

	push rbp
	mov rdi, p_fmt
	movzx si, byte [var1]
	movzx dx, byte [var2]
	call printf
	pop rbp
	ret