
section .data
	fmt: db "%f %f", 0
	p_fmt: db "%f", 0xA, 0

section .bss
	var1: resb 4
	var2: resb 4

section .text
	global main
	extern printf, scanf

main:

	push rbp
	mov rdi, p_fmt
	sub rsp, 4
	mov dword [rsp], __float32__(2.34)
	cvtss2sd xmm0, [rsp]
	add rsp, 4 
	mov rax, 1
	call printf
	pop rbp
	ret