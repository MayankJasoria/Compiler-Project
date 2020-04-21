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
nested:
mov word [dynamic], 0
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r10w, 1d
	mov r11w, 4d
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
	mov rax, rbp
	sub rax, 22d
	mov rcx, rax
	mov qword[rcx], rax
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
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
	sub rax, 22d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
; --- END: got left and right index of A in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_1:
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
	jnz label_1
; --- END: takeInput(): type: Array, Name: A --- 
	mov ax, 9d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 30, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 32d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 30, rhsoff = 0, type = Integer ---
label_2:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 32d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 0d
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jg label_4
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_5
label_4:
	mov r8b, 1
label_5:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 5d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: GT, type: Integer --- 
	mov rax, rsp
	sub rax, 5d
	mov dl, byte [rax]
	cmp dl, 0
	jz label_3
; --- START: takeInput(): type: Integer, Name: i --- 
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
	mov r9, 32d
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
; --- END: takeInput(): type: Integer, Name: i --- 
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
	mov cx, 1d
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
	mov rax, rbp
	sub rax, 40d
	mov rcx, rax
	mov qword[rcx], rax
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
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
	sub rax, 40d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
; --- END: got left and right index of A in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_7:
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
	jnz label_7
; --- END: takeInput(): type: Array, Name: A --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
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
	sub rax, 40d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_8:
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
	jnz label_8
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
	cmp cx, 3
	jnz label_6
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov r10w, 1d
	mov r11w, 4d
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
	sub rax, 22d
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
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 17d
	mov word [dynamic], 0
	mov ax, 1d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 0, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 2d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 0, rhsoff = 0, type = Integer ---
	mov ax, 4d
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
	mov rax, rbp
	sub rax, 12d
	mov qword [rax], rsp
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov rsi, 28d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_10:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_10
	mov word [dynamic], r9w
	mov rdx, rsp
	sub rdx, 4d
	mov dword [rdx], __float32__(3.141593)
	mov rax, rsp
	sub rax, 4d
	finit
	fld dword [rax]
	fchs
	mov rdx, rsp
	sub rdx, 8d
	fstp dword [rdx]
; --- START: moveOffsetToOffset(): lhsoff = 13, rhsoff = 4, type = Real ---
	mov rax, rsp
	sub rax, 8d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 17d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 13, rhsoff = 4, type = Real ---
	mov al, 1d
	mov rdx, rsp
	sub rdx, 1d
	mov byte [rdx], al
; --- START: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Boolean ---
	mov rax, rsp
	sub rax, 1d
	mov r8b, byte [rax]
	mov rax, rbp
	sub rax, 13d
	mov byte [rax], r8b
; --- END: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Boolean ---
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 12d
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
mov rsi, 33d
mov r8w, 1d
cmp r8w, r10w
jnz param
mov r8w, 4d
cmp r8w, r11w
jnz param
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	mov rcx, qword [rbp]
	sub rcx, 2d
	sub rsp, 2d
	mov ax, word [rcx]
	mov word [rsp], ax
	sub rsp, 34d
	call nested
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
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
	sub rax, 12d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_11:
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
	jnz label_11
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

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 17d
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
