
section .data
	fmt: db "%c %c", 0
	p_fmt: db "%s", 0xA, 0
	msg: db "Bye World! %s", 0xA, 0
	par: db "Integer", 0

section .bss
	var1: resb 1
	var2: resb 1

section .text
	global main
	extern printf, scanf

main:
	push rbp
	;mov rdi, msg
	;mov rsi, par
	mov rdi, par
	call printf
	pop rbp
	ret