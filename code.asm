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
	rte_divisionby0: db "RUN TIME ERROR: division by zero on line %hd.", 0xA, 0
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
array_parameter_demo:
mov word [dynamic], 0
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r10w, 10d
	mov r11w, 14d
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 8d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_0:
	push rdx
	push rcx
; --- START: outputArrayElement() for B --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for B--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_0
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov rax, rbp
	sub rax, 22d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 24d
	mov r11w, word [rax]
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 20d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_1:
	push rdx
	push rcx
; --- START: outputArrayElement() for C --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for C--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_1
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
; --- START: takeInput(): type: Integer, Name: p --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov r9, 36d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: p --- 
; --- START: takeInput(): type: Integer, Name: q --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov r9, 38d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: q --- 
	mov rax, rbp
	sub rax, 46d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 64d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 82d
	mov qword [rax], rsp
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
	mov rsi, 19d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_2:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_2
	mov word [dynamic], r9w
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
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
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 46d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of A in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_3:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	cmp rcx, 0x0
	jnz label_3
; --- END: takeInput(): type: Array, Name: A --- 
; --- START: takeInput(): type: Array, Name: E --- 
	push rbp
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_int
	movsx rcx, r10w
	movsx r8, r11w
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 82d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_4:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	cmp rcx, 0x0
	jnz label_4
; --- END: takeInput(): type: Array, Name: E --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 46d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_5:
	push rdx
	push rcx
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for A--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_5
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
	mov ax, 0d
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
	mov cx, 10d
label_6:
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
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is not NULL --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 32d
	mov r8w, word [rax]
	mov rsi, 30d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 46d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for A--- 
; --- END: giveInput() --- 
	mov rax, rbp
	sub rax, 26d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of A in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 32d
	mov r8w, word [rax]
	mov rsi, 31d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 46d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
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
; --- START: moveOffsetToOffset(): lhsoff = 24, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 26d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 24, rhsoff = 4, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 26d
	mov rdx, rbp
; --- START: outputArrayElement() for sum1 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum1--- 
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
	cmp cx, 15
	jnz label_6
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 46d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_9:
	push rdx
	push rcx
; --- START: outputArrayElement() for A --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for A--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_9
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 26d
	mov rdx, rbp
; --- START: outputArrayElement() for sum1 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum1--- 
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array E: base: rdx, offset: r9  --- 
	mov r8w, 6d
	mov rsi, 38d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 82d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_10:
	add r9w, r8w
	dec rcx
	jnz label_10
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array E: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 8d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array E: base: rdx, offset: r9  --- 
	mov r8w, 7d
	mov rsi, 38d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 82d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_11:
	add r9w, r8w
	dec rcx
	jnz label_11
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array E: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 10d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 6, rightOp: 8, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 8d
	mov r10, rsp
	sub r10, 10d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 12d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 6, rightOp: 8, operator: PLUS, type: Integer --- 
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array E: base: rdx, offset: r9  --- 
	mov r8w, 5d
	mov rsi, 38d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 82d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_12:
	add r9w, r8w
	dec rcx
	jnz label_12
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array E: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 10, type = Integer ---
	mov rax, rsp
	sub rax, 12d
	mov r8w, word [rax]
	mov rax, rdx
	sub rax, r9
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 10, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of E ---
	mov rax, rbp
	sub rax, 36d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 38d
	mov r11w, word[rax]
; --- END: got left and right index of E in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 82d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_13:
	push rdx
	push rcx
; --- START: outputArrayElement() for E --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for E--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_13
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
	mov ax, 0d
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
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
	mov rsi, 43d
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
	mov r8w, r10w
	mov r10w, 10d
	mov r11w, 14d
	cmp r8w, r10w
	jnz typeError
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
	mov r8w, r11w
	mov r10w, 10d
	mov r11w, 14d
	cmp r8w, r11w
	jnz typeError
; --- START: moveOffsetToOffset(): lhsoff = 56, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 64d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 56, rhsoff = 0, type = Array ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 64d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_14:
	push rdx
	push rcx
; --- START: outputArrayElement() for D --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for D--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_14
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
	mov cx, 10d
label_15:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 34d
	mov word [rax], cx
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
; --- idNode->next is not NULL --- 
; --- START: fetchArraybyIndex() for array D: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 34d
	mov r8w, word [rax]
	mov rsi, 47d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 64d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_16:
	add r9w, r8w
	dec rcx
	jnz label_16
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array D: base: rdx, offset: r9 --- 
; --- START: outputArrayElement() for D --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for D--- 
; --- END: giveInput() --- 
	mov rax, rbp
	sub rax, 28d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array D: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 34d
	mov r8w, word [rax]
	mov rsi, 48d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 64d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_17:
	add r9w, r8w
	dec rcx
	jnz label_17
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array D: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
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
; --- START: moveOffsetToOffset(): lhsoff = 26, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 28d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 26, rhsoff = 4, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 28d
	mov rdx, rbp
; --- START: outputArrayElement() for sum2 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum2--- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 34d
	mov cx, word[rax]
	inc cx
	cmp cx, 15
	jnz label_15
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of D ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of D in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 64d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_18:
	push rdx
	push rcx
; --- START: outputArrayElement() for D --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for D--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_18
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 28d
	mov rdx, rbp
; --- START: outputArrayElement() for sum2 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum2--- 
	mov ax, 0d
	mov rdx, rsp
	sub rdx, 8d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 28, rhsoff = 6, type = Integer ---
	mov rax, rsp
	sub rax, 8d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 30d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 28, rhsoff = 6, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov rax, rbp
	sub rax, 22d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 24d
	mov r11w, word [rax]
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov rax, rbp
	sub rax, 20d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_19:
	push rdx
	push rcx
; --- START: outputArrayElement() for C --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for C--- 
	pop rcx
	pop rdx
	push rdx
	push rcx
	push rbp
	mov rdi, single_space
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	jnz label_19
	push rbp
	mov rdi, end_line
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: giveInput() --- 
	mov cx, 1d
label_20:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 86d
	mov word [rax], cx
; --- START: takeInput(): type: Integer, Name: index --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov r9, 88d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: index --- 
	mov rax, rbp
	sub rax, 30d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 22d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 24d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array C: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 88d
	mov r8w, word [rax]
	mov rsi, 61d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 20d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 2d
label_21:
	add r9w, r8w
	dec rcx
	jnz label_21
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array C: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
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
; --- START: moveOffsetToOffset(): lhsoff = 28, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 30d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 28, rhsoff = 4, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 30d
	mov rdx, rbp
; --- START: outputArrayElement() for sum3 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum3--- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 86d
	mov cx, word[rax]
	inc cx
	cmp cx, 5
	jnz label_20
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 30d
	mov rdx, rbp
; --- START: outputArrayElement() for sum3 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for sum3--- 
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 36d
	mov word [dynamic], 0
; --- START: takeInput(): type: Integer, Name: m --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov r9, 2d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: m --- 
; --- START: takeInput(): type: Integer, Name: n --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	mov r9, 4d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: n --- 
	mov rax, rbp
	sub rax, 18d
	mov rcx, rax
	mov qword[rcx], rax
	mov rax, rbp
	sub rax, 36d
	mov qword [rax], rsp
; --- START: get left and right index of array_B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of array_B in r10w and r11w --- 
	mov rsi, 74d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_22:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_22
	mov word [dynamic], r9w
; --- START: takeInput(): type: Array, Name: array_A --- 
	push rbp
; --- START: get left and right index of array_A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of array_A in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_int
	movsx rcx, r10w
	movsx r8, r11w
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 18d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of array_A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of array_A in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_23:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	cmp rcx, 0x0
	jnz label_23
; --- END: takeInput(): type: Array, Name: array_A --- 
; --- START: takeInput(): type: Array, Name: array_B --- 
	push rbp
; --- START: get left and right index of array_B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of array_B in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_int
	movsx rcx, r10w
	movsx r8, r11w
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp

; --- rdx will be the address of the first element of the array ---
	mov rax, rbp
	sub rax, 36d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of array_B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of array_B in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_24:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_int
	sub rdx, 2d
	mov rsi, rdx
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	pop rcx
	pop rdx
	sub rdx, 2d
	dec rcx
	cmp rcx, 0x0
	jnz label_24
; --- END: takeInput(): type: Array, Name: array_B --- 
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 18d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of array_A ---
	mov r10w, 10d
	mov r11w, 14d
; --- END: got left and right index of array_A in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 77d
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
	sub rcx, 36d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of array_B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of array_B in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 77d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	sub rsp, 64d
	call array_parameter_demo
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
	mov rdx, rbp
	sub rdx, 6d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 26d
	mov cx, word [rax]
	mov word [rdx], cx
	mov rdx, rbp
	sub rdx, 8d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 28d
	mov cx, word [rax]
	mov word [rdx], cx
	mov rdx, rbp
	sub rdx, 10d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 30d
	mov cx, word [rax]
	mov word [rdx], cx
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 6d
	mov rdx, rbp
; --- START: outputArrayElement() for s1 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for s1--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 8d
	mov rdx, rbp
; --- START: outputArrayElement() for s2 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for s2--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 10d
	mov rdx, rbp
; --- START: outputArrayElement() for s3 --- 
; Function is used for both Arrays and non-Array types, don't go by the name! 
	push rbp
	mov rdi, output_fmt_int
	mov rax, rdx
	sub rax, r9
	mov si, word[rax]
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
; --- END: outputArrayElement() for s3--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 36d
	ret

; ### End of driver function. ### 
rte:
	mov ebx, 0	 ;return 0 status on exit - 'No errors'
	mov eax, 1	 ;invoke SYS_EXIT system call (kernel opcode 1)
	int 80h		 ;generate interrupt

oob:
	push rbp
	mov rdi, rte_oob
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	jmp rte

typeError:
	push rbp
	mov rdi, rte_type
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	jmp rte

param:
	push rbp
	mov rdi, rte_param
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	jmp rte

invalidbounds:
	push rbp
	mov rdi, rte_invalidbounds
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	jmp rte

divisionby0:
	push rbp
	mov rdi, rte_divisionby0
	push r10
	push r11
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
	pop r11
	pop r10
	pop rbp
	jmp rte
