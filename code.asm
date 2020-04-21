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
swap:
mov word [dynamic], 0
	mov rax, rbp
	sub rax, 18d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: moveOffsetToOffset(): lhsoff = 21, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 23d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 21, rhsoff = 0, type = Integer ---
label_0:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 23d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 20d
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
	jle label_2
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_3
label_2:
	mov r8b, 1
label_3:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 5d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: LE, type: Integer --- 
	mov rax, rsp
	sub rax, 5d
	mov dl, byte [rax]
	cmp dl, 0
	jz label_1
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 23d
	mov r8w, word [rax]
	mov rsi, 13d
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
label_4:
	add r9w, r8w
	dec rcx
	jnz label_4
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 9d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: moveOffsetToOffset(): lhsoff = 23, rhsoff = 5, type = Real ---
	mov rax, rsp
	sub rax, 9d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 27d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 23, rhsoff = 5, type = Real ---
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 27d
	sub rsp, 4d
	mov eax, dword [rcx]
	mov dword [rsp], eax
	mov rcx, qword [rbp]
	sub rcx, 16d
	sub rsp, 4d
	mov eax, dword [rcx]
	mov dword [rsp], eax
	sub rsp, 4d
	call add
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
	mov rdx, rbp
	sub rdx, 27d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 12d
	mov ecx, dword [rax]
	mov dword [rdx], ecx
	mov rax, rbp
	sub rax, 27d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 13d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 23d
	mov r8w, word [rax]
	mov rsi, 15d
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
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 9, type = Real ---
	mov rax, rsp
	sub rax, 13d
	mov r8d, dword [rax]
	mov rax, rdx
	sub rax, r9
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 9, type = Real ---
	mov rax, rbp
	sub rax, 23d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 15d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 1d
	mov rdx, rsp
	sub rdx, 17d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 13, rightOp: 15, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 15d
	mov r10, rsp
	sub r10, 17d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 19d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 13, rightOp: 15, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 21, rhsoff = 17, type = Integer ---
	mov rax, rsp
	sub rax, 19d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 23d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 21, rhsoff = 17, type = Integer ---
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_0
label_1:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 23d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov rax, rbp
	sub rax, 20d
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
	jle label_6
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_7
label_6:
	mov r8b, 1
label_7:
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
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begin of a moduledef. ### 
add:
mov word [dynamic], 0
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
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 4d
	mov r10, rsp
	sub r10, 8d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 12d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 0, rightOp: 4, operator: PLUS, type: Real --- 
; --- START: moveOffsetToOffset(): lhsoff = 8, rhsoff = 8, type = Real ---
	mov rax, rsp
	sub rax, 12d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 12d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 8, rhsoff = 8, type = Real ---
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begin of a moduledef. ### 
fun1:
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
	mov r9, 40d
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
	mov r9, 42d
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
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 38d
	mov ax, word [rax]
	cmp ax, 1d
	jnz label_9
	mov rax, rbp
	sub rax, 52d
	mov qword [rax], rsp
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 40d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 42d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	mov rsi, 37d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_10:
	sub rsp, 4d
	add r9w, 4d
	dec rcx
	jnz label_10
	mov word [dynamic], r9w
; --- START: takeInput(): type: Array, Name: dyn --- 
	push rbp
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 40d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 42d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_float
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
	sub rax, 52d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 40d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 42d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_11:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_float
	sub rdx, 4d
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
	sub rdx, 4d
	dec rcx
	cmp rcx, 0x0
	jnz label_11
; --- END: takeInput(): type: Array, Name: dyn --- 
label_12:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 38d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 5d
	mov rdx, rsp
	sub rdx, 4d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: LT, type: Integer --- 
	mov rax, rsp
	sub rax, 2d
	mov r10, rsp
	sub r10, 4d
	mov r8w, word [rax]
	mov r9w, word [r10]
	cmp r8w, r9w
	jl label_14
; --- START: if0else1() --- 
	mov r8b, 0
	jmp label_15
label_14:
	mov r8b, 1
label_15:
; --- END: if0else1() --- 
	mov rax, rsp
	sub rax, 5d
	mov byte [rax], r8b
; --- START: applyOperator(): leftOp: 0, rightOp: 2, operator: LT, type: Integer --- 
	mov rax, rsp
	sub rax, 5d
	mov dl, byte [rax]
	cmp dl, 0
	jz label_13
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array arr: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 38d
	mov r8w, word [rax]
	mov rsi, 42d
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
label_16:
	add r9w, r8w
	dec rcx
	jnz label_16
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array arr: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 9d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: moveOffsetToOffset(): lhsoff = 52, rhsoff = 5, type = Real ---
	mov rax, rsp
	sub rax, 9d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 56d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 52, rhsoff = 5, type = Real ---
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 40d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 42d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
; --- START: fetchArraybyIndex() for array dyn: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 38d
	mov r8w, word [rax]
	mov rsi, 43d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 52d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 4d
label_17:
	add r9w, r8w
	dec rcx
	jnz label_17
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array dyn: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 13d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
; --- START: moveOffsetToOffset(): lhsoff = 56, rhsoff = 9, type = Real ---
	mov rax, rsp
	sub rax, 13d
	mov r8d, dword [rax]
	mov rax, rbp
	sub rax, 60d
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = 56, rhsoff = 9, type = Real ---
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 56d
	sub rsp, 4d
	mov eax, dword [rcx]
	mov dword [rsp], eax
	mov rcx, qword [rbp]
	sub rcx, 60d
	sub rsp, 4d
	mov eax, dword [rcx]
	mov dword [rsp], eax
	sub rsp, 4d
	call add
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
	mov rdx, rbp
	sub rdx, 56d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 12d
	mov ecx, dword [rax]
	mov dword [rdx], ecx
	mov rax, rbp
	sub rax, 56d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 17d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array arr: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 38d
	mov r8w, word [rax]
	mov rsi, 45d
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
label_18:
	add r9w, r8w
	dec rcx
	jnz label_18
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array arr: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 13, type = Real ---
	mov rax, rsp
	sub rax, 17d
	mov r8d, dword [rax]
	mov rax, rdx
	sub rax, r9
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 13, type = Real ---
	mov rax, rbp
	sub rax, 56d
; --- START: pushTemporary(): type = Real ---
	mov edx, dword [rax]
	mov rax, rsp
	sub rax, 21d
	mov dword [rax], edx
; --- END: pushTemporary(): type = Real ---
	mov rdx, rsp
	sub rdx, 25d
	mov dword [rdx], __float32__(4.150000)
; --- START: applyOperator(): leftOp: 17, rightOp: 21, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 21d
	mov r10, rsp
	sub r10, 25d
	finit
	fld dword [rax]
	fld dword [r10]
	fadd
	mov rax, rsp
	sub rax, 29d
	fstp dword [rax]
; --- START: applyOperator(): leftOp: 17, rightOp: 21, operator: PLUS, type: Real --- 
	mov rax, rsp
	sub rax, 29d
	finit
	fld dword [rax]
	fchs
	mov rdx, rsp
	sub rdx, 33d
	fstp dword [rdx]
	mov rax, rbp
	sub rax, 34d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 36d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array arr3: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 38d
	mov r8w, word [rax]
	mov rsi, 46d
	cmp r8w, r10w
	jl oob
	cmp r8w, r11w
	jg oob
	mov rax, rbp
	sub rax, 32d
	mov rdx, qword [rax]
	mov r9w, 0
	sub r8w, r10w
	inc r8w
	mov rcx, 4d
label_19:
	add r9w, r8w
	dec rcx
	jnz label_19
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array arr3: base: rdx, offset: r9 --- 
; --- START: moveOffsetToOffset(): lhsoff = -1, rhsoff = 29, type = Real ---
	mov rax, rsp
	sub rax, 33d
	mov r8d, dword [rax]
	mov rax, rdx
	sub rax, r9
	mov dword [rax], r8d
; --- END: moveOffsetToOffset(): lhsoff = -1, rhsoff = 29, type = Real ---
	mov rax, rbp
	sub rax, 38d
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 35d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
	mov ax, 1d
	mov rdx, rsp
	sub rdx, 37d
	mov word [rdx], ax
; --- START: applyOperator(): leftOp: 33, rightOp: 35, operator: PLUS, type: Integer --- 
	mov rax, rsp
	sub rax, 35d
	mov r10, rsp
	sub r10, 37d
	mov r8w, word [rax]
	mov r9w, word [r10]
	add r8w, r9w
	mov rax, rsp
	sub rax, 39d
	mov word [rax], r8w
; --- START: applyOperator(): leftOp: 33, rightOp: 35, operator: PLUS, type: Integer --- 
; --- START: moveOffsetToOffset(): lhsoff = 36, rhsoff = 37, type = Integer ---
	mov rax, rsp
	sub rax, 39d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 38d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 36, rhsoff = 37, type = Integer ---
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_12
label_13:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	jmp label_8
label_9:
	mov rax, rbp
	sub rax, 38d
	mov ax, word [rax]
	cmp ax, 2d
	jnz label_20
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
label_21:
	push rdx
	push rcx
; --- START: outputArrayElement() for arr2 --- 
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
; --- END: outputArrayElement() for arr2--- 
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
	jnz label_21
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
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 20d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
	mov rax, rbp
	sub rax, 22d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 24d
	mov r11w, word [rax]
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 52d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	sub rsp, 14d
	call fun2
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
	mov rdx, rbp
	sub rdx, 38d
	mov rax, rsp
	sub rax, 8
	sub rax, 2
	sub rax, 14d
	mov cx, word [rax]
	mov word [rdx], cx
	mov cx, 2d
label_22:
; --- START: scopeBegin() --- 
	sub rsp, 2d
	mov ax, word [dynamic]
	mov word [rsp], ax
	mov ax, 0
	mov word [dynamic], ax
; --- END: scopeBegin() --- 
	mov rax, rbp
	sub rax, 44d
	mov word [rax], cx
	mov ax, 1d
	mov rdx, rsp
	sub rdx, 2d
	mov word [rdx], ax
	mov rax, rbp
	sub rax, 44d
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
; --- START: moveOffsetToOffset(): lhsoff = 60, rhsoff = 4, type = Integer ---
	mov rax, rsp
	sub rax, 6d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 62d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 60, rhsoff = 4, type = Integer ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 62d
	mov rdx, rbp
; --- START: outputArrayElement() for p --- 
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
; --- END: outputArrayElement() for p--- 
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
	mov rax, rbp
	sub rax, 44d
	mov cx, word[rax]
	inc cx
	cmp cx, 5
	jnz label_22
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
label_23:
	push rdx
	push rcx
; --- START: outputArrayElement() for arr2 --- 
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
; --- END: outputArrayElement() for arr2--- 
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
	jnz label_23
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
	jmp label_8
label_20:
label_8:
; --- START: scopeEnd() --- 
	movsx rax, word [dynamic]
	add rsp, rax
	mov ax, word [rsp]
	mov word [dynamic], ax
	add rsp, 2d
; --- END: scopeEnd() --- 
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
	mov r9, 38d
	mov rdx, rbp
; --- START: outputArrayElement() for sw1 --- 
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
; --- END: outputArrayElement() for sw1--- 
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begin of a moduledef. ### 
fun2:
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
	mov r9, 16d
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
	mov r9, 18d
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
	sub rax, 26d
	mov qword [rax], rsp
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	mov rsi, 74d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_24:
	sub rsp, 2d
	add r9w, 2d
	dec rcx
	jnz label_24
	mov word [dynamic], r9w
; --- START: takeInput(): type: Array, Name: dyn --- 
	push rbp
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 

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
	sub rax, 26d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_25:
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
	jnz label_25
; --- END: takeInput(): type: Array, Name: dyn --- 
	mov rax, rbp
	sub rax, 26d
; --- START: pushTemporary(): type = Array ---
	mov rdx, qword [rax]
	mov rax, rsp
	sub rax, 8d
	mov qword [rax], rdx
; --- END: pushTemporary(): type = Array ---
	mov rsi, 76d
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
	mov r8w, r10w
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	cmp r8w, r10w
	jnz typeError
	mov rax, rbp
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
	mov r8w, r11w
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
	cmp r8w, r11w
	jnz typeError
; --- START: moveOffsetToOffset(): lhsoff = 0, rhsoff = 0, type = Array ---
	mov rax, rsp
	sub rax, 8d
	mov r8, qword [rax]
	mov rax, rbp
	sub rax, 8d
	mov qword [rax], r8
; --- END: moveOffsetToOffset(): lhsoff = 0, rhsoff = 0, type = Array ---
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of dyn ---
	mov rax, rbp
	sub rax, 16d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 18d
	mov r11w, word[rax]
; --- END: got left and right index of dyn in r10w and r11w --- 
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
	sub rax, 26d
	mov rdx, qword [rax]
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9, 2d
label_26:
	push rdx
	push rcx
; --- START: outputArrayElement() for dyn --- 
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
; --- END: outputArrayElement() for dyn--- 
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
	jnz label_26
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
	sub rax, 10d
	mov r10w, word [rax]
	mov rax, rbp
	sub rax, 12d
	mov r11w, word [rax]
; --- START: fetchArraybyIndex() for array A: base: rdx, offset: r9  --- 
	mov rax, rbp
	sub rax, 16d
	mov r8w, word [rax]
	mov rsi, 78d
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
	mov rcx, 2d
label_27:
	add r9w, r8w
	dec rcx
	jnz label_27
	movsx r9, r9w
; --- END: fetchArraybyIndex() for array A: base: rdx, offset: r9 --- 
	mov rax, rdx
	sub rax, r9
; --- START: pushTemporary(): type = Integer ---
	mov dx, word [rax]
	mov rax, rsp
	sub rax, 2d
	mov word [rax], dx
; --- END: pushTemporary(): type = Integer ---
; --- START: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Integer ---
	mov rax, rsp
	sub rax, 2d
	mov r8w, word [rax]
	mov rax, rbp
	sub rax, 14d
	mov word [rax], r8w
; --- END: moveOffsetToOffset(): lhsoff = 12, rhsoff = 0, type = Integer ---
	movsx rax, word [dynamic]
	add rsp, rax
	ret

; ### Begining of the driver program. ### 
main:
mov rbp, rsp
	sub rsp, 30d
	mov word [dynamic], 0
	mov ax, 2d
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
	sub rax, 14d
	mov qword [rax], rsp
; --- START: get left and right index of A ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of A in r10w and r11w --- 
	mov rsi, 88d
	cmp r10w, r11w
	jg invalidbounds
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
	sub rax, 22d
	mov qword [rax], rsp
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov rsi, 89d
	cmp r10w, r11w
	jg invalidbounds
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
	mov rax, rbp
	sub rax, 30d
	mov qword [rax], rsp
; --- START: get left and right index of C ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of C in r10w and r11w --- 
	mov rsi, 90d
	cmp r10w, r11w
	jg invalidbounds
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
	mov r9w, word [dynamic]
label_30:
	sub rsp, 4d
	add r9w, 4d
	dec rcx
	jnz label_30
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
	sub rax, 14d
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
label_31:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_float
	sub rdx, 4d
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
	sub rdx, 4d
	dec rcx
	cmp rcx, 0x0
	jnz label_31
; --- END: takeInput(): type: Array, Name: A --- 
; --- START: takeInput(): type: Array, Name: B --- 
	push rbp
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
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
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_32:
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
	jnz label_32
; --- END: takeInput(): type: Array, Name: B --- 
; --- START: takeInput(): type: Array, Name: C --- 
	push rbp
; --- START: get left and right index of C ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of C in r10w and r11w --- 

; --- Asking for user input for Array ---
	mov rdi, op2
	mov si, r11w
	sub si, r10w
	movsx rsi, si
	inc rsi
	mov rdx, type_float
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
	sub rax, 30d
	mov rdx, qword [rax]

; --- Loop for scanning each element of the array --- 
; --- START: get left and right index of C ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of C in r10w and r11w --- 
	mov cx, r11w
	sub cx, r10w
	movsx rcx, cx
	inc rcx
label_33:
	push rdx
	push rcx
	push rbp

; --- Scanning input ---
	mov rdi, fmt_float
	sub rdx, 4d
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
	sub rdx, 4d
	dec rcx
	cmp rcx, 0x0
	jnz label_33
; --- END: takeInput(): type: Array, Name: C --- 
; --- Setting up the stack frame ---
	sub rsp, 2
	mov ax, word [dynamic]
	mov word [rsp], ax
	sub rsp, 8
	mov qword [rsp], rbp
	mov rbp, rsp
	mov rcx, qword [rbp]
	sub rcx, 14d
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
mov rsi, 94d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	mov rcx, qword [rbp]
	sub rcx, 22d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 94d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	mov rcx, qword [rbp]
	sub rcx, 30d
	sub rsp, 8d
	mov r9, rbp
	mov rbp, qword [rbp]
; --- START: get left and right index of C ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of C in r10w and r11w --- 
	mov rbp, r9
	mov rax, qword [rcx]
	mov qword [rsp], rax
mov rsi, 94d
	sub rsp, 2d
	mov word[rsp], r10w
	sub rsp, 2d
	mov word[rsp], r11w
	mov rcx, qword [rbp]
	sub rcx, 6d
	sub rsp, 2d
	mov ax, word [rcx]
	mov word [rsp], ax
	sub rsp, 24d
	call fun1
	mov rax, qword [rbp]
	add rbp, 8d
	mov dx, word [rbp]
	mov word [dynamic], dx
	add rbp, 2d
	mov rsp, rbp
	mov rbp, rax
; --- START: giveInput() type: AST_NODE_VARIDNUM --- 
; --- START: get left and right index of B ---
	mov rax, rbp
	sub rax, 2d
	mov r10w, word[rax]
	mov rax, rbp
	sub rax, 4d
	mov r11w, word[rax]
; --- END: got left and right index of B in r10w and r11w --- 
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
label_34:
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
	jnz label_34
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
	add rsp, 30d
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
