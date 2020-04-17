global main
extern printf, scanf

section .data
  	single_value1: dd 9.35
	single_value2: dd 4.87
	greater:	db	"Greater",0xA,0
	lesser:		db	"Lesser",0xA,0
	equal:		db	"Equal",0xA,0
	error:		db	"Error",0xA,0
    fmt:    db  "Result: %lf",0xA,0
section .text
main:
    mov rax, 0X1234560789ABCDEF
	mov rbx, 0
	push rbx
	push rax
	push rbx
	pop  rbx
	mov rbx, [rsp+1]
	ret