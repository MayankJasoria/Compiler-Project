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

; ### Begin of a moduledef. ### 
compute_expr:
mov word [dynamic], 0
; --- START: takeInput(): type: Integer, Name: d --- 
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
	mov r9, 14d
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
; --- END: takeInput(): type: Integer, Name: d --- 
; --- START: takeInput(): type: Integer, Name: q --- 
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
	mov r9, 12d
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
; --- END: takeInput(): type: Integer, Name: q --- 
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
	sub rax, 14d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 8d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 2d
	mov rdx, rsp
	sub rdx, 10d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 6, rightOp: 8, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 8d
	mov r10, rsp
	sub r10, 10d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 12d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 6, rightOp: 8, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 4, rightOp: 10, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 12d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 14d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 10, operator: PLUS, type: Integer --- 
	mov ax, 3d
	mov rdx, rsp
	sub rdx, 16d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 12, rightOp: 14, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 14d
	mov r10, rsp
	sub r10, 16d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 18d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 12, rightOp: 14, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 8, rhsoff = 16, type = Integer ---
	mov rax, rsp
	sub rax, 18d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 10d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 8, rhsoff = 16, type = Integer ---
	mov rax, rbp
	sub rax, 5d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 1d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 3d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 5d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 1, rightOp: 3, operator: LE, type: Integer --- 
	mov rax, rsp
	sub rax, 3d
	mov r10, rsp
	sub r10, 5d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jle label_0
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_1
label_0:
	mov r8b, 1
label_1:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 6d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 1, rightOp: 3, operator: LE, type: Integer --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 5, operator: AND, type: Boolean --- 
	mov rax, rsp
	sub rax, 1d
	mov r10, rsp
	sub r10, 6d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	and r8b, r9b
	mov rax, rsp
	sub rax, 7d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 5, operator: AND, type: Boolean --- 
; --- START: moveOffsetToOffset(): lhsoff = 14, rhsoff = 6, type = Boolean ---
	mov rax, rsp
	sub rax, 7d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 15d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 14, rhsoff = 6, type = Boolean ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 12d
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
; --- START: moveOffsetToOffset(): lhsoff = 5, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 7d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 5, rhsoff = 4, type = Integer ---
	mov rax, rbp
	sub rax, 15d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 1d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 3d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 12d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 5d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 1, rightOp: 3, operator: LE, type: Integer --- 
	mov rax, rsp
	sub rax, 3d
	mov r10, rsp
	sub r10, 5d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jle label_2
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_3
label_2:
	mov r8b, 1
label_3:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 6d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 1, rightOp: 3, operator: LE, type: Integer --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 5, operator: OR, type: Boolean --- 
	mov rax, rsp
	sub rax, 1d
	mov r10, rsp
	sub r10, 6d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	or r8b, r9b
	mov rax, rsp
	sub rax, 7d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 5, operator: OR, type: Boolean --- 
; --- START: moveOffsetToOffset(): lhsoff = 7, rhsoff = 6, type = Boolean ---
	mov rax, rsp
	sub rax, 7d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 8d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 7, rhsoff = 6, type = Boolean ---
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 5d
	mov rdx, rbp
; --- START: outputArrayElement() for c --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_4
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_5
label_4:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_5:
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 14d
	mov rdx, rbp
; --- START: outputArrayElement() for d --- 
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
; --- END: outputArrayElement() for d--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 10d
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 12d
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 7d
	mov rdx, rbp
; --- START: outputArrayElement() for u --- 
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
; --- END: outputArrayElement() for u--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 8d
	mov rdx, rbp
; --- START: outputArrayElement() for v --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_6
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_7
label_6:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_7:
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
; --- END: outputArrayElement() for v--- 

; ### Copying back the output parameters. ### 
	mov rax, qword [rbp]
	mov rdx, rbp
	sub rdx, 7d
	sub rax, 7d
	mov cx, word [rdx]
	mov word [rax], cx
	sub rax, 7d
	mov rdx, rbp
	sub rdx, 8d
	sub rax, 8d
	mov cl, byte [rdx]
	mov byte [rax], cl
	sub rax, 8d
	movsx rax, word [dynamic]
	add rsp, rax
	ret
	sub rbp, 8
	mov rsp, rbp
	mov rbp, rax

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 8d
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
; --- START: takeInput(): type: Integer, Name: y --- 
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
; --- END: takeInput(): type: Integer, Name: y --- 
	mov al, 0
	mov rdx, rsp
	sub rdx, 1d
	mov byte [rdx], al
; --- START: moveOffsetToOffset(): lhsoff = 7, rhsoff = 0, type = Boolean ---
	mov rax, rsp
	sub rax, 1d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 8d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 7, rhsoff = 0, type = Boolean ---
; --- Setting up the stack frame ---
	push rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 2d
	sub rsp, 2d
	mov ax, word [rcx]
	mov word [rsp], ax
	mov rcx, qword [rbp]
	sub rcx, 4d
	sub rsp, 2d
	mov ax, word [rcx]
	mov word [rsp], ax
	mov rcx, qword [rbp]
	sub rcx, 8d
	sub rsp, 1d
	mov al, byte [rcx]
	mov byte [rsp], al
	sub rsp, 10d
	call compute_expr
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 7d
	mov rdx, rbp
; --- START: outputArrayElement() for k --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_8
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_9
label_8:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_9:
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
; --- END: outputArrayElement() for k--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 8d
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
