/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures/st.h"
#include "data_structures/ast.h"
#include "codeGen.h"
#include "codeGenDef.h"

// void rte(/* char* errorMsg */) {
	
// 	fprintf(fp, "; --- START: rte() --- \n");
// 	/**
// 	 * TODO: Print error message
// 	 * RUN TIME ERROR:  Array index out of bound
// 	 */ 
// 	fprintf(fp, "\tmov ebx, 0	 ;return 0 status on exit - 'No errors'\n");
// 	fprintf(fp, "\tmov eax, 1	 ;invoke SYS_EXIT system call (kernel opcode 1)\n");
// 	fprintf(fp, "\tint 80h		 ;generate interrupt\n");

// 	fprintf(fp, "; --- END: rte() --- \n");
// }

void emitCodeInit(const char* fname) {
    /* Open fname */
    fp = fopen(fname, "w");
}

void pushRegs() {
	fprintf(fp, "\tpush rsi\n");
	fprintf(fp, "\tpush rdx\n");
	fprintf(fp, "\tpush rcx\n");
	fprintf(fp, "\tpush r8\n");
	fprintf(fp, "\tpush r9\n");
	fprintf(fp, "\tpush rax\n");
}

void popRegs() {
	fprintf(fp, "\tpop rax\n");
	fprintf(fp, "\tpop r9\n");
	fprintf(fp, "\tpop r8\n");
	fprintf(fp, "\tpop rcx\n");
	fprintf(fp, "\tpop rdx\n");
	fprintf(fp, "\tpop rsi\n");
}

void alignStack() {

	pushRegs();
	fprintf(fp, "; --- START: ALIGN STACK---\n");
	fprintf(fp, "\tmov qword [rspreserve], rsp\n");
	fprintf(fp, "\tand rsp, 0xfffffffffffffff0\n");
	fprintf(fp, "\tsub rsp, 10000B\n");
	fprintf(fp, "; --- END: ALIGN STACK ---\n");
}

void getBackStack() {

	fprintf(fp, "\tmov rsp, qword [rspreserve]\n");
	popRegs();
}

void emitCodeFinalize() {

	fprintf(fp, "rte:\n");
	fprintf(fp, "\tmov ebx, 0	 ;return 0 status on exit - 'No errors'\n");
	fprintf(fp, "\tmov eax, 1	 ;invoke SYS_EXIT system call (kernel opcode 1)\n");
	fprintf(fp, "\tint 80h		 ;generate interrupt\n");
	fprintf(fp, "\noob:\n");
	fprintf(fp, "\tpush rbp\n");
	fprintf(fp, "\tmov rdi, rte_oob\n");
	alignStack();
	fprintf(fp, "\tcall printf\n");
	getBackStack();
	fprintf(fp, "\tpop rbp\n");
	fprintf(fp, "\tjmp rte\n");
	if (fp) {
		fclose(fp);
		fp = NULL;
	}
}

void emitCodeChildren(ASTNode * head, char * fname) {
	
    ASTNode* ch = head;
    while(ch != NULL) {
        emitCodeAST(ch, fname);
        ch = ch -> next;
    }
}

void asmComment(char * str) {

	fprintf(fp, "\n; ### %s ### \n", str);
}

int getLastCaseLabel(ASTNode * curr) {

	ASTNode * tmp = curr -> child -> next;
	while(tmp -> child -> next -> next != NULL) {
		tmp = tmp -> child -> next -> next;
	}
	return tmp -> nodeData.caseStmt -> lastLabel;
}

// void rte(char * str, int line_num) {

// 	fprintf(fp, "\tpush rbp\n");
// 	fprintf(fp, "\tmov rdi, %s\n", str);
// 	fprintf(fp, "\tmov si, %dd\n", line_num);
// 	alignStack();
// 	fprintf(fp, "\tcall printf\n");
// 	getBackStack();
// 	fprintf(fp, "\tpop rbp\n");
// 	fprintf(fp, "\tjmp rte\n");
// }

int getIDOffset(ASTNode * idNode) {
	SymTableVar * tmp = fetchVarData(idNode -> parent -> localST, idNode -> nodeData.leaf -> tn -> lex);
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
	
	SymTableFunc * local = id -> table;
	SymTableFunc * func = getParentFunc(local);
	if(id -> offset < func -> inputSize) {
		int offset = id -> offset;
		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER] + typeSize[AST_TYPE_INT]);
		fprintf(fp, "\tmov r10w, word [rax]\n");

		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER] + 2*typeSize[AST_TYPE_INT]);
		fprintf(fp, "\tmov r11w, word [rax]\n");
		return;
	}

	fprintf(fp, "; --- START: get left and right index of %s ---\n", id->name);
	int lft, right;
	if(strcmp(id -> sdt.r -> lowId, "") == 0) {
		lft = id -> sdt.r -> low;
		fprintf(fp, "\tmov r10w, %dd\n", lft);		
	}
	else {
		SymTableVar * l = fetchVarData(id -> table, id -> sdt.r -> lowId);
		// if(l -> isAssigned == 0) {
		// 	rte();
		// }
		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_INT] + l -> offset);
		fprintf(fp, "\tmov r10w, word[rax]\n");
	}
	if(strcmp(id -> sdt.r -> highId, "") == 0) { 
		right = id -> sdt.r -> high;
		fprintf(fp, "\tmov r11w, %dd\n", right);	
	}
	else {
		SymTableVar * r = fetchVarData(id -> table, id -> sdt.r -> highId);
		// if(r -> isAssigned == 0) {
		// 	rte();
		// }
		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_INT] + r -> offset);
		fprintf(fp, "\tmov r11w, word[rax]\n");
	}

	fprintf(fp, "; --- END: got left and right index of %s in r10w and r11w --- \n", id->name);
}

void getInputElement(astDataType t) {
	fprintf(fp, "; START: --- getInputElement() ---\n");
	
	fprintf(fp, "\tpush rbp\n");
	if(t == AST_TYPE_INT) 
		fprintf(fp, "\tmov rdi, fmt_int\n");
	else if(t == AST_TYPE_REAL)
		fprintf(fp, "\tmov rdi, fmt_float\n");
	else if(t == AST_TYPE_BOOLEAN)
		fprintf(fp, "\tmov rdi, fmt_bool\n");
	fprintf(fp, "\tmov rax, rbp\n");
	fprintf(fp, "\tsub rax, r9\n");
	fprintf(fp, "\tmov rsi, rax\n");
	alignStack();
	fprintf(fp, "\tcall scanf\n");
	getBackStack();
	fprintf(fp, "\tpop rbp\n");
	fprintf(fp, "; --- END: getInputElement() --- \n");
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
	SymTableVar * id = fetchVarData(arr -> parent -> localST, arr -> nodeData.leaf -> tn -> lex);
	
	/* DataType of elements of array */
	astDataType type = id -> sdt.r -> dataType;
	int offset = id -> offset;
	int idx;
	
	/* store the value of the index in r8w */
	if(i -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		/* index is of type NUM */
		idx = i -> nodeData.leaf -> tn -> value.val_int;
		fprintf(fp, "\tmov r8w, %dd\n", idx);
	}
	else {
		/* index is of type ID */
		SymTableVar * tmp = fetchVarData(arr -> parent -> localST, i -> nodeData.leaf -> tn -> lex);
		// if(tmp -> isAssigned == 0) {
		// 	rte();
		// }
		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_INT] + tmp -> offset);
		fprintf(fp, "\tmov r8w, word [rax]\n");
	}

	fprintf(fp, "\tmov rsi, %dd\n", i -> nodeData.leaf -> tn -> line_num);
	fprintf(fp, "\tcmp r8w, r10w\n");
	fprintf(fp, "\tjl oob\n");
	fprintf(fp, "\tcmp r8w, r11w\n");
	fprintf(fp, "\tjg oob\n");

	/* TODO: write this in assembly */
	// if(idx < lft || idx > right) {
	// 	rte();
	// }
	/* Move base address of array to r8x */
	fprintf(fp, "\tmov rax, rbp\n");
	fprintf(fp, "\tsub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
	fprintf(fp, "\tmov rdx, qword [rax]\n");

	/* compute element address as: [rdx - (r8w - r10w + 1) * width] */
	fprintf(fp, "\tmov r9w, 0\n");
	fprintf(fp, "\tsub r8w, r10w\n");
	fprintf(fp, "\tinc r8w\n");
	fprintf(fp, "\tmov rcx, %dd\n", typeSize[type]);
	fprintf(fp, "label_%d:\n", label_num++);
	fprintf(fp, "\tadd r9w, r8w\n");		
	fprintf(fp, "\tdec rcx\n");
	fprintf(fp, "\tjnz label_%d\n", label_num - 1);
	fprintf(fp, "\tmovsx r9, r9w\n");

	fprintf(fp, "; --- END: fetchArraybyIndex() for array %s: base: rdx, offset: r9 --- \n", arr -> nodeData.leaf -> tn -> lex);
}

/**
 * NOTE: Function was initially designed to modularize arrays,
 * but later found out that this can be reused for non array types as well.
 * don't go by the name
 */
void outputArrayElement(SymTableVar * id, int op) {
	
	fprintf(fp, "; --- START: outputArrayElement() for %s --- \n", id -> name);
	fprintf(fp, "; Function is used for both Arrays and non-Array types, don't go by the name! \n");
	astDataType type = id -> dataType;
	if(type == AST_TYPE_ARRAY)
		type = id -> sdt.r -> dataType;

	fprintf(fp, "\tpush rbp\n");
	if(type == AST_TYPE_INT) {
		if(op == 1)
			fprintf(fp, "\tmov rdi, fmt_int\n");
		else
			fprintf(fp, "\tmov rdi, output_fmt_int\n");
		fprintf(fp, "\tmov rax, rdx\n");
		fprintf(fp, "\tsub rax, r9\n");
		fprintf(fp, "\tmov si, word[rax]\n");
	}
	else if(type == AST_TYPE_REAL) {
		if(op == 1)
			fprintf(fp, "\tmov rdi, fmt_float\n");
		else
			fprintf(fp, "\tmov rdi, output_fmt_float\n");
		fprintf(fp, "\tmov rax, rdx\n");
		fprintf(fp, "\tsub rax, r9\n");
		fprintf(fp, "\tcvtss2sd xmm0, dword[rax]\n");
		fprintf(fp, "\tmov rax, 1\n");
	}
	else if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "\tmov rax, rdx\n");
		fprintf(fp, "\tsub rax, r9\n");
		fprintf(fp, "\tmov al, byte[rax]\n");
		fprintf(fp, "\tcmp al, 0\n");
		fprintf(fp, "\tjz label_%d\n", label_num++);
		if(op == 1)
			fprintf(fp, "\tmov rdi, fmt_string\n");
		else
			fprintf(fp, "\tmov rdi, output_fmt_string\n");
		fprintf(fp, "\tmov rsi, bool_true\n");
		fprintf(fp, "\tjmp label_%d\n", label_num++);
		fprintf(fp, "label_%d:\n", label_num - 2);
		if(op == 1)
			fprintf(fp, "\tmov rdi, fmt_string\n");	
		else
			fprintf(fp, "\tmov rdi, output_fmt_string\n");
		fprintf(fp, "\tmov rsi, bool_false\n");
		fprintf(fp, "label_%d:\n", label_num - 1);
	}
	alignStack();
	fprintf(fp, "\tcall printf\n");
	getBackStack();
	fprintf(fp, "\tpop rbp\n");

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
	fprintf(fp, "\tmov rax, rsp\n");
	fprintf(fp, "\tsub rax, %dd\n", rhsOff + typeSize[type]);
	
	/*  */
	if(type == AST_TYPE_INT) {
		fprintf(fp, "\tmov r8w, word [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "\tmov rax, rdx\n");
			fprintf(fp, "\tsub rax, r9\n");
		}
		else {
			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "\tmov word [rax], r8w\n");
	}
	if(type == AST_TYPE_REAL) {
		fprintf(fp, "\tmov r8d, dword [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "\tmov rax, rdx\n");
			fprintf(fp, "\tsub rax, r9\n");
		}
		else {
			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "\tmov dword [rax], r8d\n");
	}
	if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "\tmov r8b, byte [rax]\n");
		if(lhsOff == -1) {
			fprintf(fp, "\tmov rax, rdx\n");
			fprintf(fp, "\tsub rax, r9\n");
		}
		else {
			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + lhsOff);
		}
		fprintf(fp, "\tmov byte [rax], r8b\n");
	}
	if(type == AST_TYPE_ARRAY) {
		fprintf(fp, "\tmov r8, qword [rax]\n");
		fprintf(fp, "\tmov rax, rbp\n");
		fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + lhsOff);
		fprintf(fp, "\tmov qword [rax], r8\n");
	}

	fprintf(fp, "; --- END: moveOffsetToOffset(): lhsoff = %d, rhsoff = %d, type = %s ---\n", lhsOff, rhsOff, typeName[type]);
}

void if0else1() {
	fprintf(fp, "; --- START: if0else1() --- \n");
	fprintf(fp, "\tmov r8b, 0\n");
	fprintf(fp, "\tjmp label_%d\n", label_num++);
	fprintf(fp, "label_%d:\n", label_num - 2);
	fprintf(fp, "\tmov r8b, 1\n");
	fprintf(fp, "label_%d:\n", label_num - 1);
	fprintf(fp, "; --- END: if0else1() --- \n");
}

void pushTemporary(astDataType type, SymTableFunc* par) {
	fprintf(fp, "; --- START: pushTemporary(): type = %s ---\n", typeName[type]);
	if(type == AST_TYPE_INT) {
		fprintf(fp, "\tmov dx, word [rax]\n");
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov word [rax], dx\n");
	}
	else if(type == AST_TYPE_REAL) {
		fprintf(fp, "\tmov edx, dword [rax]\n");
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov dword [rax], edx\n");
	}
	else if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "\tmov dl, byte [rax]\n");
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov byte [rax], dl\n");
	}
	else if(type == AST_TYPE_ARRAY) {
		fprintf(fp, "\tmov rdx, qword [rax]\n");
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov qword [rax], rdx\n");
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

	fprintf(fp, "; --- START: applyOperator(): leftOp: %d, rightOp: %d, operator: %s, type: %s --- \n", leftOp, rightOp, operator->nodeData.leaf->tn->lex, typeName[type]);

	fprintf(fp, "\tmov rax, rsp\n");
	fprintf(fp, "\tsub rax, %dd\n", leftOp + typeSize[type]);
	fprintf(fp, "\tmov r10, rsp\n");
	fprintf(fp, "\tsub r10, %dd\n", rightOp + typeSize[type]);
	
	SymTableFunc * par = getParentFunc(operator -> parent -> localST);
	operator -> parent -> nodeData.AOBExpr -> temporaryOffset = par -> dynamicRecSize;
	par -> dynamicRecSize += typeSize[operator -> parent -> nodeData.AOBExpr -> dataType];

	if(type == AST_TYPE_INT) {
		fprintf(fp, "\tmov r8w, word [rax]\n");
		fprintf(fp, "\tmov r9w, word [r10]\n");
	}
	if(type == AST_TYPE_REAL) {
		fprintf(fp, "\tfinit\n");
		if(operator -> parent -> nodeData.AOBExpr -> dataType == AST_TYPE_BOOLEAN) {
			fprintf(fp, "\tfld dword [r10]\n");
			fprintf(fp, "\tfld dword [rax]\n");
		}
		else {
			fprintf(fp, "\tfld dword [rax]\n");
			fprintf(fp, "\tfld dword [r10]\n");
		}
	}
	if(type == AST_TYPE_BOOLEAN) {
		fprintf(fp, "\tmov r8b, byte [rax]\n");
		fprintf(fp, "\tmov r9b, byte [r10]\n");
	}
	switch(operator -> nodeData.leaf -> type) {
		case AST_LEAF_AND:
			fprintf(fp, "\tand r8b, r9b\n");
			break;
		case AST_LEAF_OR:
			fprintf(fp, "\tor r8b, r9b\n");
			break;
		case AST_LEAF_LT:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tjl label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0000000100000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_LE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tjle label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0000000100000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num++);
				fprintf(fp, "\tcmp eax, 0100000000000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_GT:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tjg label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0000000000000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_GE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tjge label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0000000000000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num++);
				fprintf(fp, "\tcmp eax, 0100000000000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num - 1);
				if0else1();
			}
			break;
		case AST_LEAF_EQ: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tje label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0100000000000000B\n");
				fprintf(fp, "\tje label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_NE: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tcmp r8w, r9w\n");
				fprintf(fp, "\tjne label_%d\n", label_num++);				
				if0else1();
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfcom st0, st1\n");
				fprintf(fp, "\tfstsw ax\n");
				fprintf(fp, "\tand eax, 0100011100000000B\n");
				fprintf(fp, "\tcmp eax, 0100000000000000B\n");
				fprintf(fp, "\tjne label_%d\n", label_num++);
				if0else1();
			}
			break;
		case AST_LEAF_PLUS: 
			if(type == AST_TYPE_INT) 
				fprintf(fp, "\tadd r8w, r9w\n");
		
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfadd\n");
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
				// fprintf(fp, "\tsub rsp, 4\n");
				fprintf(fp, "\tfstp dword [rax]\n");
			}
			break;
		case AST_LEAF_MINUS: 
			if(type == AST_TYPE_INT) 
				fprintf(fp, "\tsub r8w, r9w\n");
		
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfsub\n");
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
				// fprintf(fp, "\tsub rsp, 4\n");
				fprintf(fp, "\tfstp dword [rax]\n");
			}
			break;
		case AST_LEAF_MUL: 
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tmov ax, r8w\n");
				fprintf(fp, "\tmul r9w\n");
				fprintf(fp, "\tmov r8w, ax\n");
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfmul\n");
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
				// fprintf(fp, "\tsub rsp, 4\n");
				fprintf(fp, "\tfstp dword [rax]\n");
			}
			break;
		case AST_LEAF_DIV:
			if(type == AST_TYPE_INT) {
				fprintf(fp, "\tmov dx, 0\n");
				fprintf(fp, "\tmov ax, r8w\n");
				fprintf(fp, "\tcmp r9w, 0\n");
				fprintf(fp, "\tjz rte\n");
				fprintf(fp, "\tdiv r9w\n");
				fprintf(fp, "\tmov r8w, ax\n");
			}
			if(type == AST_TYPE_REAL) {
				fprintf(fp, "\tfdiv\n");
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
				// fprintf(fp, "\tsub rsp, 4\n");
				fprintf(fp, "\tfstp dword [rax]\n");
			}
			break;
		default:
			break;
	}
	
	if(operator -> parent -> nodeData.AOBExpr -> dataType == AST_TYPE_INT) {
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov word [rax], r8w\n");
	}
	else if(operator -> parent -> nodeData.AOBExpr -> dataType == AST_TYPE_BOOLEAN) {
		fprintf(fp, "\tmov rax, rsp\n");
		fprintf(fp, "\tsub rax, %dd\n", par -> dynamicRecSize);
		fprintf(fp, "\tmov byte [rax], r8b\n");
	}

	fprintf(fp, "; --- START: applyOperator(): leftOp: %d, rightOp: %d, operator: %s, type: %s --- \n", leftOp, rightOp, operator->nodeData.leaf->tn->lex, typeName[type]);
}

void scopeBegin() {
	fprintf(fp, "; --- START: scopeBegin() --- \n");

	fprintf(fp, "\tsub rsp, 2d\n");
	fprintf(fp, "\tmov ax, word [dynamic]\n");
	fprintf(fp, "\tmov word [rsp], ax\n");
	fprintf(fp, "\tmov ax, 0\n");
	fprintf(fp, "\tmov word [dynamic], ax\n");

	fprintf(fp, "; --- END: scopeBegin() --- \n");
}

void scopeEnd() {

	fprintf(fp, "; --- START: scopeEnd() --- \n");

	fprintf(fp, "\tmovsx rax, word [dynamic]\n");
	fprintf(fp, "\tadd rsp, rax\n");
	fprintf(fp, "\tmov ax, word [rsp]\n");
	fprintf(fp, "\tmov word [dynamic], ax\n");
	fprintf(fp, "\tadd rsp, 2d\n");

	fprintf(fp, "; --- END: scopeEnd() --- \n");
}

void takeInput(astDataType t, SymTableVar * idNode) {

	fprintf(fp, "; --- START: takeInput(): type: %s, Name: %s --- \n", typeName[t], idNode->name);

	fprintf(fp, "\tpush rbp\n");
	int offset = idNode -> offset;
	// unsigned long long int addr =  
	switch(t) {
		case AST_TYPE_INT: {
			fprintf(fp, "\tmov rdi, op1\n");
			fprintf(fp, "\tmov rsi, type_int\n");
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");

			fprintf(fp, "\tmov r9, %dd\n", offset + typeSize[t]);
			getInputElement(t);
		}
		break;
		case AST_TYPE_REAL: {
			fprintf(fp, "\tmov rdi, op1\n");
			fprintf(fp, "\tmov rsi, type_float\n");
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");

			fprintf(fp, "\tmov r9, %dd\n", offset + typeSize[t]);
			getInputElement(t);
		}
		break;
		case AST_TYPE_BOOLEAN: {
			fprintf(fp, "\tmov rdi, op1\n");
			fprintf(fp, "\tmov rsi, type_bool\n");
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");

			fprintf(fp, "\tmov r9, %dd\n", offset + typeSize[t]);
			getInputElement(t);
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
			fprintf(fp, "\tmov rdi, op2\n");
			fprintf(fp, "\tmov si, r11w\n");
			fprintf(fp, "\tsub si, r10w\n");
			fprintf(fp, "\tmovsx rsi, si\n");
			fprintf(fp, "\tinc rsi\n");
			if(type == AST_TYPE_INT)
				fprintf(fp, "\tmov rdx, type_int\n");
			else if(type == AST_TYPE_REAL)
				fprintf(fp, "\tmov rdx, type_float\n");
			else if(type == AST_TYPE_BOOLEAN)
				fprintf(fp, "\tmov rdx, type_bool\n");
			fprintf(fp, "\tmovsx rcx, r10w\n");
			fprintf(fp, "\tmovsx r8, r11w\n");
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");
			
			fprintf(fp, "\n; --- rdx will be the address of the first element of the array ---\n");
			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
			fprintf(fp, "\tmov rdx, qword [rax]\n");

			fprintf(fp, "\n; --- Loop for scanning each element of the array --- \n");

			getLeftRightIndex(idNode);
			fprintf(fp, "\tmov cx, r11w\n");
			fprintf(fp, "\tsub cx, r10w\n");
			fprintf(fp, "\tmovsx rcx, cx\n");
			fprintf(fp, "\tinc rcx\n");			

			fprintf(fp, "label_%d:\n", label_num++);
			
			fprintf(fp, "\tpush rdx\n");
			fprintf(fp, "\tpush rcx\n");
			fprintf(fp, "\tpush rbp\n");
			
			fprintf(fp, "\n; --- Scanning input ---\n");
			if(type == AST_TYPE_INT) 
				fprintf(fp, "\tmov rdi, fmt_int\n");
			else if(type == AST_TYPE_REAL) 
				fprintf(fp, "\tmov rdi, fmt_float\n");
			else if(type == AST_TYPE_BOOLEAN) 
				fprintf(fp, "\tmov rdi, fmt_bool\n");

			fprintf(fp, "\tsub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "\tmov rsi, rdx\n");
			alignStack();
			fprintf(fp, "\tcall scanf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");
			fprintf(fp, "\tpop rcx\n");
			fprintf(fp, "\tpop rdx\n");
			fprintf(fp, "\tsub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "\tdec rcx\n");
			fprintf(fp, "\tcmp rcx, 0x0\n");
			fprintf(fp, "\tjnz label_%d\n", label_num - 1);
			// fprintf(fp, "\tpop rbp\n");
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
				fprintf(fp, "\tpush rbp\n");
				fprintf(fp, "\tmov rdi, output_fmt_int\n");
				fprintf(fp, "\tmov rsi, %d\n", val);
				alignStack();
				fprintf(fp, "\tcall printf\n");
				getBackStack();
				fprintf(fp, "\tpop rbp\n");
			}
			break;
			case AST_LEAF_VARIDNUM_RNUM: {
				float val = ch -> nodeData.leaf -> tn -> value.val_float;
				fprintf(fp, " leaf-type: AST_LEAF_VARIDNUM_RNUM, value: %f --- \n", val);

				fprintf(fp, "\tpush rbp\n");
				fprintf(fp, "\tmov rdi, output_fmt_float\n");
				fprintf(fp, "\tsub rsp, 4\n");
				fprintf(fp, "\tmov dword [rsp], __float32__(%f)\n", val);
				fprintf(fp, "\tcvtss2sd xmm0, [rsp]\n");
				fprintf(fp, "\tadd rsp, 4\n");
				fprintf(fp, "\tmov rax, 1\n");
				alignStack();
				fprintf(fp, "\tcall printf\n");
				getBackStack();
				fprintf(fp, "\tpop rbp\n");
			}
			break;
			case AST_LEAF_BOOLTRUE: {
				fprintf(fp, " leaf-type: AST_LEAF_BOOLTRUE --- \n");

				fprintf(fp, "\tpush rbp\n");
				fprintf(fp, "\tmov rdi, output_fmt_string\n");
				fprintf(fp, "\tmov rsi, bool_true\n");
				alignStack();
				fprintf(fp, "\tcall printf\n");
				getBackStack();
				fprintf(fp, "\tpop rbp\n");
			}
			break;
			case AST_LEAF_BOOLFALSE: {
				fprintf(fp, " leaf-type: AST_LEAF_BOOLFALSE --- \n");

				fprintf(fp, "\tpush rbp\n");
				fprintf(fp, "\tmov rdi, output_fmt_string\n");
				fprintf(fp, "\tmov rsi, bool_false\n");
				alignStack();
				fprintf(fp, "\tcall printf\n");
				getBackStack();
				fprintf(fp, "\tpop rbp\n");
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
		fprintf(fp, " type: AST_NODE_VARIDNUM --- \n");

		/* non array variable */
		ASTNode * idNode = ch -> child;
		SymTableVar * id = fetchVarData(curr -> localST, idNode -> nodeData.leaf -> tn -> lex);
		if(id -> dataType != AST_TYPE_ARRAY) {
			// if(id -> isAssigned == 0) {
			// 	rte();
			// }
			fprintf(fp, "\tmov r9, %dd\n", (id -> offset) + typeSize[id -> dataType]);
			fprintf(fp, "\tmov rdx, rbp\n");
			outputArrayElement(id, 0);
			return;
		}

		getLeftRightIndex(id);
		// if(lft > right) {
		// 	rte();
		// }
		astDataType type = id -> sdt.r -> dataType;

		if(idNode -> next == NULL) {
			fprintf(fp, "; --- idNode->next is NULL --- \n");
			int offset = id -> offset;
			fprintf(fp, "\tpush rbp\n");
			fprintf(fp, "\tmov rdi, output_fmt_plain\n" );
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");

			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
			fprintf(fp, "\tmov rdx, qword [rax]\n");

			fprintf(fp, "\tmov cx, r11w\n");
			fprintf(fp, "\tsub cx, r10w\n");
			fprintf(fp, "\tmovsx rcx, cx\n");
			fprintf(fp, "\tinc rcx\n");

			fprintf(fp, "\tmov r9, %dd\n", typeSize[type]);

			fprintf(fp, "label_%d:\n", label_num++);
			int loopLabel = label_num - 1;
		
			fprintf(fp, "\tpush rdx\n");
			fprintf(fp, "\tpush rcx\n");

			outputArrayElement(id, 1);
			
			fprintf(fp, "\tpop rcx\n");
			fprintf(fp, "\tpop rdx\n");

			fprintf(fp, "\tpush rdx\n");
			fprintf(fp, "\tpush rcx\n");
			fprintf(fp, "\tpush rbp\n");
			fprintf(fp, "\tmov rdi, single_space\n" );
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");
			fprintf(fp, "\tpop rcx\n");
			fprintf(fp, "\tpop rdx\n");

			fprintf(fp, "\tsub rdx, %dd\n", typeSize[type]);
			fprintf(fp, "\tdec rcx\n");
			fprintf(fp, "\tjnz label_%d\n", loopLabel);
			// fprintf(fp, "\tpop rbp\n");

			fprintf(fp, "\tpush rbp\n");
			fprintf(fp, "\tmov rdi, end_line\n" );
			alignStack();
			fprintf(fp, "\tcall printf\n");
			getBackStack();
			fprintf(fp, "\tpop rbp\n");
		}
		else {
			fprintf(fp, "; --- idNode->next is not NULL --- \n");
			fetchArraybyIndex(ch -> child, ch -> child -> next);
			outputArrayElement(id, 0);
		}
	}

	fprintf(fp, "; --- END: giveInput() --- \n");

}

void codegenInit() {
	/*
		init data section and code section
		global main ;NOTE: In case you are linking with ld, use _start. Use main when linking with gcc
    */
		   
	fprintf(fp, "; --- START: init code and data --- \n");
	fprintf(fp, "section .data\n");
	fprintf(fp, "\tfmt_float: db \"%%f\", 0\n");
	fprintf(fp, "\tfmt_int: db \"%%hd\", 0\n");
	fprintf(fp, "\tfmt_string: db \"%%s\", 0\n");
	fprintf(fp, "\tfmt_bool: db \"%%hhu\", 0\n");
	fprintf(fp, "\tsingle_space: db \" \", 0\n");
	fprintf(fp, "\tend_line: db \"\", 0xA, 0\n");	

	fprintf(fp, "\ttype_int: db \"Integer\", 0\n");
	fprintf(fp, "\ttype_float: db \"Real Number\", 0\n");
	fprintf(fp, "\ttype_bool: db \"Boolean\", 0\n");
	
	fprintf(fp, "\top1: db \"Input: Enter an %%s Value\", 0xA, 0\n");
	fprintf(fp, "\top2: db \"Input: Enter %%d array elements of %%s type for range %%d to %%d\", 0xA, 0\n");

	fprintf(fp, "\toutput_fmt_float: db \"Output: %%f\", 0xA, 0\n");
	fprintf(fp, "\toutput_fmt_int: db \"Output: %%hd\", 0xA, 0\n");
	fprintf(fp, "\toutput_fmt_string: db \"Output: %%s\", 0xA, 0\n");
	fprintf(fp, "\toutput_fmt_plain: db \"Output: \", 0\n"); 

	fprintf(fp, "\tbool_true: db \"true\", 0\n");
	fprintf(fp, "\tbool_false: db \"false\", 0\n");

	fprintf(fp, "\trte_oob: db \"RUN TIME ERROR: Array index out of bounds at line %%hd.\", 0xA, 0\n");

	fprintf(fp, "section .bss\n");
	fprintf(fp, "\tbuffer: resb 64\n");
	fprintf(fp, "\tdynamic: resw 1\n");
	fprintf(fp, "\trspreserve: resq 1\n");
	fprintf(fp, "section .text\n");
	fprintf(fp, "\tglobal main\n");
	fprintf(fp, "\textern printf\n");
	fprintf(fp, "\textern scanf\n");
	fprintf(fp, "; --- END: init code and data --- \n");
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
				fprintf(fp, "mov rbp, rsp\n");

				int actRecSize = driver -> actRecSize;
				fprintf(fp, "\tsub rsp, %dd\n", actRecSize);
				fprintf(fp, "\tmov word [dynamic], 0\n");
				
				emitCodeAST(ch, "driver");
				
				asmComment("Resetting(aligning) the rsp.");
				fprintf(fp, "\tmovsx rax, word [dynamic]\n");
				fprintf(fp, "\tadd rsp, rax\n");
				fprintf(fp, "\tadd rsp, %dd\n", driver -> actRecSize);
				// rte();
				fprintf(fp, "\tret\n");
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
			asmComment("Begin of a moduledef.");
			fprintf(fp, "%s:\n", fn);
			fprintf(fp, "mov word [dynamic], 0\n");
			emitCodeChildren(ch, fname);

			// asmComment("Copying back the output parameters.");
			// fprintf(fp, "\tmov rax, qword [rbp]\n");
			// while(ret != NULL) {
			// 	ASTNode * idNode = ret -> child;
			// 	SymTableVar * id = fetchVarData(func, idNode -> nodeData.leaf -> tn -> lex);
			// 	fprintf(fp, "\tmov rdx, rbp\n");
			// 	fprintf(fp, "\tsub rdx, %dd\n", typeSize[id -> dataType] + id -> offset);
			// 	fprintf(fp, "\tsub rax, %dd\n", typeSize[id -> dataType] + id -> offset);
			// 	if(id -> dataType == AST_TYPE_INT) {
			// 		fprintf(fp, "\tmov cx, word [rdx]\n");
			// 		fprintf(fp, "\tmov word [rax], cx\n");
			// 	}
			// 	if(id -> dataType == AST_TYPE_REAL) {
			// 		fprintf(fp, "\tmov ecx, dword [rdx]\n");
			// 		fprintf(fp, "\tmov word [rax], ecx\n");
			// 	}
			// 	if(id -> dataType == AST_TYPE_BOOLEAN) {
			// 		fprintf(fp, "\tmov cl, byte [rdx]\n");
			// 		fprintf(fp, "\tmov byte [rax], cl\n");
			// 	}
			// 	if(id -> dataType == AST_TYPE_ARRAY) {
			// 		fprintf(fp, "\tmov rcx, qword [rdx]\n");
			// 		fprintf(fp, "\tmov qword [rax], rcx\n");
			// 	}
			// 	fprintf(fp, "\tsub rax, %dd\n", typeSize[id -> dataType] + id -> offset);
			// 	ret = ret -> child -> next -> next;
			// }
			fprintf(fp, "\tmovsx rax, word [dynamic]\n");
			fprintf(fp, "\tadd rsp, rax\n");
			fprintf(fp, "\tret\n");
			// fprintf(fp, "\tsub rbp, 8\n");
			// fprintf(fp, "\tmov rsp, rbp\n");
			// fprintf(fp, "\tmov rbp, rax\n");
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
				SymTableVar * tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
				astDataType type = tmp -> dataType;
				moveOffsetToOffset(lhsOff, rhsOff, type);
			}
			// fprintf(fp, "\tadd rsp, %dd\n", curr -> localST -> dynamicRecSize);
			curr -> localST -> dynamicRecSize = 0;
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode * ch = curr -> child;
			
			/* Setting up stack frame. Set the current stack pointer as the starting 
			   of the base of stack frame of the function being called, and storing 
			   current base pointer in stack */
			fprintf(fp, "; --- Setting up the stack frame ---\n");
			fprintf(fp, "\tsub rsp, 2\n");
			fprintf(fp, "\tmov ax, word [dynamic]\n");
			fprintf(fp, "\tmov word [rsp], ax\n");
			fprintf(fp, "\tsub rsp, 8\n");
			fprintf(fp, "\tmov qword [rsp], rbp\n");
			
			// fprintf(fp, "\tpush rbp\n");
			fprintf(fp, "\tmov rbp, rsp\n");

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
				// if(id -> isAssigned == 0)
				// 	rte();
				fprintf(fp, "\tmov rcx, qword [rbp]\n");
				// fprintf(fp, "\tmov rcx, [rax]\n");
				fprintf(fp, "\tsub rcx, %dd\n", typeSize[id -> dataType] + id -> offset);
				inputSize += typeSize[id -> dataType];
				if(id -> dataType == AST_TYPE_ARRAY)
					inputSize += 2*typeSize[AST_TYPE_INT];

				fprintf(fp, "\tsub rsp, %dd\n", typeSize[id -> dataType]);
				if(id -> dataType == AST_TYPE_INT) {
					fprintf(fp, "\tmov ax, word [rcx]\n");
					// fprintf(fp, "\tpush ax\n");
					fprintf(fp, "\tmov word [rsp], ax\n");
				}
				if(id -> dataType == AST_TYPE_REAL) {
					fprintf(fp, "\tmov eax, dword [rcx]\n");
					// fprintf(fp, "\tpush eax\n");
					fprintf(fp, "\tmov dword [rsp], eax\n");
				}
				if(id -> dataType == AST_TYPE_BOOLEAN) {
					fprintf(fp, "\tmov al, byte [rcx]\n");
					// fprintf(fp, "\tpush al\n");
					fprintf(fp, "\tmov byte [rsp], al\n");
				}
				if(id -> dataType == AST_TYPE_ARRAY) {
					fprintf(fp, "\tmov r9, rbp\n");
					fprintf(fp, "\tmov rbp, qword [rbp]\n");
					getLeftRightIndex(id);
					fprintf(fp, "\tmov rbp, r9\n");
					fprintf(fp, "\tmov rax, qword [rcx]\n");
					// fprintf(fp, "\tpush rax\n");
					fprintf(fp, "\tmov qword [rsp], rax\n");
					fprintf(fp, "\tsub rsp, %dd\n", typeSize[AST_TYPE_INT]);
					fprintf(fp, "\tmov word[rsp], r10w\n");
					fprintf(fp, "\tsub rsp, %dd\n", typeSize[AST_TYPE_INT]);
					fprintf(fp, "\tmov word[rsp], r11w\n");
				}
				inParam = inParam -> child -> next;
			}
			ch = curr -> child;
			if(ch -> type != AST_NODE_LEAF)
				ch = ch -> next;
			SymTableFunc * fun = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			int actRecSize = fun -> actRecSize;
			fprintf(fp, "\tsub rsp, %dd\n", actRecSize - inputSize);
			fprintf(fp, "\tcall %s\n", ch -> nodeData.leaf -> tn -> lex);

			/* Function has returned here after */

			fprintf(fp, "\tmov rax, qword [rbp]\n");
			fprintf(fp, "\tadd rbp, 8d\n");
			fprintf(fp, "\tmov dx, word [rbp]\n");
			fprintf(fp, "\tmov word [dynamic], dx\n");
			fprintf(fp, "\tadd rbp, 2d\n");
			fprintf(fp, "\tmov rsp, rbp\n");
			fprintf(fp, "\tmov rbp, rax\n");

			ASTNode * ret = curr -> child;
			if(ret -> type == AST_NODE_LEAF) 
				return;
			while(ret != NULL) {

				ASTNode * idNode = ret -> child;
				SymTableVar * id = fetchVarData(curr -> localST, idNode -> nodeData.leaf -> tn -> lex);
				fprintf(fp, "\tmov rdx, rbp\n");
				fprintf(fp, "\tsub rdx, %dd\n", typeSize[id -> dataType] + id -> offset);
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, 8\n");
				fprintf(fp, "\tsub rax, 2\n");
				fprintf(fp, "\tsub rax, %dd\n", inputSize + typeSize[id -> dataType]);

				if(id -> dataType == AST_TYPE_INT) {
					fprintf(fp, "\tmov cx, word [rax]\n");
					fprintf(fp, "\tmov word [rdx], cx\n");
				}
				if(id -> dataType == AST_TYPE_REAL) {
					fprintf(fp, "\tmov ecx, dword [rax]\n");
					fprintf(fp, "\tmov word [rdx], ecx\n");
				}
				if(id -> dataType == AST_TYPE_BOOLEAN) {
					fprintf(fp, "\tmov cl, byte [rax]\n");
					fprintf(fp, "\tmov byte [rdx], cl\n");
				}
				if(id -> dataType == AST_TYPE_ARRAY) {
					fprintf(fp, "\tmov rcx, qword [rax]\n");
					fprintf(fp, "\tmov qword [rdx], rcx\n");
				}
				inputSize += typeSize[id -> dataType];
				ret = ret -> child -> next;
			}
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
				ASTNode * idNode = ch;
				ASTNode * arr = ch -> next;
				astDataType type = arr -> nodeData.dataType -> dataType;
				if(arr -> nodeData.dataType -> is_static == 1) {
					while(idNode != NULL) {
						SymTableVar * id = fetchVarData(curr -> localST, idNode -> child -> nodeData.leaf -> tn -> lex);
						fprintf(fp, "\tmov rax, rbp\n");
						fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_POINTER] + id -> offset);
						fprintf(fp, "\tmov rcx, rax\n");
						fprintf(fp, "\tmov qword[rcx], rax\n");
						idNode = idNode -> child -> next;
					}
					return;
				}

				while(idNode != NULL) {
					SymTableVar * id = fetchVarData(curr -> localST, idNode -> child -> nodeData.leaf -> tn -> lex); 
					fprintf(fp, "\tmov rax, rbp\n");
					fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_POINTER] + id -> offset);
					fprintf(fp, "\tmov qword [rax], rsp\n");
					getLeftRightIndex(id);
					fprintf(fp, "\tcmp r10w, r11w\n");
					fprintf(fp, "\tjg rte\n");
					fprintf(fp, "\tmov cx, r11w\n");
					fprintf(fp, "\tsub cx, r10w\n");
					fprintf(fp, "\tmovsx rcx, cx\n");
					fprintf(fp, "\tinc rcx\n");
					fprintf(fp, "\tmov r9w, word [dynamic]\n");
					fprintf(fp, "label_%d:\n", label_num++);
					fprintf(fp, "\tsub rsp, %dd\n", typeSize[type]);
					fprintf(fp, "\tadd r9w, %dd\n", typeSize[type]);
					fprintf(fp, "\tdec rcx\n");
					fprintf(fp, "\tjnz label_%d\n", label_num - 1);
					fprintf(fp, "\tmov word [dynamic], r9w\n");
					idNode = idNode -> child -> next;
				}
			}
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode* ch = curr -> child;
			SymTableVar * switchVar = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			ch -> next -> nodeData.caseStmt -> breakLabel = label_num++;
			int tmp = label_num - 1;
			scopeBegin();

			emitCodeAST(ch -> next, fname);
			int label = getLastCaseLabel(curr);
			if(tmp != label)
				fprintf(fp, "label_%d:\n", label);
			if(ch -> next -> next != NULL)
				emitCodeAST(ch -> next -> next, fname);
			
			fprintf(fp, "label_%d:\n", tmp);
			scopeEnd();
			/* Check: defualt will automatically be handled(statements) */
		}
		break;
		
		/* todo: complete it */
		case AST_NODE_CASESTMT: {
			ASTNode * ch = curr -> child;
			SymTableVar * switchvar = fetchVarData(curr -> localST, curr -> localST -> dependentVar);
			
			if(curr -> parent -> type == AST_NODE_CASESTMT)
				fprintf(fp, "label_%d:\n", curr -> nodeData.caseStmt -> label);
			fprintf(fp, "\tmov rax, rbp\n");
			fprintf(fp, "\tsub rax, %dd\n", typeSize[switchvar -> dataType] + switchvar -> offset);
			if(switchvar -> dataType == AST_TYPE_INT) {
				fprintf(fp, "\tmov ax, word [rax]\n");
				int val = ch -> nodeData.leaf -> tn -> value.val_int;
				fprintf(fp, "\tcmp ax, %dd\n", val);
				fprintf(fp, "\tjnz label_%d\n", label_num++);
				int nextcase = label_num - 1;
				// fprintf(fp, "label_%d:\n", label_num - 2);
				
				emitCodeAST(ch -> next, fname);
				
				fprintf(fp, "\tjmp label_%d\n", curr -> nodeData.caseStmt -> breakLabel);
				ASTNode * chtmp = ch;
				ch = ch -> next -> next;
				if(ch != NULL) {
					ch -> nodeData.caseStmt -> breakLabel = curr -> nodeData.caseStmt -> breakLabel;
					ch -> nodeData.caseStmt -> label = nextcase;
					emitCodeAST(ch, fname);
				}
				else {
					chtmp -> parent -> nodeData.caseStmt -> lastLabel = nextcase;
				}
			}
			else if(switchvar -> dataType == AST_TYPE_BOOLEAN) {
				
				fprintf(fp, "\tmov al, byte [rax]\n");
				int val = (ch -> nodeData.leaf -> tn -> sym.T == TRUE);
				fprintf(fp, "\tcmp al, %dd\n", val);
				fprintf(fp, "\tjnz label_%d\n", label_num++);
				int nextcase = label_num - 1;
				// fprintf(fp, "label_%d:\n", label_num - 2);
				
				emitCodeAST(ch -> next, fname);
				
				fprintf(fp, "jmp label_%d\n", curr -> nodeData.caseStmt -> breakLabel);
				ASTNode * chtmp = ch;
				ch = ch -> next -> next;
				if(ch != NULL) {
					ch -> nodeData.caseStmt -> breakLabel = curr -> nodeData.caseStmt -> breakLabel;
					ch -> nodeData.caseStmt -> label = nextcase;
					emitCodeAST(ch, fname);
				}
				else {
					chtmp -> parent -> nodeData.caseStmt -> lastLabel = nextcase;
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
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + tempOff);
				fprintf(fp, "\tmov ax, word [rax]\n");

				if(ch -> nodeData.leaf -> type == AST_LEAF_UOPMINUS) {
					fprintf(fp, "\txor ax, 0xffff\n");
					fprintf(fp, "\tinc ax\n");
				}

				fprintf(fp, "\tmov rdx, rsp\n");
				fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
				fprintf(fp, "\tmov word [rdx], ax\n");
			}

			else {
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", typeSize[type] + tempOff);
				
				if(ch -> nodeData.leaf -> type == AST_LEAF_UOPMINUS) {
					fprintf(fp, "\tfinit\n");
					fprintf(fp, "\tfld dword [rax]\n");
					fprintf(fp, "\tfchs\n");
				}

				fprintf(fp, "\tmov rdx, rsp\n");
				fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
				fprintf(fp, "\tfstp word [rdx]\n");
			}
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			/* do nothing */
			ASTNode * ch = curr -> child;
			emitCodeChildren(ch, fname);
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

				fprintf(fp, "\tmov cx, %dd\n", num1);

				fprintf(fp, "label_%d:\n", label_num++);
				
				scopeBegin();
				
				int tmp = label_num - 1;
				fprintf(fp, "\tmov rax, rbp\n");
				fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_INT] + loopVar -> offset);
				fprintf(fp, "\tmov word [rax], cx\n");

				emitCodeAST(ch -> next -> next, fname);
				scopeEnd();
				
				fprintf(fp, "\tmov rax, rbp\n");
				fprintf(fp, "\tsub rax, %dd\n", typeSize[AST_TYPE_INT] + loopVar -> offset);
				fprintf(fp, "\tmov cx, word[rax]\n");
				fprintf(fp, "\tinc cx\n");
				fprintf(fp, "\tcmp cx, %d\n", num2 + 1);
				fprintf(fp, "\tjnz label_%d\n", tmp);

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
				fprintf(fp, "\tmov rax, rsp\n");
				fprintf(fp, "\tsub rax, %dd\n", tmpOff);
				fprintf(fp, "\tmov dl, byte [rax]\n");
				fprintf(fp, "\tcmp dl, 0\n");
				fprintf(fp, "\tjz label_%d\n", last);

				emitCodeAST(ch -> next, fname);
				scopeEnd();

				fprintf(fp, "\tjmp label_%d\n", tmp);
				fprintf(fp, "label_%d:\n", last);
				scopeEnd();

				par -> dynamicRecSize = 0;
			}
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode* ch = curr -> child;
			SymTableFunc * par = getParentFunc(curr -> localST);
			SymTableVar * id = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			if(ch -> next == NULL) {
				fprintf(fp, "\tmov rax, rbp\n");
				fprintf(fp, "\tsub rax, %dd\n", id -> offset + typeSize[id -> dataType]);
				curr -> nodeData.var -> temporaryOffset = par -> dynamicRecSize;
				par -> dynamicRecSize += typeSize[id -> dataType];
				astDataType type = id -> dataType;
				pushTemporary(type, par);
			}
			else {
				getLeftRightIndex(id);
				fetchArraybyIndex(ch, ch -> next);
				curr -> nodeData.var -> temporaryOffset = par -> dynamicRecSize;
				par -> dynamicRecSize += typeSize[id -> sdt.r -> dataType];
				astDataType type = id -> sdt.r -> dataType;
				fprintf(fp, "\tmov rax, rdx\n");
				fprintf(fp, "\tsub rax, r9\n");
				pushTemporary(type, par);
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
					fprintf(fp, "\tmov ax, %dd\n", val);
					fprintf(fp, "\tmov rdx, rsp\n");
					fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "\tmov word [rdx], ax\n");
				}
				break;
				case AST_LEAF_VARIDNUM_RNUM: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_REAL];
					float val = curr -> nodeData.leaf -> tn -> value.val_float;
					fprintf(fp, "\tmov rdx, rsp\n");
					fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "\tmov dword [rdx], __float32__(%f)\n", val);
				}
				break;
				case AST_LEAF_BOOLTRUE: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_BOOLEAN];
					fprintf(fp, "\tmov al, 1d\n");
					fprintf(fp, "\tmov rdx, rsp\n");
					fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "\tmov byte [rdx], al\n");
				}
				break;
				case AST_LEAF_BOOLFALSE: {
					SymTableFunc * par = getParentFunc(curr -> localST);
					curr -> nodeData.leaf -> temporaryOffset = par -> dynamicRecSize;
					par -> dynamicRecSize += typeSize[AST_TYPE_BOOLEAN];
					fprintf(fp, "\tmov al, 0\n");
					fprintf(fp, "\tmov rdx, rsp\n");
					fprintf(fp, "\tsub rdx, %dd\n", par -> dynamicRecSize);
					fprintf(fp, "\tmov byte [rdx], al\n");				
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