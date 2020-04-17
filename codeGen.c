#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures/st.h"
#include "data_structures/ast.h"
#include "codeGen.h"
#include "codeGenDef.h"

void emitCodeInit(const char* fname) {
    /* Open fname */
    fp = open(fname, "w");
}

void emitCodeChildren(ASTNode * head, char * fname) {
	
    ASTNode* ch = head;
    while(ch != NULL) {
        traverseAST(ch, fname);
        ch = ch -> next;
    }
}

int getIDOffset(ASTNode * idNode) {
	SymTableVar * tmp = fetchVarData(idNode -> localST, idNode -> nodeData.leaf -> tn -> lex);
	return tmp -> offset;
}

/**
 * Returns temporary offset of the node in the expression
 */ 
int getExprOffset(ASTNode * expr) {
	if(expr -> type == AST_NODE_LEAF)
		return expr -> nodeData.leaf -> temporaryOffset;
	else if(expr -> type == AST_NODE_VARIDNUM)
		return expr -> nodeData.var -> temporaryOffset;
	else if(expr -> type == AST_NODE_AOBEXPR)
		return expr -> nodeData.AOBExpr -> temporaryOffset;
	else if(expr -> type == AST_NODE_UNARY)
		return expr -> nodeData.unary -> temporaryOffset;
}

/**
 * Returns datatype of expression
 * @param expr	AST Node representing the root of expression subtree
 */
int getExprType(ASTNode * expr) {
	
	if(expr -> type == AST_NODE_LEAF)
		return expr -> nodeData.leaf -> dataType;
	else if(expr -> type == AST_NODE_VARIDNUM)
		return expr -> nodeData.var -> dataType;
	else if(expr -> type == AST_NODE_AOBEXPR)
		return expr -> nodeData.AOBExpr -> dataType;
	else if(expr -> type == AST_NODE_UNARY)
		return expr -> nodeData.unary -> dataType;
}

/**
 * Populates  	r10w : left index
 * 				r11w : right index 
 */
void getLeftRightIndex(SymTableVar * id) {
	
	int lft, right;
	if(strcmp(id -> sdt.r -> lowId, "") == 0) {
		lft = id -> sdt.r -> low;
		fprintf(fp, "mov rbx, %dd\n", lft);		
	}
	else {
		SymTableVar * l = fetchVarData(id -> table, id -> sdt.r -> lowId);
		if(l -> isAssigned == 0) {
			rte();
		}
		fprintf(fp, "mov rax, rbp\n");
		fprintf(fp, "sub rax, %dd\n", typeSize[AST_TYPE_INT] + l -> offset);
		fprintf(fp, "mov r10w, word[rax]\n");
	}
	if(strcmp(id -> sdt.r -> highId, "") == 0) { 
		right = id -> sdt.r -> high;
		fprintf(fp, "mov rbx, %dd\n", right);	
	}
	else {
		SymTableVar * r = fetchVarData(id -> table, id -> sdt.r -> highId);
		if(r -> isAssigned == 0) {
			rte();
		}
		fprintf(fp, "mov rax, rbp\n");
		fprintf(fp, "sub rax, %dd\n", typeSize[AST_TYPE_INT] + r -> offset);
		fprintf(fp, "mov r11w, word[rax]\n");
	}
}

void getInputElement() {

	fprintf(fp, "push rbp\n");
	fprintf(fp, "mov rdi, fmt_int\n");
	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, r9\n");
	fprintf(fp, "mov rsi, rax\n");
	fprintf(fp, "call scanf\n");
	fprintf(fp, "pop rbp\n");
}

/**
 * r9 <- offset relative to base address of array, the offset, base address rdx
 * @param arr	AST node of the array
 * @param index	AST Node specifying index
 */
void fetchArraybyIndex(ASTNode * arr, ASTNode * index) {

	/* Array index */
	ASTNode * i = index;

	/* Fetch array from symbol table */ 
	SymTableVar * id = fetchVarData(arr -> localST, arr -> nodeData.leaf -> tn -> lex);
	
	/* DataType of elements of array */
	astDataType type = id -> sdt.r -> dataType;
	int offset = id -> offset;
	int idx;
	
	/* store the value of the index in r8w */
	if(i -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		/* index is of type NUM */
		idx = i -> nodeData.leaf -> tn -> value.val_int;
		fprintf(fp, "mov r8w, %dd\n", idx);
	}
	else {
		/* index is of type ID */
		SymTableVar * tmp = fetchVarData(arr -> localST, i -> nodeData.leaf -> tn -> lex);
		if(tmp -> isAssigned == 0) {
			rte();
		}
		fprintf(fp, "mov rax, rbp\n");
		fprintf(fp, "sub rax, %dd\n", typeSize[AST_TYPE_INT] + tmp -> offset);
		fprintf(fp, "mov r8w, word [rax]\n");
	}
	/* TODO: write this in assembly */
	// if(idx < lft || idx > right) {
	// 	rte();
	// }
	/* Move base address of array to r8x */
	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
	fprintf(fp, "mov rdx, qword [rax]\n");

	/* compute element address as: [rdx - (r8w - r10w + 1) * width] */
	fprintf(fp, "mov r9w, 0\n");
	fprintf(fp, "sub r8w, r10w\n");
	fprintf(fp, "inc r8w\n");
	fprintf(fp, "mov rcx, %dd\n", typeSize[type]);
	fprintf(fp, "label_%d:\n", label_num++);
	fprintf(fp, "add r9w, r8w\n");		
	fprintf(fp, "dec rcx\n");
	fprintf(fp, "jnz label_%d\n", label_num - 1);
	fprintf(fp, "movsz r9, r9w\n");
}

/**
 * NOTE: Function was initially designed to modularize arrays,
 * but later found out that this can be reused for non array types as well.
 * don't go by the name
 */
void outputArrayElement(SymTableVar * id) {
	
	astDataType type = id -> sdt.r -> dataType;

	fprintf(fp, "push rbp\n");
	if(type == AST_TYPE_INT) {
		fprintf(fp, "mov rdi, output_fmt_int\n");
		fprintf(fp, "mov rax, rdx\n");
		fprintf(fp, "sub rax, r9\n");
		fprintf(fp, "mov si, word[rax]");
	}
	else if(type == AST_TYPE_REAL) {
		fprintf(fp, "mov rdi, output_fmt_float\n");
		fprintf(fp, "mov rax, rdx\n");
		fprintf(fp, "sub rax, r9\n");
		fprintf(fp, "cvtss2sd xmm0, dword[rax]\n");
		fprintf(fp, "mov rax, 1\n");
	}
	else if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "mov rax, rdx\n");
		fprintf(fp, "sub rax, r9\n");
		fprintf(fp, "mov al, byte[rax]\n");
		fprintf(fp, "cmp al, 0\n");
		fprintf(fp, "jz label_%d\n", label_num++);
		fprintf(fp, "mov rdi, bool_true\n");
		fprintf(fp, "jmp label_%d\n", label_num++);
		fprintf(fp, "label_%d:\n", label_num - 2);
		fprintf(fp, "mov rdi, bool_false\n");
		fprintf(fp, "label_%d:\n", label_num - 1);
	}
	fprintf(fp, "call printf\n");
	fprintf(fp, "pop rbp\n");
}

/**
 * Emits code for copying rhs to lhs
 * If lhsOff is -1, left hand side is treated as an array and assumed
 * that rdx is base and r9 is offset, already emitted.
 * @param lshOff
 * @param rhsOff
 * @param type
 */ 
void moveOffsetToOffset(int lhsOff, int rhsOff, astDataType type) {

	/* offset of rhs is in rax */
	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, %dd\n", rhsOff + typeSize[type]);
	
	/*  */
	if(type == AST_TYPE_INT) {
		fprintf(fp, "mov r8w, word [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "mov rax, rdx\n");
			fprintf(fp, "sub rax, r9\n");
		}
		else {
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rbp, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "mov word [rax], r8w\n");
	}
	if(type == AST_TYPE_REAL) {
		fprintf(fp, "mov r8d, dword [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "mov rax, rdx\n");
			fprintf(fp, "sub rax, r9\n");
		}
		else {
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rbp, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "mov dword [rax], r8d\n");
	}
	if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "mov r8b, byte [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "mov rax, rdx\n");
			fprintf(fp, "sub rax, r9\n");
		}
		else {
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rbp, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "mov byte [rax], r8b\n");
	}
}

void if0else1() {
	fprintf(fp, "mov r8b, 0\n");
	fprintf(fp, "jmp label_%d\n", label_num++);
	fprintf(fp, "label_%d:\n", label_num - 2);
	fprintf(fp, "mov r8b, 1\n");
	fprintf(fp, "label_%d\n", label_num - 1);
}

/**
 * Floating point operations source: https://gist.github.com/nikAizuddin/0e307cac142792dcdeba
 *	cmp    eax, 0000000000000000B ;is st0 > source ?
 *  je     .example_11_greater
    cmp    eax, 0000000100000000B ;is st0 < source ?
    je     .example_11_less
    cmp    eax, 0100000000000000B ;is st0 = source ?
    je     .example_11_equal

 */
void applyOperator(int leftOp, int rightOp, ASTNode * operator, astDataType type) {

	fprintf(fp, "mov rax, rsp\n");
	fprintf(fp, "sub rax, %dd\n", leftOp + typeSize[type]);
	fprintf(fp, "mov r10, rsp\n");
	fprintf(fp, "sub r10, %dd\n", rightOp + typeSize[type]);
	if(type == AST_TYPE_INT) {
		fprintf(fp, "mov r8w, word [rax]\n");
		fprintf(fp, "mov r9w, word [r10]\n");
	}
	if(type == AST_TYPE_REAL) {
		fprintf(fp, "finit\n");
		fprintf(fp, "fld dword [r10]\n");
		fprintf(fp, "fld dword [rax]\n");
	}
	if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "mov r8b, byte [rax]\n");
		fprintf(fp, "mov r9b, byte [r10]\n");
	}
	switch(operator -> nodeData.leaf -> type) {
		case AST_LEAF_AND:
			fprintf(fp, "and r8b, r9b\n");
			break;
		case AST_LEAF_OR:
			fprintf(fp, "or r8b, r9b\n");
			break;
		case AST_LEAF_LT:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "jlt label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0000000100000000B\n");
				fprintf(fp, "je label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_LE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "jle label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0000000100000000B\n");
				fprintf(fp, "je label_%d\n", label_num++);
				fprintf(fp, "cmp eax, 0100000000000000B\n");
				fprintf(fp, "je label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_GT:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "jgt label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0000000000000000B\n");
				fprintf(fp, "je label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_GE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "jge label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0000000000000000B\n");
				fprintf(fp, "je label_%d\n", label_num++);
				fprintf(fp, "cmp eax, 0100000000000000B\n");
				fprintf(fp, "je label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_EQ: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "je label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0100000000000000B\n");
				fprintf(fp, "je label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_NE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "cmp r8w, r9w\n");
				fprintf(fp, "jne label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fcom st0, st1\n");
				fprintf(fp, "fstsw ax\n");
				fprintf(fp, "and eax, 0100011100000000B\n");
				fprintf(fp, "cmp eax, 0100000000000000B\n");
				fprintf(fp, "jne label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_PLUS: 
			if(type == AST_TYPE_INT) 
				fprintf(fp, "add r8w, r9w\n");
		
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fadd\n");
				fprintf(fp, "sub rsp, 4\n");
				fprintf(fp, "fstp dword [rsp]\n");
			}
			break;
		case AST_LEAF_MINUS: 
			if(type == AST_TYPE_INT) 
				fprintf(fp, "sub r8w, r9w\n");
		
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fsub\n");
				fprintf(fp, "sub rsp, 4\n");
				fprintf(fp, "fstp dword [rsp]\n");
			}
			break;
		case AST_LEAF_MUL: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "mov eax, r8w\n");
				fprintf(fp, "mul r9w\n");
				fprintf(fp, "mov r8w, eax\n");
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fmul\n");
				fprintf(fp, "sub rsp, 4\n");
				fprintf(fp, "fstp dword [rsp]\n");
			}
			break;
		case AST_LEAF_DIV:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "mov edx, 0\n");
				fprintf(fp, "mov eax, r8w\n");
				fprintf(fp, "cmp r9w, 0\n");
				fprintf(fp, "jz rte\n");
				fprintf(fp, "div r9w\n");
				fprintf(fp, "mov r8w, eax\n");
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "fdiv\n");
				fprintf(fp, "sub rsp, 4\n");
				fprintf(fp, "fstp dword [rsp]\n");
			}
			break;
		default:
			break;
	}
	SymTableFunc * par = getParentFunc(operator -> parent -> localST);
	operator -> parent -> nodeData.AOBExpr -> temporaryOffset = par -> dynamicRecSize;
	par -> dynamicRecSize += typeSize[operator -> parent -> nodeData.AOBExpr -> dataType];
	if(operator -> parent -> nodeData.AOBExpr -> dataType == AST_TYPE_INT) {
		fprintf(fp, "mov rax, rsp\n");
		fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "mov word [rax], r8w\n");
	}
	else if(operator -> parent -> nodeData.AOBExpr -> dataType == AST_TYPE_BOOLEAN) {
		fprintf(fp, "mov rax, rsp\n");
		fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "mov byte [rax], r8b\n");
	}
}

void scopeBegin() {

	fprintf(fp, "sub rsp, 2d\n");
	fprintf(fp, "mov ax, word [dynamic]\n");
	fprintf(fp, "mov word [rsp], ax\n");
	fprintf(fp, "mov ax, 0\n");
	fprintf(fp, "mov word [dynamic], ax\n");
}

void scopeEnd() {

	fprintf(fp, "movsx rax, word [dynamic]\n");
	fprintf(fp, "add rsp, rax\n");
	fprintf(fp, "mov ax, word [rsp]\n");
	fprintf(fp, "mov word [dynamic], ax\n");
	fprintf(fp, "add rsp, 2d\n");
}

void takeInput(astDataType t, SymTableVar * idNode) {

	fprintf(fp, "push rbp\n");
	int offset = idNode -> offset;
	// unsigned long long int addr =  
	switch(t) {
		case AST_TYPE_INT: {
			fprintf(fp, "mov rdi, op1\n");
			fprintf(fp, "mov rsi, type_int\n");
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "mov r9, %dd\n", offset + typeSize[t]);
			getInputElement();
		}
		break;
		case AST_TYPE_REAL: {
			fprintf(fp, "mov rdi, op1\n");
			fprintf(fp, "mov rsi, type_float\n");
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "mov r9, %dd\n", offset + typeSize[t]);
			getInputElement();
		}
		break;
		case AST_TYPE_BOOLEAN: {
			fprintf(fp, "mov rdi, op1\n");
			fprintf(fp, "mov rsi, type_bool\n");
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "mov r9, %dd\n", offset + typeSize[t]);
			getInputElement();
		}
		break;
		case AST_TYPE_ARRAY: {
			
			getLeftRightIndex(idNode);
			/* TODO write it in register format */
			// if(lft > right) {
			// 	rte();
			// }
			astDataType type = idNode -> sdt.r -> dataType;

			fprintf(fp, "\n; ### Asking for user input for Array ###\n");
			fprintf(fp, "mov rdi, op2\n");
			fprintf(fp, "movsx rsi, r11w\n");
			fprintf(fp, "sub rsi, r10w\n");
			fprintf(fp, "inc rsi\n");
			if(type == AST_TYPE_INT)
				fprintf(fp, "mov rdx, type_int\n");
			else if(type == AST_TYPE_REAL)
				fprintf(fp, "mov rdx, type_float\n");
			else if(type == AST_TYPE_BOOLEAN)
				fprintf(fp, "mov rdx, type_bool\n");
			fprintf(fp, "mov rcx, r10w\n");
			fprintf(fp, "mov r8, r11w\n");
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");
			
			fprintf(fp, "\n; ### rdx will be the address of the first element of the array ###\n");
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
			fprintf(fp, "mov rdx, qword [rax]\n");

			fprintf(fp, "\n; ### Loop for scanning each element of the array ### \n");

			fprintf(fp, "mov rcx, r11w\n");
			fprintf(fp, "sub rcx, r10w\n");
			fprintf(fp, "inc rcx\n");			

			fprintf(fp, "label_%d:\n", label_num++);
			
			fprintf(fp, "push rdx\n");
			fprintf(fp, "push rcx\n");
			fprintf(fp, "push rbp\n");
			
			fprintf(fp, "\n; ### Scanning input ###\n");
			if(type == AST_TYPE_INT) 
				fprintf(fp, "mov rdi, fmt_int\n");
			else if(type == AST_TYPE_REAL) 
				fprintf(fp, "mov rdi, fmt_float\n");
			else if(type == AST_TYPE_BOOLEAN) 
				fprintf(fp, "mov rdi, fmt_bool\n");

			fprintf(fp, "sub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "mov rsi, rdx\n");
			fprintf(fp, "call scanf\n");
			fprintf(fp, "pop rbp\n");
			fprintf(fp, "pop rcx\n");
			fprintf(fp, "pop rdx\n");
			fprintf(fp, "sub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "dec rcx\n");
			fprintf(fp, "jnz label_%d\n", label_num - 1);
			fprintf(fp, "pop rbp\n");
		}
		break;
	}
}

void giveOutput(ASTNode * curr) {
	ASTNode * ch = curr;
	if(ch -> type == AST_NODE_LEAF) {
		switch(ch -> nodeData.leaf -> type) {
			case AST_LEAF_VARIDNUM_NUM: {
				int val = ch -> nodeData.leaf -> tn -> value.val_int;
				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, output_fmt_int\n");
				fprintf(fp, "mov rsi, %d\n", val);
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			case AST_LEAF_VARIDNUM_RNUM: {
				float val = ch -> nodeData.leaf -> tn -> value.val_float;
				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, output_fmt_float\n");
				fprintf(fp, "sub rsp, 4\n");
				fprintf(fp, "mov dword [rsp], __float32__(%f)\n", val);
				fprintf(fp, "cvtss2sd xmm0, [rsp]\n");
				fprintf(fp, "add rsp, 4\n");
				fprintf(fp, "mov rax, 1\n");
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			case AST_LEAF_BOOLTRUE: {
				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, bool_true\n" );
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			case AST_LEAF_BOOLFALSE: {
				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, bool_false\n" );
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			default: {
				/* do nothing */
			}
			break;
		}
	}
	if(ch -> type == AST_NODE_VARIDNUM) {

		/* non array variable */
		ASTNode * idNode = ch -> child;
		SymTableVar * id = fetchVarData(curr -> localST, idNode -> nodeData.leaf -> tn -> lex);
		if(id -> dataType != AST_TYPE_ARRAY) {
			if(id -> isAssigned == 0) {
				rte();
			}
			fprintf(fp, "mov r9, %dd\n", (id -> offset) + typeSize[id -> dataType]);
			fprintf(fp, "mov rdx, rbp\n");
			outputArrayElement(id);
			return;
		}

		getLeftRightIndex(id);
		// if(lft > right) {
		// 	rte();
		// }
		astDataType type = id -> sdt.r -> dataType;

		if(idNode -> next == NULL) {
			int offset = id -> offset;
			fprintf(fp, "push rbp\n");
			fprintf(fp, "mov rdi, output_fmt_plain\n" );
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
			fprintf(fp, "mov rdx, qword [rax]\n");

			fprintf(fp, "mov rcx, r11w\n");
			fprintf(fp, "sub rcx, r10w\n");
			fprintf(fp, "inc rcx\n");

			fprintf(fp, "mov r9, %dd\n", typeSize[type]);

			fprintf(fp, "label_%d:\n", label_num++);
			int loopLabel = label_num - 1;
		
			fprintf(fp, "push rdx\n");
			fprintf(fp, "push rcx\n");

			outputArrayElement(id);
			
			fprintf(fp, "pop rcx\n");
			fprintf(fp, "pop rdx\n");

			fprintf(fp, "push rbp\n");
			fprintf(fp, "mov rdi, single_space\n" );
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "sub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "dec rcx\n");
			fprintf(fp, "jnz label_%d\n", loopLabel);
			fprintf(fp, "pop rbp\n");

			fprintf(fp, "push rbp\n");
			fprintf(fp, "mov rdi, end_line\n" );
			fprintf(fp, "call printf\n");
			fprintf(fp, "pop rbp\n");
		}
		else {
			fetchArraybyIndex(ch -> child, ch -> child -> next);
			outputArrayElement(id);
		}
	}
}

void codegenInit() {
	/*
		init data section and code section
		global main ;NOTE: In case you are linking with ld, use _start. Use main when linking with gcc
    */
		   
	fprintf(fp, ";init code and data\n");
	fprintf(fp, "section .data\n");
	fprintf(fp, "fmt_float: db \"%f\", 0\n");
	fprintf(fp, "fmt_int: db \"%hd\", 0\n");
	fprintf(fp, "fmt_string: db \"%s\", 0\n");
	fprintf(fp, "fmt_bool: db \"%c\", 0\n");
	fprintf(fp, "single_space: db \" \", 0\n");
	fprintf(fp, "end_line: db \"\", 0xA, 0\n");	

	fprintf(fp, "type_int: db \"Integer\", 0\n");
	fprintf(fp, "type_float: db \"Real Number\", 0\n");
	fprintf(fp, "type_bool: db \"Boolean\", 0\n");
	
	fprintf(fp, "op1: db \"Input: Enter an %s Value\n\", 0\n");
	fprintf(fp, "op2: db \"Input: Enter %d array elements of %s type for range %d to %d\", 0\n");

	fprintf(fp, "output_fmt_float: db \"Output: %f\n\", 0xA, 0\n");
	fprintf(fp, "output_fmt_int: db \"Output: %hd\n\", 0xA, 0\n");
	fprintf(fp, "output_fmt_string: db \"Output: %s\n\", 0xA, 0\n");
	fprintf(fp, "output_fmt_plain: db \"Output: \", 0\n"); 

	fprintf(fp, "bool_true: db \"true\", 0xA, 0\n");
	fprintf(fp, "bool_false: db \"false\", 0xA, 0\n");

	fprintf(fp, "except_fmt: db \"RUN TIME ERROR: Array index out of bounds at line %d.\n\"");
	
	fprintf(fp, "section .bss\n");
	fprintf(fp, "\tbuffer: resb 64\n");
	fprintf(fp, "\tdynamic: resw 1\n");
	fprintf(fp, "section .text\n");
	fprintf(fp, "\tglobal main\n");
	fprintf(fp, "\textern printf\n");
	fprintf(fp, "\textern scanf\n");
}

void emitCodeAST(ASTNode* curr, char* fname) {

	switch(curr -> type) {
		case AST_NODE_PROGRAM: {

			codegenInit();
            ASTNode* ch = curr -> child;
            emitCodeChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULEDECLARATION: {
			/* no need */
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.moduleList -> type == AST_MODULE_DRIVER) {
				if(ch == NULL)
					return;
				emitCodeAST(ch, "driver");
			}
			else
				emitCodeChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			char fn[30];
			strcpy(fn, ch -> nodeData.leaf -> tn -> lex);
			fprintf(fp, "\t%s:\n", fn);
			emitCodeChildren(ch, fname);
		}
		break;

		case AST_NODE_INPUTLIST: {
			/* Verify: nothing to do*/
		}
		break;

		case AST_NODE_OUTPUTLIST: {
			/* Verify: nothing to do */
		}
		break;

		case AST_NODE_ARRAY: {
			/* nothing required */
		}
		break;

		case AST_NODE_RANGEARRAYS: {
			/* nothing required */
		}
		break;

		case AST_NODE_STATEMENT: {
			ASTNode* ch = curr -> child;
			emitCodeChildren(ch, fname);
			/* Todo: if end stament of moduledef fprinf ret*/
		}
		break;

		case AST_NODE_IO: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.io -> type == AST_IO_GETVAL) {
				SymTableVar * idNode = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
				astDataType t = idNode -> dataType;
				takeInput(t, idNode);
			}
			else { // AST_IO_PRINT
				giveOutput(ch);
			}
		}
		break;

		case AST_NODE_SIMPLESTMT: {
			ASTNode* ch = curr -> child;
			emitCodeChildren(ch, fname);
		}
		break;

		case AST_NODE_ASSIGN: {
			ASTNode* ch = curr -> child;
			emitCodeChildren(ch, fname);
			ch = curr -> child;
			if(ch -> next -> type == AST_NODE_LVALARRSTMT) {
				/* Fetching Array data form Symbol Table */
				SymTableVar * id = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
				
				/* Getting index of array element being accessed */
				ASTNode * index = ch -> next -> child;

				/* Getting range limits of array: r10 left, r11 right*/
				getLeftRightIndex(id);

				/* rdx -> base, r9 -> offset of array element */
				fetchArraybyIndex(ch, index);
				
				/* Evaluating expression on RHS */
				ASTNode * rhs = ch -> next -> child -> next;

				/* Get offset of temporary variable on RHS of operator */
				int rhsOff = getExprOffset(rhs);
				astDataType type = getExprType(rhs);

				moveOffsetToOffset(-1, rhsOff, type);
			}
			else {
				/* LVALUE_ID_STMT */
				int lhsOff = getIDOffset(ch);
				int rhsOff = getExprOffset(ch -> next);
				astDataType type = ch -> nodeData.leaf -> dataType;
				moveOffsetToOffset(lhsOff, rhsOff, type);
			}
			// fprintf(fp, "add rsp, %dd\n", curr -> localST -> dynamicRecSize);
			curr -> localST -> dynamicRecSize = 0;
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode * ch = curr -> child;
			
			/* Setting up stack frame. Set the current stack pointer as the starting 
			   of the base of stack frame of the function being called, and storing 
			   current base pointer in stack */
			fprintf(fp, "; ### Setting up the stack frame ###");
			fprintf(fp, "push rbp\n");
			fprintf(fp, "mov rbp, rsp\n");

			/* Actual parameters */
			ASTNode * inParam = ch -> next;
			if(inParam -> type != AST_NODE_IDLIST)
				inParam = inParam -> next;

			int inputSize = 0;
			/* Traversing actual parameters */
			while(inParam != NULL) {
				ASTNode * idNode = inParam -> child;
				/* Fetch current ID from symbol table */
				SymTableVar * id = fetchVarData(curr -> localST, idNode -> nodeData.leaf -> tn -> lex);
				if(id -> isAssigned == 0)
					rte();
				fprintf(fp, "mov rcx, qword [rbp]\n");
				// fprintf(fp, "mov rcx, [rax]\n");
				fprintf(fp, "sub rcx, %dd\n", typeSize[id -> dataType] + id -> offset);
				inputSize += typeSize[id -> dataType];
				if(id -> dataType == AST_TYPE_INT) {
					fprintf(fp, "mov ax, word [rcx]\n");
					fprintf(fp, "push ax\n");
				}
				if(id -> dataType == AST_TYPE_REAL) {
					fprintf(fp, "mov eax, dword [rcx]\n");
					fprintf(fp, "push eax\n");
				}
				if(id -> dataType == AST_TYPE_BOOLEAN) {
					fprintf(fp, "mov al, byte [rcx]\n");
					fprintf(fp, "push al\n");
				}
				if(id -> dataType == AST_TYPE_ARRAY) {
					fprintf(fp, "mov rax, qword [rcx]\n");
					fprintf(fp, "push rax\n");
				}
				inParam = inParam -> child -> next;
			}
			ch = curr -> child;
			if(ch -> type != AST_NODE_LEAF)
				ch = ch -> next;
			SymTableFunc * fun = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			int actRecSize = fun -> actRecSize;
			fprintf(fp, "add rsp, %dd\n", actRecSize - inputSize);
			fprintf(fp, "call %s\n", ch -> nodeData.leaf -> tn -> lex);
		}
		break;

		case AST_NODE_IDLIST: {
			/* no need*/
		}
		break;

		case AST_NODE_EXPR: {
			/* no need*/
		}
		break;

		case AST_NODE_AOBEXPR: {
			ASTNode * ch = curr -> child;
			emitCodeChildren(ch, fname);
			ch = curr -> child;
			int leftOpTemp, rightOpTemp;
			leftOpTemp = getExprOffset(ch);
			rightOpTemp = getExprOffset(ch -> next -> next);
			astDataType type = getExprType(ch);
			applyOperator(leftOpTemp, rightOpTemp, ch -> next, type);
		}
		break;

		case AST_NODE_DECLARESTMT: {
			ASTNode * ch = curr -> child;
			if(ch -> next -> type == AST_NODE_ARRAY) {
				ASTNode * arr = ch -> next;
				if(arr -> nodeData.dataType -> is_static == 0)
					return;
				ASTNode * idNode = ch;
				astDataType type = arr -> nodeData.dataType -> dataType;
				while(idNode != NULL) {
					SymTableVar * id = fetchVarData(curr -> localST, idNode -> child -> nodeData.leaf -> tn -> lex); 
					fprintf(fp, "mov rax, rbp\n");
					fprintf(fp, "add rax, %dd\n", typeSize[AST_TYPE_POINTER] + id -> offset);
					fprintf(fp, "mov qword [rax], rsp\n");
					getLeftRightIndex(id);
					fprintf(fp, "cmp r10w, r11w\n");
					fprintf(fp, "jgt rte\n");
					fprintf(fp, "mov rcx, r11w\n");
					fprintf(fp, "sub rcx, r10w\n");
					fprintf(fp, "inc rcx\n");
					fprintf(fp, "label_%d\n", label_num++);
					fprintf(fp, "sub rsp, %dd\n", typeSize[type]);
					fprintf(fp, "dec rcx\n");
					fprintf(fp, "jnz label_%d\n", label_num - 1);
					idNode = idNode -> child -> next;
				}
			}
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode* ch = curr -> child;
			SymTableVar * switchVar = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			ch -> child -> next -> nodeData.caseStmt -> breakLabel = label_num++;
			int tmp = label_num - 1;
			emitCodeAST(ch -> next, fname);
			fprintf(fp, "label_%d:\n", label_num - 1);
			emitCodeAST(ch -> next -> next, fname);
			fprintf(fp, "label_%d:\n", tmp);
			/* Check: defualt will automatically be handled(statements) */
		}
		break;
		
		case AST_NODE_CASESTMT: {
			ASTNode * ch = curr -> child;
			SymTableVar * switchvar = fetchVarData(curr -> localST, curr -> localST -> dependentVar);
			fprintf(fp, "label_%d:\n", label_num - 1);
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "add rax, %dd\n", typeSize[switchvar -> dataType] + switchvar -> offset);
			if(switchvar -> dataType == AST_TYPE_INT) {
				fprintf(fp, "mov eax, word [rax]\n");
				int val = ch -> nodeData.leaf -> tn -> value.val_int;
				fprintf(fp, "cmp eax, %dd\n", val);
				fprintf(fp, "jnz label_%d\n", label_num++);
				fprintf(fp, "label_%d:\n", label_num - 2);
				emitCodeAST(ch -> next, fname);
				fprintf(fp, "jmp label_%d\n", curr -> nodeData.caseStmt -> breakLabel);
				ch = ch -> next -> next;
				if(ch != NULL) {
					ch -> nodeData.caseStmt -> breakLabel = curr -> nodeData.caseStmt -> breakLabel;
					emitCodeAST(ch, fname);
				}
			}
		}
		break;

		case AST_NODE_UNARY: {
			ASTNode* ch = curr -> child;
			int tempOff = getExprOffset(ch -> next);
			astDataType type = getExprType(ch -> next);
			SymTableFunc * par = getParentFunc(curr -> localST);
			curr -> nodeData.unary -> temporaryOffset = par -> dynamicRecSize;
			par -> dynamicRecSize += typeSize[type];
			if(type == AST_TYPE_INT) {
				fprintf(fp, "mov rax, rsp\n");
				fprintf(fp, "add rax, %dd\n", typeSize[type] + tempOff);
				fprintf(fp, "mov ax, word [rax]\n");

				if(ch -> nodeData.leaf -> type == AST_LEAF_UOPMINUS) {
					fprintf(fp, "xor ax, 0xffff\n");
					fprintf(fp, "inc ax\n");
				}

				fprintf(fp, "mov rdx, rsp\n");
				fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
				fprintf(fp, "mov word [rdx], ax\n");
			}

			else {
				fprintf(fp, "mov rax, rsp\n");
				fprintf(fp, "add rax, %dd\n", typeSize[type] + tempOff);
				
				if(ch -> nodeData.leaf -> type == AST_LEAF_UOPMINUS) {
					fprintf(fp, "finit\n");
					fprintf(fp, "fld dword [rax]\n");
					fprintf(fp, "fchs\n");
				}

				fprintf(fp, "mov rdx, rsp\n");
				fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
				fprintf(fp, "fstp word [rdx]\n");
			}
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			/* do nothing */
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode * ch = curr -> child;
			if(curr -> nodeData.iterStmt -> type == AST_ITER_FOR) {

				SymTableVar * loopVar = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
				
				int num1 = ch -> next -> child -> nodeData.leaf -> tn -> value.val_int;
				int num2 = ch -> next -> child -> next -> nodeData.leaf -> tn -> value.val_int;
				
				if(num1 > num2)
					return;
				// optimized

				fprintf(fp, "mov cx, %d\n", num1);

				fprintf(fp, "label_%d\n", label_num++);
				
				scopeBegin();
				
				int tmp = label_num - 1;
				fprintf(fp, "mov rax, rbp\n");
				fprintf(fp, "add rax, %dd\n", typeSize[AST_TYPE_INT] + loopVar -> offset);
				fprintf(fp, "mov word [rax], cx\n");

				emitCodeAST(ch -> next -> next, fname);
				scopeEnd();
				
				fprintf(fp, "mov rax, rbp\n");
				fprintf(fp, "add rax, %dd\n", typeSize[AST_TYPE_INT] + loopVar -> offset);
				fprintf(fp, "mov cx, word[rax]\n");
				fprintf(fp, "inc cx\n");
				fprintf(fp, "cmp cx, %d", num2);
				fprintf(fp, "jnz label_%d", tmp);

			}
			else {
				SymTableFunc * par = getParentFunc(curr -> localST);
				par -> dynamicRecSize = 0;

				fprintf(fp, "label_%d:\n", label_num++);
				
				scopeBegin();

				int tmp = label_num - 1;
				int last = label_num++;

				emitCodeAST(ch, fname);
				int tmpOff = par -> dynamicRecSize;
				fprintf(fp, "mov rax, rsp\n");
				fprintf(fp, "sub rax, %dd\n", tmpOff);
				fprintf(fp, "mov dl, byte [rax]\n");
				fprintf(fp, "cmp dl, 0\n");
				fprintf(fp, "jz label_\n", last);

				emitCodeAST(ch -> next);
				scopeEnd();

				fprintf(fp, "jmp label_%d\n", tmp);
				fprintf(fp, "label_%d:\n", last);

				par -> dynamicRecSize = 0;
			}
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode* ch = curr -> child;
			SymTableFunc * par = getParentFunc(curr -> localST);
			SymTableVar * id = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			if(ch -> next == NULL) {
				fprintf(fp, "mov rax, rbp\n");
				fprintf(fp, "sub rax, %dd\n", id -> offset + typeSize[id -> dataType]);
				curr -> nodeData.var -> temporaryOffset = par -> dynamicRecSize;
				par -> dynamicRecSize += typeSize[id -> dataType];
				if(id -> dataType == AST_TYPE_INT) {
					fprintf(fp, "mov dx, word [rax]\n");
					fprintf(fp, "mov rax, rsp\n");
					fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov word [rax], dx\n");
				}
				else if(id -> dataType == AST_TYPE_REAL) {
					fprintf(fp, "mov edx, dword [rax]\n");
					fprintf(fp, "mov rax, rsp\n");
					fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov dword [rax], edx\n");
				}
				else if(id -> dataType == AST_TYPE_BOOLEAN) {
					fprintf(fp, "mov dl, byte [rax]\n");
					fprintf(fp, "mov rax, rsp\n");
					fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov byte [rax], dl\n");
				}
				else if(id -> dataType == AST_TYPE_ARRAY) {
					fprintf(fp, "mov rdx, qword [rax]\n");
					fprintf(fp, "mov rax, rsp\n");
					fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov qword [rax], rdx\n");
				}
			}
		}
		break;

		case AST_NODE_LEAF: {
			/* 
				For ID: (As in ast.c)
				CASE: 3, 7, 10, 13, 16, 17, 18 
			*/
			switch(curr -> nodeData.leaf -> type) {
				case AST_LEAF_INT: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
					return;
				}
				break;
				case AST_LEAF_RNUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_REAL;
					return;	
				}
				break;
				case AST_LEAF_BOOL: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
					return;	
				}
				break;
				case AST_LEAF_ID: {
					char str[30];
					strcpy(str, curr -> nodeData.leaf -> tn -> lex);
					switch(curr -> parent -> type) {
						case AST_NODE_MODULEDECLARATION: {
							SymTableFunc * tmp = insertFuncRecord(str);
							if(tmp == NULL) {
								fprintf(stderr, "A record with the given already exists within the symbol table on line %d.", curr -> nodeData.leaf -> tn -> line_num);
							}
							return;
						}
						break;
						case AST_NODE_MODULE: {
							SymTableFunc* tmp = fetchFuncData(str);
							if(tmp != NULL && tmp -> isDeclared == 1) {
								fprintf(stderr, 
								"Redundant declaration of the function '%s' on line %d.\n", str, curr -> nodeData.leaf -> tn -> line_num);
							}
							if(tmp != NULL && tmp -> isDefined == 1) {
								fprintf(stderr, 
								"Multiple definitions for the function '%s' on line %d.\n", str,
								curr -> nodeData.leaf -> tn -> line_num);
								return;
							}
							if(tmp == NULL) {
								tmp = insertFuncRecord(str);
								tmp -> isDeclared = 0;
								tmp -> isDefined = 1;
							}
							tmp -> isDefined = 1;
							curr -> localST = tmp;
							insertplist(curr -> next, str);
							insertplist(curr -> next -> next, str);
						}
						break;
						case AST_NODE_INPUTLIST: {
							/* handled in insertinputplist();*/
						}
						break;
						case AST_NODE_OUTPUTLIST: {
							/* handled in insertoutputplist();*/
						}
						break;
						case AST_NODE_IO: {
							/* handles above*/
						}
						break;
						case AST_NODE_VARIDNUM: {
							if(curr -> prev != NULL) {
								SymTableVar* idx = fetchVarData(curr -> localST, str);
								if(idx == NULL) {
									fprintf(stderr, 
									"Index variable('%s') is not defined on line %d.\n", str,
									curr -> nodeData.leaf -> tn -> line_num);
									return;
								}
								if(idx -> dataType != AST_TYPE_INT) {
									fprintf(stderr, 
									"Index variable('%s') is not Integer on line %d.\n", str,
									curr -> nodeData.leaf -> tn -> line_num);
								}
								curr -> nodeData.leaf -> dataType = idx -> dataType;
							}
							else {
								SymTableVar* tmp = fetchVarData(curr -> localST, str);
								if(tmp == NULL) {
									// fprintf(stderr, 
									// "The identifier('%s') not declared on line %d.\n", str, 
									// curr -> nodeData.leaf -> tn -> line_num);
									return;
								}
								curr -> nodeData.leaf -> dataType = tmp -> dataType;
							}
						}
						break;
						case AST_NODE_LVALARRSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Index variable('%s') is not defined on line %d.\n", str,
									curr -> nodeData.leaf -> tn -> line_num);
								return;
							}
							if(idx -> dataType != AST_TYPE_INT) {
								fprintf(stderr, 
								"Range Arrays variable('%s') is not Integer on line %d.\n", str,
									curr -> nodeData.leaf -> tn -> line_num);
							}
						}
						break;
						case AST_NODE_ASSIGN: {
							// SymTableVar* idx = fetchVarData(curr -> localST, str);
							// if(idx == NULL) {
							// 	fprintf(stderr, 
							// 	"The variable to be assigned is not declared.\n");
								return;
							// }
							/* No need */
						}
						break;
						case AST_NODE_MODULEREUSE: {
							SymTableFunc* func = fetchFuncData(str);
							if(func == NULL) {
								fprintf(stderr, 
								"The function used('%s') is not declared and defined on line %d.\n", str, curr -> nodeData.leaf -> tn -> line_num);
								return;
							}
							if(func -> isDefined == 0) {
								func -> isDeclared++;
							}
						}
						break;
						case AST_NODE_IDLIST: {
							/* handled above in typelistmatch()*/
						}
						break;
						case AST_NODE_CONDSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Switch variable('%s') is not defined line %d.\n",
								str, curr -> nodeData.leaf -> tn -> line_num);
								return;
							}
							else {
								curr -> nodeData.leaf -> dataType = idx -> dataType;
							}
						}
						break;
						case AST_NODE_ITERSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Loop variable('%s') is not defined line %d.\n",
								str, curr -> nodeData.leaf -> tn -> line_num);
								/* not declared, still giving it a type*/
								curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
								return;
							}
							else {
								curr -> nodeData.leaf -> dataType = idx -> dataType;
							}
						}
						break;
					}
				}
				break;
				case AST_LEAF_NUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
				}
				break;
				case AST_LEAF_IDXNUM: {
					
					curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
					if(curr -> parent -> type == AST_NODE_VARIDNUM) {
						SymTableVar* arr = fetchVarData(curr -> localST, curr -> parent -> child -> nodeData.leaf -> tn -> lex);
						if(arr == NULL) {
							// fprintf(stderr, 
							// "The array variable is not defined.\n");
							return;
						}
						boundChecking(arr, curr -> parent);
					}
					return;
				}
				break;
				case AST_LEAF_IDXID: {
					char str[30];
					strcpy(str, curr -> nodeData.leaf -> tn -> lex);
					SymTableVar* idx = fetchVarData(curr -> localST, str);
					if(idx == NULL) {
						fprintf(stderr, 
						"Index variable is not defined on line %d.\n", curr -> nodeData.leaf -> tn -> line_num);
						return;
					}
					if(idx -> dataType != AST_TYPE_INT) {
						fprintf(stderr, 
						"Index variable in range arrays is not Integer on line %d.\n", curr -> nodeData.leaf -> tn -> line_num);
					}
				}
				break;
				case AST_LEAF_PLUS: {
					curr -> nodeData.leaf -> op = AST_AOP;
				}
				break;
				case AST_LEAF_MINUS: { 
					curr -> nodeData.leaf -> op = AST_AOP;
				}
				break;
				case AST_LEAF_MUL: { 
					curr -> nodeData.leaf -> op = AST_AOP;
				}
				break;
				case AST_LEAF_DIV: { 
					curr -> nodeData.leaf -> op = AST_AOP;
				}
				break;
				case AST_LEAF_OR: { 
					curr -> nodeData.leaf -> op = AST_LOP;
				}
				break;
				case AST_LEAF_AND: {
					curr -> nodeData.leaf -> op = AST_LOP;
				}
				break;
				case AST_LEAF_LT: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_LE: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_GT: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_GE: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_EQ: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_NE: {
					curr -> nodeData.leaf -> op = AST_RELOP;
				}
				break;
				case AST_LEAF_TRUE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_FALSE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_VALNUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
				}
				break;
				case AST_LEAF_VALTRUE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_VALFALSE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_VARIDNUM_NUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_INT;
				}
				break;
				case AST_LEAF_VARIDNUM_ID: {
					char str[30];
					strcpy(str, curr -> nodeData.leaf -> tn -> lex);
					SymTableVar* tmp = fetchVarData(curr -> localST, str);
					if(tmp == NULL) {
						fprintf(stderr, 
						"The identifier not declared.\n");
					}
					curr -> nodeData.leaf -> dataType = tmp -> dataType;
				}
				break;
				case AST_LEAF_VARIDNUM_RNUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_REAL;
				}
				break;
				case AST_LEAF_BOOLTRUE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_BOOLFALSE: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
				}
				break;
				case AST_LEAF_UOPPLUS: {
					/* nothing required as of now*/
				}
				break;
				case AST_LEAF_UOPMINUS: {
					/* nothing required as of now*/
				}
				break;
				default: {
					/* nothing required as of now*/
				}
			}
		}
		break;
		default: {
			fprintf(stderr, "Default error!\n");
		}
	}
}