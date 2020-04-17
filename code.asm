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
	op2: db "Input: Enter %d array elements of %s type for range %d to %d", 0
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
	sub rsp, 34d
	mov word [dynamic], 0
	mov rax, rbp
	sub rax, 22d
	mov qword [rax], rsp
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
; --- END: got left and right index of A in r10w and r11w --- 
	cmp r10w, r11w
	jg rte
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_0:
	sub rsp, 2d
	dec rcx
	jnz label_0
	mov al, 1d
	mov rdx, rsp
	sub rdx, 1d
	mov byte [rdx], al
; --- START: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 14d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Integer ---
	mov ax, 5d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 6, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 8d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 6, rhsoff = 0, type = Integer ---
	mov ax, 9d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
; --- START: moveOffsetToOffset(): lhsoff = 8, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 10d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 8, rhsoff = 0, type = Integer ---
; --- START: takeInput(): type: Integer, Name: x --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
	mov r9, 2d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: x --- 
; --- START: takeInput(): type: Integer, Name: y --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
	mov r9, 4d
; START: --- getInputElement() ---
	push rbp
	mov rdi, fmt_int
	mov rax, rbp
	sub rax, r9
	mov rsi, rax
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call scanf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: y --- 
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
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 6d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 2, rightOp: 4, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 6d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 8d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 2, rightOp: 4, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 0, rightOp: 6, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 8d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 10d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 0, rightOp: 6, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 12d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 14d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 10, rightOp: 12, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 12d
	mov r10, rsp
	sub r10, 14d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 16d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 10, rightOp: 12, operator: MINUS, type: Integer --- 
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 18d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 14, rightOp: 16, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 16d
	mov r10, rsp
	sub r10, 18d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 20d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 14, rightOp: 16, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 8, rightOp: 18, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 10d
	mov r10, rsp
	sub r10, 20d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 22d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 8, rightOp: 18, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 24d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 2d
	mov rdx, rsp
	sub rdx, 26d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 22, rightOp: 24, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 24d
	mov r10, rsp
	sub r10, 26d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 28d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 22, rightOp: 24, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 20, rightOp: 26, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 22d
	mov r10, rsp
	sub r10, 28d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 30d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 20, rightOp: 26, operator: PLUS, type: Integer --- 
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 32d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 34d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 30, rightOp: 32, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 32d
	mov r10, rsp
	sub r10, 34d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 36d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 30, rightOp: 32, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 28, rightOp: 34, operator: MINUS, type: Integer --- 
	mov rax, rsp
	sub rax, 30d
	mov r10, rsp
	sub r10, 36d
	mov r8w, word [rax]
	mov r9w, word [r10]
	sub r8w, r9w
	mov rax, rsp
	sub rax, 38d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 28, rightOp: 34, operator: MINUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 4, rhsoff = 36, type = Integer ---
	mov rax, rsp
	sub rax, 38d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 6d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 4, rhsoff = 36, type = Integer ---
	mov rax, rbp
	sub rax, 6d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 10d
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
	jg label_1
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
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: GT, type: Integer --- 
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 7d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 10d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 9d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 5, rightOp: 7, operator: LE, type: Integer --- 
	mov rax, rsp
	sub rax, 7d
	mov r10, rsp
	sub r10, 9d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jle label_3
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_4
label_3:
	mov r8b, 1
label_4:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 10d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 5, rightOp: 7, operator: LE, type: Integer --- 
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
	mov rax, rbp
	sub rax, 2d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 13d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 4d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 15d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 11, rightOp: 13, operator: LT, type: Integer --- 
	mov rax, rsp
	sub rax, 13d
	mov r10, rsp
	sub r10, 15d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jl label_5
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_6
label_5:
	mov r8b, 1
label_6:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 16d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 11, rightOp: 13, operator: LT, type: Integer --- 
; --- START: applyOperator(): leftOp: 10, rightOp: 15, operator: AND, type: Boolean --- 
	mov rax, rsp
	sub rax, 11d
	mov r10, rsp
	sub r10, 16d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	and r8b, r9b
	mov rax, rsp
	sub rax, 17d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 10, rightOp: 15, operator: AND, type: Boolean --- 
	mov rax, rbp
	sub rax, 13d
; --- START: pushTemporary(): type = Boolean ---
	mov dl, byte [rax]
	mov rax, rsp
	sub rax, 18d
	mov byte [rax], dl
; --- END: pushTemporary(): type = Boolean ---
; --- START: applyOperator(): leftOp: 16, rightOp: 17, operator: AND, type: Boolean --- 
	mov rax, rsp
	sub rax, 17d
	mov r10, rsp
	sub r10, 18d
	mov r8b, byte [rax]
	mov r9b, byte [r10]
	and r8b, r9b
	mov rax, rsp
	sub rax, 19d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 16, rightOp: 17, operator: AND, type: Boolean --- 
; --- START: moveOffsetToOffset(): lhsoff = 13, rhsoff = 18, type = Integer ---
	mov rax, rsp
	sub rax, 20d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 15d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 13, rhsoff = 18, type = Integer ---
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
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: outputArrayElement() for z--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 13d
	mov rdx, rbp
; --- START: outputArrayElement() for u --- 
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
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: outputArrayElement() for u--- 
; --- START: takeInput(): type: Array, Name: A --- 
	push rbp
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
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
	sub rax, 22d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_9:
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
	jnz label_9
	pop rbp
; --- END: takeInput(): type: Array, Name: A --- 
	mov rax, rbp
	sub rax, 8d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 2d
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
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
; --- END: got left and right index of A in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov r8w, 13d
	mov rax, rbp
	sub rax, 22d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 14d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 2d
	mov rdx, rsp
	sub rdx, 16d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 6, rightOp: 14, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 8d
	mov r10, rsp
	sub r10, 16d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 18d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 6, rightOp: 14, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 4, rightOp: 16, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 6d
	mov r10, rsp
	sub r10, 18d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 20d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 4, rightOp: 16, operator: PLUS, type: Integer --- 
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
; --- END: got left and right index of A in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov r8w, 14d
	mov rax, rbp
	sub rax, 22d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 28d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 3d
	mov rdx, rsp
	sub rdx, 30d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 20, rightOp: 28, operator: MUL, type: Integer --- 
	mov rax, rsp
	sub rax, 22d
	mov r10, rsp
	sub r10, 30d
	mov r8w, word [rax]
	mov r9w, word [r10]
	mov ax, r8w
	mul r9w
	mov r8w, ax
	mov rax, rsp
	sub rax, 32d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 20, rightOp: 28, operator: MUL, type: Integer --- 
; --- START: applyOperator(): leftOp: 18, rightOp: 30, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 20d
	mov r10, rsp
	sub r10, 32d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 34d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 18, rightOp: 30, operator: PLUS, type: Integer --- 
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
; --- END: got left and right index of A in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov r8w, 15d
	mov rax, rbp
	sub rax, 22d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 42d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: applyOperator(): leftOp: 32, rightOp: 34, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 34d
	mov r10, rsp
	sub r10, 36d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 44d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 32, rightOp: 34, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 2, rhsoff = 42, type = Integer ---
	mov rax, rsp
	sub rax, 44d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 4d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 2, rhsoff = 42, type = Integer ---
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
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: outputArrayElement() for y--- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of A ---
	mov rbx, 10d
	mov rbx, 15d
; --- END: got left and right index of A in r10w and r11w --- 
; --- idNode->next is NULL --- 
	push rbp
	mov rdi, output_fmt_plain
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
	mov rax, rbp
	sub rax, 22d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_13:
	push rdx
	push rcx
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
	pop rcx
	pop rdx
	push rbp
	mov rdi, single_space
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
	sub rdx, 2d
	dec rcx
	jnz label_13
	pop rbp
	push rbp
	mov rdi, end_line
; --- START: ALIGN STACK---
	mov qword [rspreserve], rsp
	and rsp, 0xfffffffffffffff0
	sub rsp, 10000B
; --- END: ALIGN STACK ---
	call printf
	mov rsp, qword [rspreserve]
	pop rbp
; --- END: giveInput() --- 

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
