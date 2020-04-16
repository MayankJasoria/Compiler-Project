global main
extern printf, scanf

section .data
  	single_value1: dd 9.35
	single_value2: dd 4.87
	greater:	db	"Greater",0xA,0
	lesser:		db	"Lesser",0xA,0
	equal:		db	"Equal",0xA,0
	error:		db	"Error",0xA,0
section .text
main:
	finit                         ;reset fpu stacks to default
    fld    dword [single_value2]  ;push single_value2 to fpu stack(st1)
    fld    dword [single_value1]  ;push single_value1 to fpu stack(st0)
    fcom   st0, st1               ;compare st0 with st1
    fstsw  ax                     ;ax := fpu status register

    and    eax, 0100011100000000B ;take only condition code flags
    cmp    eax, 0000000000000000B ;is st0 > source ?
    je     .print_greater
    cmp    eax, 0000000100000000B ;is st0 < source ?
    je     .print_less
    cmp    eax, 0100000000000000B ;is st0 = source ?
    je     .print_equal
    jmp    .print_error      ;else, st0 or source are undefined

.print_greater:
	push rbp
	mov rbp, rsp

    mov rdi, greater
    jmp    .print_write

.print_less:
	push rbp
	mov rbp, rsp

    mov rdi, lesser
    jmp    .print_write

.print_equal:
	push rbp
	mov rbp, rsp

    mov rdi, equal
    jmp    .print_write

.print_error:
	push rbp
	mov rbp, rsp

    mov rdi, error
    jmp    .print_write

.print_write:
	mov rax, 0
    call printf
	
	;---- reset stack----
	mov rsp, rbp
	pop rbp
	ret
	
