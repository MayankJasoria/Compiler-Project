
section .data
	fmt: db "%hd %hd", 0
	p_fmt: db "%hd %hd", 0xA, 0

section .bss
	var1: resb 2
	var2: resb 2
	forrsp: resq 1

section .text
	global main
	extern printf, scanf

main:
	
	sub rsp, 12
	mov ax, [var1]
	mov word [rsp], ax

	;mov r11, rsp
	mov qword [forrsp], rsp
	and rsp, 0xfffffffffffffff0
	add rsp, 10000B


	;push rdx
	;push rbp
	mov rdi, fmt
	mov rsi, var1
	mov rdx, var2
	mov rax, 0
	call scanf
	;pop rbp
	;pop rdx
	mov rsp, qword [forrsp]
	add rsp, 12

	push rbp
	mov rdi, p_fmt
	mov si, word [var1]
	mov dx, word [var2]
	call printf
	pop rbp
	ret