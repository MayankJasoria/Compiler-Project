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
	finit                         ;reset fpu stacks to default
    fld    dword [single_value1]  ;push single_value1 to fpu stack(st0)
    fchs
    fstp   dword [single_value2]

    push rbp
    mov rbp, rsp

    mov rdi, fmt
    cvtss2sd xmm0, dword [single_value2]
    mov rax, 1
    call printf  
    mov rsp, rbp
    pop rbp
    
	ret