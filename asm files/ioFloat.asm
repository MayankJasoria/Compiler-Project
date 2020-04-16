
section .data
	fmt: db "%f %f", 0
	p_fmt: db "%f %f", 0xA, 0

section .bss
	var1: resb 4
	var2: resb 4

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

	mov rax, var1
	mov rbx, var2

	sub rsp, 8
	fld dword[rax]
	fstp qword[rsp]
	mov rax, qword[rsp]
	add rsp, 8

	sub rsp, 8
	fld dword[rbx]
	fstp qword[rsp]
	mov rbx, qword[rsp]
	add rsp, 8

	movq xmm0, rax
	movq xmm1, rbx
	mov rax, 2
	call printf
	pop rbp
	ret