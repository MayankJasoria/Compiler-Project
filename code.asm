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
	rte_oob: db "RUN TIME ERROR: Array index out of bounds at line %hd.", 0xA, 0
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
	sub rsp, 7d
	mov word [dynamic], 0
; --- START: takeInput(): type: Integer, Name: x --- 
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
; --- END: takeInput(): type: Integer, Name: x --- 
	mov ax, 19d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 2, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 4d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 2, rhsoff = 0, type = Integer ---
	mov ax, 56d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 4, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 6d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 4, rhsoff = 0, type = Integer ---
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 2d
	mov ax, word [rax]
	cmp ax, 1d
	jnz label_1
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 2d
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 6d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: MUL, type: Integer --- 
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 8d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 8d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 10d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 2, rhsoff = 8, type = Integer ---
	mov rax, rsp
	sub rax, 10d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 4d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 2, rhsoff = 8, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 4d
	mov rdx, rbp
; --- START: outputArrayElement() for y --- 
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
; --- END: outputArrayElement() for y--- 
	jmp label_0
label_1:
	mov rax, rbp
	sub rax, 2d
	mov ax, word [rax]
	cmp ax, 2d
	jnz label_2
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 12d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 3d
	mov rdx, rsp
	sub rdx, 14d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 10, rightOp: 12, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 12d
	mov r10, rsp
	sub r10, 14d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 16d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 10, rightOp: 12, operator: MUL, type: Integer --- 
	mov rax, rbp
	sub rax, 6d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 18d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 14, rightOp: 16, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 16d
	mov r10, rsp
	sub r10, 18d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 20d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 14, rightOp: 16, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 4, rhsoff = 18, type = Integer ---
	mov rax, rsp
	sub rax, 20d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 6d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 4, rhsoff = 18, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 6d
	mov rdx, rbp
; --- START: outputArrayElement() for z --- 
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
; --- END: outputArrayElement() for z--- 
	jmp label_0
label_2:
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 2d
	mov rdx, rbp
; --- START: outputArrayElement() for x --- 
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
; --- END: outputArrayElement() for x--- 
label_0:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 4d
	mov rdx, rbp
; --- START: outputArrayElement() for y --- 
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
; --- END: outputArrayElement() for y--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 6d
	mov rdx, rbp
; --- START: outputArrayElement() for z --- 
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
; --- END: outputArrayElement() for z--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 7d
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
