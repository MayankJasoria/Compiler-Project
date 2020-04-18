
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
	
	mov ebx, 0	 ;return 0 status on exit - 'No errors'\n");
	mov eax, 1
	int 80h		 ;generate interrupt\n");
	ret