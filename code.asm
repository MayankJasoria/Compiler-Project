; --- START: init code and data --- 
section .data
	fmt_float: db "%f", 0
	fmt_int: db "%hd", 0
	fmt_string: db "%s", 0
	fmt_bool: db "%c", 0
	single_space: db " ", 0
	end_line: db "", 0xA, 0
	type_int: db "Integer", 0
	type_float: db "Real Number", 0
	type_bool: db "Boolean", 0
	op1: db "Input: Enter an %s Value", 0xA, 0
	op2: db "Input: Enter %d array elements of %s type for range %d to %d", 0xA, 0
	output_fmt_float: db "Output: %f", 0xA, 0
	output_fmt_int: db "Output: %hd", 0xA, 0
	output_fmt_string: db "Output: %s", 0xA, 0
	output_fmt_plain: db "Output: ", 0
	bool_true: db "true", 0
	bool_false: db "false", 0
	except_fmt: db "RUN TIME ERROR: Array index out of bounds at line %d."
section .bss
	buffer: resb 64
	dynamic: resw 1
	rspreserve: resq 1
section .text
	global main
	extern printf
	extern scanf
; --- END: init code and data --- 

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 20d
	mov word [dynamic], 0
	mov rax, rbp
	sub rax, 8d
	mov rcx, rax
	mov qword[rcx], rax
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 15d
; --- END: got left and right index of A in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_int
	movsx rcx, r10w
	movsx r8, r11w
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 8d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_0:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_0
; --- END: takeInput(): type: Array, Name: A --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 15d
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is not NULL --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov r8w, 11d
	mov rax, rbp
	sub rax, 8d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_1:
	add r9w, r8w
	dec rcx
	jnz label_1
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: outputArrayElement() for A--- 
; --- END: giveInput() --- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 20d
	ret

; ### End of driver function. ### 
rte:
	mov ebx, 0	 ;return 0 status on exit - 'No errors'
	mov eax, 1	 ;invoke SYS_EXIT system call (kernel opcode 1)
	int 80h		 ;generate interrupt
