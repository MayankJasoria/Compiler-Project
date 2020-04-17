
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
	push ax
	pop ax	
	and al, bl
	sub rsp, 2
	mov word [rsp], 103d
	add rsp, 2
	sub rsp, 1
	mov byte [rsp], 1
	add rsp, 1
	;mov	rbx,0		; exit code, 0=normal
	;mov	rax,1		; exit command to kernel
	;int	0x80
	ret