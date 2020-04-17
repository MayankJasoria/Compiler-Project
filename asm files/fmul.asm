global main
extern printf, scanf

section .data
  	value1: dd 9.35
	value2: dd 4.87
	fmt: db	"Result: %lf",0xA,0
section .bss
	res:	resb 4
section .text
main:
	finit                         ;reset fpu stacks to default
    fld    dword [value2]  ;push single_value2 to fpu stack(st1)
    fld    dword [value1]  ;push single_value1 to fpu stack(st0)
	fmul
	fstp   dword [res]
    
	;---- setup stack ---
	push rbp
	mov rbp, rsp
	mov rdi, fmt
	cvtss2sd xmm0, dword [res]
	mov rax,1
    call printf
	
	;---- reset stack----
	mov rsp, rbp
	pop rbp
	ret
	
