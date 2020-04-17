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
sub rsp, 14d
mov word [dynamic], 0
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
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
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
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
	call scanf
mov rsp, qword [rspreserve]
	pop rbp
; --- END: getInputElement() --- 
; --- END: takeInput(): type: Integer, Name: x --- 
; --- START: takeInput(): type: Integer, Name: y --- 
	push rbp
	mov rdi, op1
	mov rsi, type_int
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
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
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
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
	jg label_0
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_1
label_0:
	mov r8b, 1
label_1:
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
	jle label_2
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_3
label_2:
	mov r8b, 1
label_3:
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
	jl label_4
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_5
label_4:
	mov r8b, 1
label_5:
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
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
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
	jz label_6
	mov rdi, output_fmt_string
	mov rsi, bool_true
	jmp label_7
label_6:
	mov rdi, output_fmt_string
	mov rsi, bool_false
	mov rdi, bool_false
label_7:
mov qword [rspreserve], rsp
and rsp, 0xfffffffffffffff0
sub rsp, 10000B
	call printf
mov rsp, qword [rspreserve]
	pop rbp
; --- END: outputArrayElement() for u--- 

; ### Resetting(aligning) the rsp. ### 
	movsx rax, word [dynamic]
	add rsp, rax
	add rsp, 14d
	ret

; ### End of driver function. ### 
