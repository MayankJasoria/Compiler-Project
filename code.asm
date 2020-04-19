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
	sub rsp, 34d
	mov word [dynamic], 0
; --- START: takeInput(): type: Integer, Name: a --- 
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
; --- END: takeInput(): type: Integer, Name: a --- 
; --- START: takeInput(): type: Integer, Name: b --- 
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
; --- END: takeInput(): type: Integer, Name: b --- 
; --- START: takeInput(): type: Integer, Name: c --- 
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
; --- END: takeInput(): type: Integer, Name: c --- 
; --- START: takeInput(): type: Boolean, Name: x --- 
	push rbp
	mov rdi, op1
	mov rsi, type_bool
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
	mov r9, 7d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_bool
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
; --- END: takeInput(): type: Boolean, Name: x --- 
; --- START: takeInput(): type: Boolean, Name: y --- 
	push rbp
	mov rdi, op1
	mov rsi, type_bool
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
	mov rdi, fmt_bool
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
; --- END: takeInput(): type: Boolean, Name: y --- 
; --- START: takeInput(): type: Boolean, Name: z --- 
	push rbp
	mov rdi, op1
	mov rsi, type_bool
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
	mov r9, 9d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_bool
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
; --- END: takeInput(): type: Boolean, Name: z --- 
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
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 7d
	mov al, byte [rax]
	cmp al, 1d
	jnz label_3
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 2d
	mov rdx, rbp
; --- START: outputArrayElement() for a --- 
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
; --- END: outputArrayElement() for a--- 
jmp label_2
label_3:
	mov rax, rbp
	sub rax, 7d
	mov al, byte [rax]
	cmp al, 0d
	jnz label_4
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 4d
	mov rdx, rbp
; --- START: outputArrayElement() for b --- 
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
; --- END: outputArrayElement() for b--- 
jmp label_2
label_4:
label_2:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_0
label_1:
	mov rax, rbp
	sub rax, 2d
	mov ax, word [rax]
	cmp ax, 2d
	jnz label_5
	mov cx, 2d
label_6:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 4d
	mov word [rax], cx
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 1d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 3d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 0, rightOp: 1, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 3d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 5d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 1, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 29, rhsoff = 3, type = Boolean ---
	mov rax, rsp
	sub rax, 4d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 30d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 29, rhsoff = 3, type = Boolean ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 30d
	mov rdx, rbp
; --- START: outputArrayElement() for c --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_7
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_8
label_7:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_8:
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
; --- END: outputArrayElement() for c--- 
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 8d
	mov al, byte [rax]
	cmp al, 1d
	jnz label_10
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 8d
	mov rdx, rbp
; --- START: outputArrayElement() for y --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_11
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_12
label_11:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_12:
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
	mov r9, 4d
	mov rdx, rbp
; --- START: outputArrayElement() for b --- 
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
; --- END: outputArrayElement() for b--- 
jmp label_9
label_10:
	mov rax, rbp
	sub rax, 8d
	mov al, byte [rax]
	cmp al, 0d
	jnz label_13
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 8d
	mov rdx, rbp
; --- START: outputArrayElement() for y --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_14
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_15
label_14:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_15:
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
jmp label_9
label_13:
label_9:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 4d
	mov cx, word[rax]
	inc cx
	cmp cx, 8
	jnz label_6
	jmp label_0
label_5:
	mov rax, rbp
	sub rax, 2d
	mov ax, word [rax]
	cmp ax, 3d
	jnz label_16
label_17:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 4d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 6d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 7d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 8d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 9d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MINUS, type: Integer --- 
	mov ax, 0d
	mov rdx, rsp
	sub rdx, 11d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 7, rightOp: 9, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 9d
	mov r10, rsp
	sub r10, 11d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jg label_19
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_20
label_19:
	mov r8b, 1
label_20:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 12d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 7, rightOp: 9, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 12d
	mov dl, byte [rax]
	cmp dl, 0
	jz label_18
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 13d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
	mov ax, 2d
	mov rdx, rsp
	sub rdx, 15d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 12, rightOp: 13, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 14d
	mov r10, rsp
	sub r10, 15d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 17d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 12, rightOp: 13, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 29, rhsoff = 15, type = Boolean ---
	mov rax, rsp
	sub rax, 16d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 30d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 29, rhsoff = 15, type = Boolean ---
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 9d
	mov al, byte [rax]
	cmp al, 1d
	jnz label_22
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 9d
	mov rdx, rbp
; --- START: outputArrayElement() for z --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_23
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_24
label_23:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_24:
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
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 19d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 21d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 17, rightOp: 19, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 19d
	mov r10, rsp
	sub r10, 21d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 23d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 17, rightOp: 19, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 24d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
; --- START: applyOperator(): leftOp: 21, rightOp: 23, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 23d
	mov r10, rsp
	sub r10, 25d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 26d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 21, rightOp: 23, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 9, rhsoff = 24, type = Integer ---
	mov rax, rsp
	sub rax, 26d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 11d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 9, rhsoff = 24, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 11d
	mov rdx, rbp
; --- START: outputArrayElement() for p --- 
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
; --- END: outputArrayElement() for p--- 
jmp label_21
label_22:
	mov rax, rbp
	sub rax, 9d
	mov al, byte [rax]
	cmp al, 0d
	jnz label_25
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 9d
	mov rdx, rbp
; --- START: outputArrayElement() for z --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_26
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_27
label_26:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_27:
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
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 28d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 30d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 26, rightOp: 28, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 28d
	mov r10, rsp
	sub r10, 30d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 32d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 26, rightOp: 28, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 33d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
; --- START: applyOperator(): leftOp: 30, rightOp: 32, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 32d
	mov r10, rsp
	sub r10, 34d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 35d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 30, rightOp: 32, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 11, rhsoff = 33, type = Integer ---
	mov rax, rsp
	sub rax, 35d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 13d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 11, rhsoff = 33, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 13d
	mov rdx, rbp
; --- START: outputArrayElement() for q --- 
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
; --- END: outputArrayElement() for q--- 
jmp label_21
label_25:
label_21:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_17
label_18:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_0
label_16:
	mov rax, rbp
	sub rax, 21d
	mov qword [rax], rsp
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	cmp r10w, r11w
	jg rte
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_28:
	sub rsp, 4d
	add r9w, 4d
	dec rcx
	jnz label_28
	mov word [dynamic], r9w
	mov rax, rbp
	sub rax, 29d
	mov qword [rax], rsp
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 4d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 31d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	cmp r10w, r11w
	jg rte
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_29:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_29
	mov word [dynamic], r9w
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_float
	movsx rcx, r10w
	movsx r8, r11w
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

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 21d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_30:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_float
	sub rdx, 4d
	mov rsi, rdx
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
	pop rcx
	pop rdx
	sub rdx, 4d
	dec rcx
	cmp rcx, 0x0
	jnz label_30
; --- END: takeInput(): type: Array, Name: A --- 
; --- START: takeInput(): type: Array, Name: B --- 
	push rbp
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 4d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 31d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_int
	movsx rcx, r10w
	movsx r8, r11w
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

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 29d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 4d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 31d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_31:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
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
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	cmp rcx, 0x0
	jnz label_31
; --- END: takeInput(): type: Array, Name: B --- 
; --- START: takeInput(): type: Boolean, Name: c --- 
	push rbp
	mov rdi, op1
	mov rsi, type_bool
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
	mov r9, 30d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_bool
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
; --- END: takeInput(): type: Boolean, Name: c --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
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
	mov rax, rbp
	sub rax, 21d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 4d
label_32:
	push rdx
	push rcx
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_float
	mov rax, rdx
	sub rax, r9
	cvtss2sd xmm0, dword[rax]
	mov rax, 1
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
; --- END: outputArrayElement() for A--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
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
	pop rcx
	pop rdx
	sub rdx, 4d
	dec rcx
	jnz label_32
	push rbp
	mov rdi, end_line
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
; --- END: giveInput() --- 
	mov cx, 1d
label_33:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 32d
	mov word [rax], cx
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 32d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 4d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 6d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 32, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 34d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 32, rhsoff = 4, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is not NULL --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 34d
	mov r8w, word [rax]
	mov rsi, 75d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 21d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 4d
label_34:
	add r9w, r8w
	dec rcx
	jnz label_34
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_float
	mov rax, rdx
	sub rax, r9
	cvtss2sd xmm0, dword[rax]
	mov rax, 1
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
; --- END: outputArrayElement() for A--- 
; --- END: giveInput() --- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 32d
	mov cx, word[rax]
	inc cx
	cmp cx, 5
	jnz label_33
label_0:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 34d
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
