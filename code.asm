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

; ### Begin of a moduledef. ### 
var_demo_array:
mov word [dynamic], 0
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
	mov r9, 37d
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
	mov rax, rbp
	sub rax, 47d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 12d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 14d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array m: base: rdx, offset: r9  --- 
	mov r8w, 5d
	mov rsi, 12d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 10d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_0:
	add r9w, r8w
	dec rcx
	jnz label_0
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array m: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 3d
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], ax
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
; --- START: moveOffsetToOffset(): lhsoff = 33, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 35d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 33, rhsoff = 4, type = Integer ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 39, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 47d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 39, rhsoff = 0, type = Array ---
	mov al, 1d
	mov rdx, rsp
	sub rdx, 1d
	mov byte [rdx], al
; --- START: moveOffsetToOffset(): lhsoff = 32, rhsoff = 0, type = Boolean ---
	mov rax, rsp
	sub rax, 1d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 33d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 32, rhsoff = 0, type = Boolean ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
	mov rax, rbp
	sub rax, 47d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 16d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: applyOperator(): leftOp: 0, rightOp: 8, operator: PLUS, type: Array --- 
	mov rax, rsp
	sub rax, 8d
	mov r10, rsp
	sub r10, 16d
	mov rax, rsp
	sub rax, 18d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 8, operator: PLUS, type: Array --- 
; --- START: moveOffsetToOffset(): lhsoff = 39, rhsoff = 16, type = Array ---
	mov rax, rsp
	sub rax, 24d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 47d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 39, rhsoff = 16, type = Array ---
	mov rax, rbp
	sub rax, 35d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 37d
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
	mov ax, 20d
	mov rdx, rsp
	sub rdx, 8d
	mov word [rdx], ax
	mov rax, rbp
	sub rax, 39d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 10d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
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
; --- START: applyOperator(): leftOp: 4, rightOp: 10, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 12d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 14d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 10, operator: MINUS, type: Integer --- 
; --- START: get left and right index of p ---
	mov r10w, 2d
	mov r11w, 20d
; --- END: got left and right index of p in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array p: base: rdx, offset: r9  --- 
	mov r8w, 10d
	mov rsi, 16d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 47d
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
; --- END: fetchArraybyIndex() for array p: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 12, type = Integer ---
	mov rax, rsp
	sub rax, 14d
	mov r8w, word [rax]
	mov rax, rdx
	sub rax, r9
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 12, type = Integer ---
label_2:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 33d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 1d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
	mov rax, rbp
	sub rax, 35d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 3d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 12d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 14d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array m: base: rdx, offset: r9  --- 
	mov r8w, 11d
	mov rsi, 17d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 10d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_4:
	add r9w, r8w
	dec rcx
	jnz label_4
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array m: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
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
	jle label_5
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_6
label_5:
	mov r8b, 1
label_6:
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
	mov al, 0
	mov rdx, rsp
	sub rdx, 8d
	mov byte [rdx], al
; --- START: applyOperator(): leftOp: 6, rightOp: 7, operator: OR, type: Boolean --- 
	mov rax, rsp
	sub rax, 7d
	mov r10, rsp
	sub r10, 8d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	or r8b, r9b
	mov rax, rsp
	sub rax, 9d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 6, rightOp: 7, operator: OR, type: Boolean --- 
	mov rax, rsp
	sub rax, 9d
	mov dl, byte [rax]
	cmp dl, 0
	jz label_3
	mov rax, rbp
	sub rax, 97d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 17d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 89, rhsoff = 9, type = Array ---
	mov rax, rsp
	sub rax, 17d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 97d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 89, rhsoff = 9, type = Array ---
	mov rax, rbp
	sub rax, 89d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 19d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 12d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 14d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array m: base: rdx, offset: r9  --- 
	mov r8w, 25d
	mov rsi, 22d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 10d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_7:
	add r9w, r8w
	dec rcx
	jnz label_7
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array m: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
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
; --- START: get left and right index of b ---
	mov r10w, 2d
	mov r11w, 20d
; --- END: got left and right index of b in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array b: base: rdx, offset: r9  --- 
	mov r8w, 2d
	mov rsi, 22d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 97d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_8:
	add r9w, r8w
	dec rcx
	jnz label_8
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array b: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 21, type = Integer ---
	mov rax, rsp
	sub rax, 23d
	mov r8w, word [rax]
	mov rax, rdx
	sub rax, r9
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 21, type = Integer ---
; --- START: get left and right index of b ---
	mov r10w, 2d
	mov r11w, 20d
; --- END: got left and right index of b in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array b: base: rdx, offset: r9  --- 
	mov r8w, 18d
	mov rsi, 23d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 97d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_9:
	add r9w, r8w
	dec rcx
	jnz label_9
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array b: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 25d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rdx, rsp
	sub rdx, 29d
	mov dword [rdx], __float32__(1856.000000)
; --- START: applyOperator(): leftOp: 23, rightOp: 25, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 25d
	mov r10, rsp
	sub r10, 27d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 31d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 23, rightOp: 25, operator: MUL, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 33, rhsoff = 29, type = Integer ---
	mov rax, rsp
	sub rax, 31d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 35d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 33, rhsoff = 29, type = Integer ---
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_2
label_3:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 35d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 47d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 10d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
	mov rax, rbp
	sub rax, 37d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 12d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 2, rightOp: 10, operator: MUL, type: Array --- 
	mov rax, rsp
	sub rax, 10d
	mov r10, rsp
	sub r10, 18d
	mov rax, rsp
	sub rax, 14d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 2, rightOp: 10, operator: MUL, type: Array --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 12, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 14d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 16d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 12, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 30, rhsoff = 14, type = Integer ---
	mov rax, rsp
	sub rax, 16d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 32d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 30, rhsoff = 14, type = Integer ---
	mov rax, rbp
	sub rax, 37d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 3d
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], ax
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
; --- START: moveOffsetToOffset(): lhsoff = 35, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 37d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 35, rhsoff = 4, type = Integer ---
	mov rax, rbp
	sub rax, 35d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 37d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 4d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jg label_10
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_11
label_10:
	mov r8b, 1
label_11:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 5d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: GT, type: Integer --- 
	mov rax, rbp
	sub rax, 37d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 7d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 100d
	mov rdx, rsp
	sub rdx, 9d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 5, rightOp: 7, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 7d
	mov r10, rsp
	sub r10, 9d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jg label_12
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_13
label_12:
	mov r8b, 1
label_13:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 10d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 5, rightOp: 7, operator: GT, type: Integer --- 
; --- START: applyOperator(): leftOp: 4, rightOp: 9, operator: OR, type: Boolean --- 
	mov rax, rsp
	sub rax, 5d
	mov r10, rsp
	sub r10, 10d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	or r8b, r9b
	mov rax, rsp
	sub rax, 11d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 4, rightOp: 9, operator: OR, type: Boolean --- 
; --- START: moveOffsetToOffset(): lhsoff = 32, rhsoff = 10, type = Boolean ---
	mov rax, rsp
	sub rax, 11d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 33d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 32, rhsoff = 10, type = Boolean ---
	mov rax, rbp
	sub rax, 143d
	mov qword [rax], rsp
; --- START: get left and right index of z2 ---
	mov rax, rbp
	sub rax, 35d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 37d
	mov r11w, word[rax]
; --- END: got left and right index of z2 in r10w and r11w --- 
	cmp r10w, r11w
	jg rte
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_14:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_14
	mov word [dynamic], r9w
	mov rax, rbp
	sub rax, 151d
	mov qword [rax], rsp
; --- START: get left and right index of z3 ---
	mov rax, rbp
	sub rax, 35d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 37d
	mov r11w, word[rax]
; --- END: got left and right index of z3 in r10w and r11w --- 
	cmp r10w, r11w
	jg rte
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_15:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_15
	mov word [dynamic], r9w
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 33d
	mov rdx, rbp
; --- START: outputArrayElement() for k --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rax, rdx
	sub rax, r9
	mov al, byte[rax]
	cmp al, 0
	jz label_16
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_17
label_16:
	mov rdi, output_fmt_string
	mov rsi, bool_false
label_17:
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
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begin of a moduledef. ### 
f1:
mov word [dynamic], 0
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
	mov r9, 39d
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
	mov r9, 35d
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
	mov rax, rbp
	sub rax, 53d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 75d
	mov rcx, rax
	mov qword[rcx], rax
; --- START: takeInput(): type: Array, Name: B --- 
	push rbp
; --- START: get left and right index of B ---
	mov r10w, 4d
	mov r11w, 10d
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
	sub rax, 75d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of B ---
	mov r10w, 4d
	mov r11w, 10d
; --- END: got left and right index of B in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_18:
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
	jnz label_18
; --- END: takeInput(): type: Array, Name: B --- 
	mov rax, rbp
	sub rax, 97d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 147d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 75d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 45, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 53d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 45, rhsoff = 0, type = Array ---
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 139, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 147d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 139, rhsoff = 0, type = Array ---
	mov rax, rbp
	sub rax, 147d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 89, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 97d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 89, rhsoff = 0, type = Array ---
	mov cx, 15d
label_19:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 45d
	mov word [rax], cx
	mov rax, rbp
	sub rax, 35d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 4d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 45d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 6d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 39d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 10d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 8d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 12d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 6, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 10, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 14d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 14d
	fstp dword [rax]
	mov rax, rsp
	sub rax, 14d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 10, operator: PLUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 31, rhsoff = 12, type = Real ---
	mov rax, rsp
	sub rax, 16d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 35d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 31, rhsoff = 12, type = Real ---
	mov rax, rbp
	sub rax, 39d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 18d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 28d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 22d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rdx, rsp
	sub rdx, 26d
	mov dword [rdx], __float32__(34.200001)
; --- START: applyOperator(): leftOp: 18, rightOp: 22, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 22d
	mov r10, rsp
	sub r10, 26d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 30d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 18, rightOp: 22, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 14, rightOp: 26, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 18d
	mov r10, rsp
	sub r10, 30d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 34d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 14, rightOp: 26, operator: PLUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 189, rhsoff = 30, type = Real ---
	mov rax, rsp
	sub rax, 34d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 193d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 189, rhsoff = 30, type = Real ---
	mov rax, rbp
	sub rax, 193d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 38d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 28d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 42d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 43d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 46d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 38, rightOp: 42, operator: MUL, type: Real --- 
	mov rax, rsp
	sub rax, 42d
	mov r10, rsp
	sub r10, 46d
	finit
	fld dword [rax]
	fld dword [r10]
	fmul
	mov rax, rsp
	sub rax, 50d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 38, rightOp: 42, operator: MUL, type: Real --- 
; --- START: applyOperator(): leftOp: 34, rightOp: 46, operator: MINUS, type: Real --- 
	mov rax, rsp
	sub rax, 38d
	mov r10, rsp
	sub r10, 50d
	finit
	fld dword [rax]
	fld dword [r10]
	fsub
	mov rax, rsp
	sub rax, 54d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 34, rightOp: 46, operator: MINUS, type: Real --- 
	mov rdx, rsp
	sub rdx, 58d
	mov dword [rdx], __float32__(2050.000000)
; --- START: applyOperator(): leftOp: 50, rightOp: 54, operator: MINUS, type: Real --- 
	mov rax, rsp
	sub rax, 54d
	mov r10, rsp
	sub r10, 58d
	finit
	fld dword [rax]
	fld dword [r10]
	fsub
	mov rax, rsp
	sub rax, 62d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 50, rightOp: 54, operator: MINUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 193, rhsoff = 58, type = Real ---
	mov rax, rsp
	sub rax, 62d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 197d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 193, rhsoff = 58, type = Real ---
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 45d
	mov ax, word [rax]
	cmp ax, 10d
	jnz label_21
	mov rax, rbp
	sub rax, 211d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 261d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 45d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 64d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 20d
	mov rdx, rsp
	sub rdx, 66d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 62, rightOp: 64, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 64d
	mov r10, rsp
	sub r10, 66d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 68d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 62, rightOp: 64, operator: MUL, type: Integer --- 
; --- START: get left and right index of B ---
	mov r10w, 10d
	mov r11w, 30d
; --- END: got left and right index of B in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array B: base: rdx, offset: r9  --- 
	mov r8w, 9d
	mov rsi, 60d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 211d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_22:
	add r9w, r8w
	dec rcx
	jnz label_22
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array B: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 66, type = Integer ---
	mov rax, rsp
	sub rax, 68d
	mov r8w, word [rax]
	mov rax, rdx
	sub rax, r9
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 66, type = Integer ---
	mov rax, rbp
	sub rax, 147d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 76d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
; --- START: moveOffsetToOffset(): lhsoff = 203, rhsoff = 68, type = Array ---
	mov rax, rsp
	sub rax, 76d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 211d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 203, rhsoff = 68, type = Array ---
	mov rax, rbp
	sub rax, 203d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 78d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: moveOffsetToOffset(): lhsoff = 253, rhsoff = 76, type = Array ---
	mov rax, rsp
	sub rax, 84d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 261d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 253, rhsoff = 76, type = Array ---
	jmp label_20
label_21:
	mov rax, rbp
	sub rax, 45d
	mov ax, word [rax]
	cmp ax, 20d
	jnz label_23
	mov rdx, rsp
	sub rdx, 82d
	mov dword [rdx]