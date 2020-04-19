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
	sub rsp, 27d
	mov word [dynamic], 0
	mov rdx, rsp
	sub rdx, 4d
	mov dword [rdx], __float32__(5.000000)
; --- START: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Real ---
	mov rax, rsp
	sub rax, 4d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 16d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Real ---
	mov rdx, rsp
	sub rdx, 4d
	mov dword [rdx], __float32__(9.000000)
; --- START: moveOffsetToOffset(): lhsoff = 16, rhsoff = 0, type = Real ---
	mov rax, rsp
	sub rax, 4d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 20d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 16, rhsoff = 0, type = Real ---
	mov rax, rbp
	sub rax, 16d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 4d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 8d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: LT, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 8d
	finit
	fld dword [r10]
	fld dword [rax]
	fcom st0, st1
	fstsw ax
	and eax, 0100011100000000B
	cmp eax, 0000000100000000B
	je label_0
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_1
label_0:
	mov r8b, 1
label_1:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 9d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: LT, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 24, rhsoff = 8, type = Boolean ---
	mov rax, rsp
	sub rax, 9d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 25d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 24, rhsoff = 8, type = Boolean ---
	mov rax, rbp
	sub rax, 16d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 4d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 8d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: GT, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 8d
	finit
	fld dword [r10]
	fld dword [rax]
	fcom st0, st1
	fstsw ax
	and eax, 0100011100000000B
	cmp eax, 0000000000000000B
	je label_2
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_3
label_2:
	mov r8b, 1
label_3:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 9d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: GT, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 25, rhsoff = 8, type = Boolean ---
	mov rax, rsp
	sub rax, 9d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 26d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 25, rhsoff = 8, type = Boolean ---
	mov rax, rbp
	sub rax, 16d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 4d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 8d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: NE, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 8d
	finit
	fld dword [r10]
	fld dword [rax]
	fcom st0, st1
	fstsw ax
	and eax, 0100011100000000B
	cmp eax, 0100000000000000B
	jne label_4
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_5
label_4:
	mov r8b, 1
label_5:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 9d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: NE, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 26, rhsoff = 8, type = Boolean ---
	mov rax, rsp
	sub rax, 9d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 27d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 26, rhsoff = 8, type = Boolean ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 25d
	mov rdx, rbp
; --- START: outputArrayElement() for t --- 
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
; --- END: outputArrayElement() for t--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 26d
	mov rdx, rbp
; --- START: outputArrayElement() for t1 --- 
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
; --- END: outputArrayElement() for t1--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 27d
	mov rdx, rbp
; --- START: outputArrayElement() for t2 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_10
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_11
label_10:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_11:
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
; --- END: outputArrayElement() for t2--- 
; --- START: takeInput(): type: Real, Name: x --- 
	push rbp
	mov rdi, op1
	mov rsi, type_float
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
	mov rdi, fmt_float
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
; --- END: takeInput(): type: Real, Name: x --- 
; --- START: takeInput(): type: Real, Name: y --- 
	push rbp
	mov rdi, op1
	mov rsi, type_float
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
	mov rdi, fmt_float
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
; --- END: takeInput(): type: Real, Name: y --- 
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 4d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 8d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 12d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 4, rightOp: 8, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 8d
	mov r10, rsp
	sub r10, 12d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 16d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 4, rightOp: 8, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 12, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 16d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 20d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 0, rightOp: 12, operator: PLUS, type: Real --- 
	mov rax, rbp
	sub rax, 16d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 24d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 28d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 20, rightOp: 24, operator: MINUS, type: Real --- 
	mov rax, rsp
	sub rax, 24d
	mov r10, rsp
	sub r10, 28d
	finit
	fld dword [rax]
	fld dword [r10]
	fsub
	mov rax, rsp
	sub rax, 32d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 20, rightOp: 24, operator: MINUS, type: Real --- 
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 36d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 28, rightOp: 32, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 32d
	mov r10, rsp
	sub r10, 36d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 40d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 28, rightOp: 32, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 16, rightOp: 36, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 20d
	mov r10, rsp
	sub r10, 40d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 44d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 16, rightOp: 36, operator: PLUS, type: Real --- 
	mov rax, rbp
	sub rax, 16d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 48d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rdx, rsp
	sub rdx, 52d
	mov dword [rdx], __float32__(2.000000)
; --- START: applyOperator(): leftOp: 44, rightOp: 48, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 48d
	mov r10, rsp
	sub r10, 52d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 56d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 44, rightOp: 48, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 40, rightOp: 52, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 44d
	mov r10, rsp
	sub r10, 56d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 60d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 40, rightOp: 52, operator: PLUS, type: Real --- 
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 64d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 68d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 60, rightOp: 64, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 64d
	mov r10, rsp
	sub r10, 68d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 72d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 60, rightOp: 64, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 56, rightOp: 68, operator: MINUS, type: Real --- 
	mov rax, rsp
	sub rax, 60d
	mov r10, rsp
	sub r10, 72d
	finit
	fld dword [rax]
	fld dword [r10]
	fsub
	mov rax, rsp
	sub rax, 76d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 56, rightOp: 68, operator: MINUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 8, rhsoff = 72, type = Real ---
	mov rax, rsp
	sub rax, 76d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 12d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 8, rhsoff = 72, type = Real ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 12d
	mov rdx, rbp
; --- START: outputArrayElement() for z --- 
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
; --- END: outputArrayElement() for z--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 27d
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
