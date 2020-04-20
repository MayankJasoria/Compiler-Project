; --- START: init code and data --- 
section .data
	fmt_float: db "%f", 0
	fmt_int: db "%hd", 0
	fmt_string: db "%s", 0
	fmt_bool: db "%hhu", 0
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
	rte_oob: db "RUN TIME ERROR: Array index out of bounds at line %hd.", 0xA, 0
	rte_type: db "RUN TIME ERROR: Dynamic array type checking failed on line %hd.", 0xA, 0
	rte_param: db "RUN TIME ERROR: Dynamic array type checking failed on function reuse parameter passing on line %hd.", 0xA, 0
	rte_invalidbounds: db "RUN TIME ERROR: Invalid dynamic array bounds on line %hd.", 0xA, 0
section .bss
	buffer: resb 64
	dynamic: resw 1
	rspreserve: resq 1
section .text
	global main
	extern printf
	extern scanf
; --- END: init code and data --- 

; ### Begin of a moduledef. ### 
lol:
mov word [dynamic], 0
	mov ax, 6d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 24, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 26d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 24, rhsoff = 0, type = Integer ---
	mov ax, 7d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 26, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 28d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 26, rhsoff = 0, type = Integer ---
	mov ax, 8d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 28, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 30d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 28, rhsoff = 0, type = Integer ---
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 24d
	mov word [dynamic], 0
; --- START: takeInput(): type: Integer, Name: s1 --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	mov r9, 2d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: s1 --- 
; --- START: takeInput(): type: Integer, Name: s2 --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	mov r9, 4d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: s2 --- 
; --- START: takeInput(): type: Integer, Name: s3 --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	mov r9, 6d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: s3 --- 
; --- START: takeInput(): type: Integer, Name: s4 --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	mov r9, 8d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: s4 --- 
	mov rax, rbp
	sub rax, 16d
	mov qword [rax], rsp
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov rsi, 17d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_0:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_0
	mov word [dynamic], r9w
	mov rax, rbp
	sub rax, 24d
	mov qword [rax], rsp
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 6d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 8d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov rsi, 18d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_1:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_1
	mov word [dynamic], r9w
	mov rax, rbp
	sub rax, 24d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
	mov rsi, 20d
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov r8w, r10w
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 6d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 8d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	cmp r8w, r10w
	jnz typeError
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov r8w, r11w
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 6d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 8d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	cmp r8w, r11w
	jnz typeError
; --- START: moveOffsetToOffset(): lhsoff = 8, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 16d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 8, rhsoff = 0, type = Array ---
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 16d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 22d
mov r8w, 10d
cmp r8w, r10w
jnz param
mov r8w, 14d
cmp r8w, r11w
jnz param
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	mov rcx, qword [rbp]
	sub rcx, 24d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 6d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 8d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 22d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	sub rsp, 6d
	call lol
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
	mov rdx, rbp
	sub rdx, 2d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 26d
	mov cx, word [rax]
	mov word [rdx], cx
	mov rdx, rbp
	sub rdx, 4d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 28d
	mov cx, word [rax]
	mov word [rdx], cx
	mov rdx, rbp
	sub rdx, 6d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 30d
	mov cx, word [rax]
	mov word [rdx], cx
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 2d
	mov rdx, rbp
; --- START: outputArrayElement() for s1 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: outputArrayElement() for s1--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 4d
	mov rdx, rbp
; --- START: outputArrayElement() for s2 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: outputArrayElement() for s2--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 6d
	mov rdx, rbp
; --- START: outputArrayElement() for s3 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
; --- END: outputArrayElement() for s3--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 24d
	ret

; ### End of driver function. ### 
rte:
	mov ebx, 0	 ;return 0 status on exit - 'No errors'
	mov eax, 1	 ;invoke SYS_EXIT system call (kernel opcode 1)
	int 80h		 ;generate interrupt

oob:
	push rbp
	mov rdi, rte_oob
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	jmp rte

typeError:
	push rbp
	mov rdi, rte_type
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	jmp rte

param:
	push rbp
	mov rdi, rte_param
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	jmp rte

invalidbounds:
	push rbp
	mov rdi, rte_invalidbounds
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rax
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rbp
	jmp rte
