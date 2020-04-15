
section .data
	fmt: db "%lf %lf", 0
	p_fmt: db "%lf %lf", 0xA, 0

section .bss
	var1: resb 8
	var2: resb 8

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
	movq xmm0, qword [var1]
	movq xmm1, qword [var2]
	mov rax, 2
	call printf
	pop rbp
	ret