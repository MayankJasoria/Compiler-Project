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

void asmComment(char * str) {

	fprintf(fp, "\n; ### %s ### \n", str);
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
	
	fprintf(fp, "; --- START: get left and right index of %s ---\n", id->name);
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

	fprintf(fp, "; --- END: got left and right index of %s in r10w and r11w ---\n", id->name);
}

void getInputElement() {
	fprintf(fp, "; START: --- getInputElement() ---\n");
	fprintf(fp, "push rbp\n");
	fprintf(fp, "mov rdi, fmt_int\n");
	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, r9\n");
	fprintf(fp, "mov rsi, rax\n");
	fprintf(fp, "call scanf\n");
	fprintf(fp, "pop rbp\n");
	fprintf(fp, "; --- END: getInputElement() --- \n")
}

/**
 * r9 <- offset relative to base address of array, the offset, base address rdx
 * @param arr	AST node of the array
 * @param index	AST Node specifying index
 */
void fetchArraybyIndex(ASTNode * arr, ASTNode * index) {

	fprintf(fp, "; --- START: fetchArraybyIndex() for array %s: base: rdx, offset: r9  --- \n", arr -> nodeData.leaf -> tn -> lex);

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

	fprintf(fp, "; --- END: fetchArraybyIndex() for array %s: base: rdx, offset: r9 --- \n", arr -> nodeData.leaf -> tn -> lex);
}

/**
 * NOTE: Function was initially designed to modularize arrays,
 * but later found out that this can be reused for non array types as well.
 * don't go by the name
 */
void outputArrayElement(SymTableVar * id) {
	
	fprintf(fp, "; --- START: outputArrayElement() for %s--- \n", id -> name);
	fprintf(fp, "; Function is used for both Arrays and non-Array types, don't go by the name! \n");
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

	fprintf(fp, "; --- END: outputArrayElement() for %s--- \n", id -> name);
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

	fprintf(fp, "; --- START: moveOffsetToOffset(): lhsoff = %d, rhsoff = %d, type = %s ---\n", lhsOff, rhsOff, typeName[type]);
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

	fprintf(fp, "; --- END: moveOffsetToOffset(): lhsoff = %d, rhsoff = %d, type = %s ---\n", lhsOff, rhsOff, typeName[type]);
}

void if0else1() {
	fprintf(fp, "; --- START: if0else1() --- \n");
	fprintf(fp, "mov r8b, 0\n");
	fprintf(fp, "jmp label_%d\n", label_num++);
	fprintf(fp, "label_%d:\n", label_num - 2);
	fprintf(fp, "mov r8b, 1\n");
	fprintf(fp, "label_%d\n", label_num - 1);
	fprintf(fp, "; --- END: if0else1() --- \n");
}

void pushTemporary(astDataType type) {
	fprintf(fp, "; --- START: pushTemporary(): type = %s ---\n", typeName[type]);
	if(type == AST_TYPE_INT) {
		fprintf(fp, "mov dx, word [rax]\n");
		fprintf(fp, "mov rax, rsp\n");
		fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "mov word [rax], dx\n");
	}
	else if(type == AST_TYPE_REAL) {
		fprintf(fp, "mov edx, dword [rax]\n");
		fprintf(fp, "mov rax, rsp\n");
		fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "mov dword [rax], edx\n");
	}
	else if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "mov dl, byte [rax]\n");
		fprintf(fp, "mov rax, rsp\n");
		fprintf(fp, "sub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "mov byte [rax], dl\n");
	}

	fprintf(fp, "; --- END: pushTemporary(): type = %s ---\n", typeName[type]);
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

	fprintf(fp, "; --- START: applyOperator(): leftOp: %d, rightOp: %d, operator: %s, type: %s --- \n", leftOp, rightOp, operator->nodeData.leaf->tn->lex, typeName[type], ;

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

	fprintf(fp, "; --- START: applyOperator(): leftOp: %d, rightOp: %d, operator: %s, type: %s --- \n", leftOp, rightOp, operator->nodeData.leaf->tn->lex, typeName[type], ;
}

void scopeBegin() {
	fprintf(fp, "; --- START: scopeBegin() --- \n");

	fprintf(fp, "sub rsp, 2d\n");
	fprintf(fp, "mov ax, word [dynamic]\n");
	fprintf(fp, "mov word [rsp], ax\n");
	fprintf(fp, "mov ax, 0\n");
	fprintf(fp, "mov word [dynamic], ax\n");

	fprintf(fp, "; --- END: scopeBegin() --- \n")
}

void scopeEnd() {

	fprintf(fp, "; --- START: scopeEnd() --- \n");

	fprintf(fp, "movsx rax, word [dynamic]\n");
	fprintf(fp, "add rsp, rax\n");
	fprintf(fp, "mov ax, word [rsp]\n");
	fprintf(fp, "mov word [dynamic], ax\n");
	fprintf(fp, "add rsp, 2d\n");

	fprintf(fp, "; --- END: scopeEnd() --- \n");
}

void takeInput(astDataType t, SymTableVar * idNode) {

	fprintf(fp, "; --- START: takeInput(): type: %s, Name: %s --- \n", typeName[t], idNode->name);

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

			fprintf(fp, "\n; --- Asking for user input for Array ---\n");
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
			
			fprintf(fp, "\n; --- rdx will be the address of the first element of the array ---\n");
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "sub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
			fprintf(fp, "mov rdx, qword [rax]\n");

			fprintf(fp, "\n; --- Loop for scanning each element of the array --- \n");

			fprintf(fp, "mov rcx, r11w\n");
			fprintf(fp, "sub rcx, r10w\n");
			fprintf(fp, "inc rcx\n");			

			fprintf(fp, "label_%d:\n", label_num++);
			
			fprintf(fp, "push rdx\n");
			fprintf(fp, "push rcx\n");
			fprintf(fp, "push rbp\n");
			
			fprintf(fp, "\n; --- Scanning input ---\n");
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

	fprintf(fp, "; --- END: takeInput(): type: %s, Name: %s --- \n", typeName[t], idNode->name);
}

void giveOutput(ASTNode * curr) {
	fprintf(fp, "; --- START: giveInput()");

	ASTNode * ch = curr;
	if(ch -> type == AST_NODE_LEAF) {
		fprintf(fp, " type: AST_NODE_LEAF, ");
		switch(ch -> nodeData.leaf -> type) {
			case AST_LEAF_VARIDNUM_NUM: {

				fprintf(fp, " leaf-type: AST_LEAF_VARIDNUM_NUM --- \n");

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
				fprintf(fp, " leaf-type: AST_LEAF_VARIDNUM_RNUM, value: %f --- \n", val);

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
				fprintf(fp, " leaf-type: AST_LEAF_BOOLTRUE --- \n");

				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, bool_true\n" );
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			case AST_LEAF_BOOLFALSE: {
				fprintf(fp, " leaf-type: AST_LEAF_BOOLFALSE --- \n");

				fprintf(fp, "push rbp\n");
				fprintf(fp, "mov rdi, bool_false\n" );
				fprintf(fp, "call printf\n");
				fprintf(fp, "pop rbp\n");
			}
			break;
			default: {
				fprintf(fp, " leaf-type: default case hit --- \n");
				/* do nothing */
			}
			break;
		}
	}
	if(ch -> type == AST_NODE_VARIDNUM) {
		fprintf(fp, " type: AST_NODE_LEAF, ");

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
				SymTableFunc * driver = fetchFuncData("driver");
				asmComment("Begining of the driver program.");
				fprintf(fp, "main:\n");
				
				emitCodeAST(ch, "driver");
				
				asmComment("Resetting(aligning) the rsp.");
				fprintf(fp, "movsx rax, [word] dynamic\n");
				fprintf(fp, "sub rsp, rax\n");
				fprintf(fp, "sub rsp, %dd\n", driver -> actRecSize);
				fprintf(fp, "ret\n");
				asmComment("End of driver function.");
			}
			else
				emitCodeChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			ASTNode * ret = ch -> next -> next;
			char fn[30];
			strcpy(fn, ch -> nodeData.leaf -> tn -> lex);
			SymTableFunc * func = fetchFuncData(fn);
			asmComment("Begin of a moduledef.")
			fprintf(fp, "\t%s:\n", fn);
			emitCodeChildren(ch, fname);

			asmComment("Copying back the output parameters.");
			fprintf(fp, "mov rax, qword [rbp]\n");
			while(ret != NULL) {
				ASTNode * idNode = ret -> child;
				SymTableVar * id = fetchVarData(func, idNode -> nodeData.leaf -> tn -> lex);
				fprintf(fp, "mov rdx, rbp\n");
				fprintf(fp, "sub rdx, %dd\n", typeSize[id -> dataType] + id -> offset);
				fprintf(fp, "sub rax, %dd\n", typeSize[id -> dataType] + id -> offset);
				if(id -> dataType == AST_TYPE_INT) {
					fprintf(fp, "mov cx, word [rdx]\n");
					fprintf(fp, "mov word [rax], cx\n");
				}
				if(id -> dataType == AST_TYPE_REAL) {
					fprintf(fp, "mov ecx, dword [rdx]\n");
					fprintf(fp, "mov word [rax], ecx\n");
				}
				if(id -> dataType == AST_TYPE_BOOLEAN) {
					fprintf(fp, "mov cl, byte [rdx]\n");
					fprintf(fp, "mov byte [rax], cl\n");
				}
				if(id -> dataType == AST_TYPE_ARRAY) {
					fprintf(fp, "mov rcx, qword [rdx]\n");
					fprintf(fp, "mov qword [rax], rcx\n");
				}
				fprintf(fp, "add rax, %dd\n", typeSize[id -> dataType] + id -> offset);
				ret = ret -> child -> next -> next;
			}
			fprintf(fp, "sub rbp, 8\n");
			fprintf(fp, "mov rsp, rbp\n");
			fprintf(fp, "mov rbp, rax\n");
			fprintf(fp, "ret\n");
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
			fprintf(fp, "; --- Setting up the stack frame ---");
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
		
		/* todo: complete it */
		case AST_NODE_CASESTMT: {
			ASTNode * ch = curr -> child;
			SymTableVar * switchvar = fetchVarData(curr -> localST, curr -> localST -> dependentVar);
			fprintf(fp, "label_%d:\n", label_num - 1);
			fprintf(fp, "mov rax, rbp\n");
			fprintf(fp, "add rax, %dd\n", typeSize[switchvar -> dataType] + switchvar -> offset);
			if(switchvar -> dataType == AST_TYPE_INT) {
				fprintf(fp, "mov ax, word [rax]\n");
				int val = ch -> nodeData.leaf -> tn -> value.val_int;
				fprintf(fp, "cmp ax, %dd\n", val);
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
			else if(switchvar -> dataType == AST_TYPE_BOOLEAN) {
				
				fprintf(fp, "mov aL, byte [rax]\n");
				int val = (ch -> nodeData.leaf -> tn -> sym.T == TRUE);
				fprintf(fp, "cmp al, %dd\n", val);
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
				astDataType type = id -> dataType;
				pushTemporary(type);
			}
			else {
				getLeftRightIndex(id);
				fetchArraybyIndex(ch, ch -> next);
				curr -> nodeData.var -> temporaryOffset = par -> dynamicRecSize;
				par -> dynamicRecSize += typeSize[id -> dataType];
				astDataType type = id -> sdt.r -> dataType;
				fprintf(fp, "mov rax, rdx\n");
				fprintf(fp, "sub rax, r9\n");
				pushTemporary(type);
			}
		}
		break;

		case AST_NODE_LEAF: {
			switch(curr -> nodeData.leaf -> type) {
				case AST_LEAF_VARIDNUM_NUM: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_INT];
					int val = curr -> nodeData.leaf -> tn -> value.val_int;
					fprintf(fp, "mov ax, %dd\n", val);
					fprintf(fp, "mov rdx, rsp\n");
					fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov word [rdx], ax\n");
				}
				break;
				case AST_LEAF_VARIDNUM_RNUM: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_REAL];
					float val = curr -> nodeData.leaf -> tn -> value.val_float;
					fprintf(fp, "mov rdx, rsp\n");
					fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov word [rdx], __float32__(%f)\n", val);
				}
				break;
				case AST_LEAF_BOOLTRUE: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_BOOLEAN];
					fprintf(fp, "mov al, 1d\n");
					fprintf(fp, "mov rdx, rsp\n");
					fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov byte [rdx], al\n");
				}
				break;
				case AST_LEAF_BOOLFALSE: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_BOOLEAN];
					fprintf(fp, "mov al, 0\n");
					fprintf(fp, "mov rdx, rsp\n");
					fprintf(fp, "sub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "mov byte [rdx], al\n");				}
				}
				break;
				default: {
					/* nothing required as of now */
				}
			}
		}
		break;
		default: {
			/* do nothing */
			// fprintf(stderr, "Default error!\n");
		}
	}
}