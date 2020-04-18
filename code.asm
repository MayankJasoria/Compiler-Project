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
arraySum:
mov word [dynamic], 0
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], __float32__(0.000000)
; --- START: moveOffsetToOffset(): lhsoff = 14, rhsoff = 0, type = Real ---
	mov rax, rsp
	sub rax, 4d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 18d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 14, rhsoff = 0, type = Real ---
	mov cx, 1d
label_0:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 20d
	mov word [rax], cx
	mov rax, rbp
	sub rax, 20d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 14d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 4d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: LE, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jle label_1
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_2
label_1:
	mov r8b, 1
label_2:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 5d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: LE, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 20, rhsoff = 4, type = Boolean ---
	mov rax, rsp
	sub rax, 5d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 21d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 20, rhsoff = 4, type = Boolean ---
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 21d
	mov aL, byte [rax]
	cmp al, 1d
	jnz label_4
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- idNode->next is not NULL --- 
; --- START: fetchArraybyIndex() for array list: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 20d
	mov r8w, word [rax]
	mov rsi, 17d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 8d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 4d
label_5:
	add r9w, r8w
	dec rcx
	jnz label_5
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array list: base: rdx, offset: r9 --- 
; --- START: outputArrayElement() for list --- 
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
; --- END: outputArrayElement() for list--- 
; --- END: giveInput() --- 
	mov ax, 25d
	mov rdx, rsp
	sub rdx, 7d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 25, rhsoff = 5, type = Integer ---
	mov rax, rsp
	sub rax, 7d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 27d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 25, rhsoff = 5, type = Integer ---
	mov rax, rbp
	sub rax, 18d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 11d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array list: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 20d
	mov r8w, word [rax]
	mov rsi, 20d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 8d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 4d
label_6:
	add r9w, r8w
	dec rcx
	jnz label_6
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array list: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 15d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: applyOperator(): leftOp: 7, rightOp: 11, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 11d
	mov r10, rsp
	sub r10, 15d
	finit
	fld dword [r10]
	fld dword [rax]
	fadd
	sub rsp, 4
	fstp dword [rsp]
; --- START: applyOperator(): leftOp: 7, rightOp: 11, operator: PLUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 14, rhsoff = 15, type = Real ---
	mov rax, rsp
	sub rax, 19d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 18d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 14, rhsoff = 15, type = Real ---
jmp label_3
label_6:
	mov rax, rbp
	sub rax, 21d
	mov aL, byte [rax]
	cmp al, 0d
	jnz label_7
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 18d
	mov rdx, rbp
; --- START: outputArrayElement() for sum --- 
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
; --- END: outputArrayElement() for sum--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 20d
	mov rdx, rbp
; --- START: outputArrayElement() for index --- 
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
; --- END: outputArrayElement() for index--- 
jmp label_3
label_7:
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 27d
	mov rdx, rbp
; --- START: outputArrayElement() for p1 --- 
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
; --- END: outputArrayElement() for p1--- 
label_3:
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
	sub rax, 20d
	mov cx, word[rax]
	inc cx
	cmp cx, 16
	jnz label_0
; --- START: giveInput() type: AST_NODE_VARID