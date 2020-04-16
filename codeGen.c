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

int getExprOffset(ASTNode * expr) {
	
	if(expr -> type == AST_NODE_LEAF)
		return rhs -> nodeData.leaf -> temporaryOffset;
	else if(expr -> type == AST_NODE_VARIDNUM)
		return rhs -> nodeData.var -> temporaryOffset;
	else if(expr -> type == AST_NODE_AOBEXPR)
		return rhs -> nodeData.AOBExpr -> temporaryOffset;
	else if(expr -> type == AST_NODE_UNARY)
		return rhs -> nodeData.unary -> temporaryOffset;
}

int getExprType(ASTNode * expr) {
	
	if(expr -> type == AST_NODE_LEAF)
		return rhs -> nodeData.leaf -> dataType;
	else if(expr -> type == AST_NODE_VARIDNUM)
		return rhs -> nodeData.var -> dataType;
	else if(expr -> type == AST_NODE_AOBEXPR)
		return rhs -> nodeData.AOBExpr -> dataType;
	else if(expr -> type == AST_NODE_UNARY)
		return rhs -> nodeData.unary -> dataType;
}

/*
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

void fetchArraybyIndex(ASTNode * arr, ASTNode * index) {

	ASTNode * i = index;
	SymTableVar * id = fetchVarData(arr -> localST, arr -> nodeData.leaf -> tn -> lex);
	astDataType type = id -> sdt.r -> dataType;
	int offset = id -> offset;
	int idx;
	if(i -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		idx = i -> nodeData.leaf -> tn -> value.val_int;
		fprintf(fp, "mov r8w, idx\n");
	}
	else {
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
	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, %dd\n", offset + typeSize[AST_TYPE_POINTER]);
	fprintf(fp, "mov rdx, qword [rax]\n");

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

/* Important NOTE: Function was initially designed to modularize arrays,
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

void moveOffsetToOffset(int lhsOff, int rhsOff, astDataType type) {

	fprintf(fp, "mov rax, rbp\n");
	fprintf(fp, "sub rax, %dd\n", rhsOff + typeSize[type]);
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
			fprintf(fp, "mov r9, %dd\n", (id -> offset) + typeSize[id -> dataType];
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
			emitCodeChildren(ch);
			ch = curr -> child;
			if(ch -> next -> type == AST_NODE_LVALARRSTMT) {
				SymTableVar * id = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
				ASTNode * index = ch -> next -> child;
				getLeftRightIndex(id);
				fetchArraybyIndex(ch, index);
				ASTNode * rhs = ch -> next -> child -> next;
				int rhsOff = getExprOffset(rhs);
				astDataType type = getExprType(rhs);
				moveOffsetToOffset(-1, rhsOff, type)
			}
			else {
				int lhsOff = getIDOffset(ch);
				int rhsOff = getExprOffset(ch -> next);
				astDataType type = ch -> nodeData.leaf -> dataType;
				moveOffsetToOffset(lhsOff, rhsOff, type);
			}
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode * ch = curr -> child;
			
			fprintf(fp, "push rbp\n");
			fprintf(fp, "mov rbp, rsp\n");

			ASTNode * inParam = ch -> next;
			if(inParam -> type != AST_NODE_IDLIST)
				inParam = inParam -> next;

			int inputSize = 0;
			while(inParam != NULL) {
				ASTNode * idNode = inParam -> child;
				SymTableVar * id = fetchVarData(curr -> localST, idNode -> nodeData.leaf -> tn -> lex);
				if(id -> isAssigned == 0)
					rte();
				fprintf(fp, "mov rax, qword [rbp]\n");
				fprintf(fp, "mov rcx, [rax]\n");
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
			emitCodeChildren(ch);
			ch = curr -> child;
			
		}
		break;

		case AST_NODE_DECLARESTMT: {
			ASTNode* ch = curr -> child;
			ch -> next -> localST = curr -> localST;
			emitCodeAST(ch -> next, fname);
			ASTNode* tmp = ch;
			while(tmp != NULL) {

				ASTNode* idNode = tmp -> child;

				if(ch -> next -> type == AST_NODE_ARRAY) {

					ASTNode* lft = (ch -> next) -> child -> child;
					ASTNode* right = lft -> next; 
					astDataType t = (ch -> next) -> child -> next -> nodeData.leaf -> dataType;
					addArrToFunction(curr -> localST, fname, idNode -> nodeData.leaf -> tn -> lex, lft, right, t);
				}
				else {
					addDataToFunction(curr -> localST, fname, idNode -> nodeData.leaf -> tn -> lex, ch -> next -> nodeData.leaf -> dataType, idNode -> nodeData.leaf -> tn -> line_num);
				}
				tmp = tmp -> child;
				tmp = tmp -> next;
			}
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);
			if((ch -> nodeData).leaf -> dataType == AST_TYPE_REAL) {
				fprintf(stderr, 
				"Switch variable('%s') is of real type on line %d.\n", ch -> nodeData.leaf -> tn -> lex,
					ch -> nodeData.leaf -> tn -> line_num);
			}
			SymTableFunc* newST = getFuncTable(fname, curr -> localST);
			ASTNode* ch1 = ch -> next;
			ch1 -> localST = newST;
			ch1 -> nodeData.dataType = ch -> nodeData.dataType;
			strcpy(ch1 -> nodeData.caseStmt -> switchVar, ch -> nodeData.leaf -> tn -> lex);
			emitCodeAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			if(ch -> nodeData.leaf -> dataType == AST_TYPE_BOOLEAN) {
				if(curr -> nodeData.condStmt -> def == 1) {
					fprintf(stderr, 
					"Default case in bool type switch statement on line %d.\n", curr -> nodeData.condStmt -> def_line_num);
				}
				if(ch2 == NULL)
					return;
				ch2 -> localST = newST;
				emitCodeAST(ch2, fname);
			}
			else if(ch -> nodeData.leaf -> dataType == AST_TYPE_INT) {
				if(curr -> nodeData.condStmt -> def == 0) {
					fprintf(stderr, 
					"Default case not present in int type switch statement line %d.\n", curr -> nodeData.condStmt -> end_line_num);
				}
				else {
					if(ch2 == NULL) {
						return;
					}
					ch2 -> localST = newST;
					// ch2 -> nodeData.statement -> type = ch -> nodeData.leaf -> dataType;
					emitCodeAST(ch2, fname);
				}
			}
			else {
				fprintf(stderr, 
				"Switch variable not of feasible type on line %d.\n", ch -> nodeData.leaf -> tn -> line_num);
				if(ch2 == NULL)
					return;
				ch2 -> localST = newST;
				emitCodeAST(ch2, fname);
			}
		}
		break;
		
		case AST_NODE_CASESTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);

			ch = ch -> next;
			if(ch == NULL)
				return;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);

			ch = ch -> next;
			if(ch == NULL) {
				return;
			}

			ch -> localST = curr -> localST;
			ch -> nodeData.dataType = curr -> nodeData.dataType;
			strcpy(ch -> nodeData.caseStmt -> switchVar, curr -> nodeData.caseStmt -> switchVar);
			emitCodeAST(ch, fname);
		}
		break;

		case AST_NODE_UNARY: {
			ASTNode* ch = curr -> child;
			ch = ch -> next;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);
			if(ch -> type == AST_NODE_LEAF)
				curr -> nodeData.unary -> dataType = ch -> nodeData.leaf ->dataType;
			if(ch -> type == AST_NODE_AOBEXPR)
				curr -> nodeData.unary -> dataType = ch -> nodeData.AOBExpr ->dataType;
			if(ch -> type == AST_NODE_VARIDNUM)
				curr -> nodeData.unary -> dataType = ch -> nodeData.var ->dataType;
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			ASTNode* ch = curr -> child;
			SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			SymTableVar* par = fetchVarData(curr -> localST, curr -> parent -> child -> nodeData.leaf -> tn -> lex);
			if(par == NULL) {
				// fprintf(stderr, 
				// "Lvalue The variable taken as input is not being declared.\n");
				/* already been taken care of */
			}
			else if(par -> dataType != AST_TYPE_ARRAY) {
				fprintf(stderr, 
				"A non array type variable('%s') access using whichId on line %d\n", par -> name,
					ch -> nodeData.leaf -> tn -> line_num);
			}
			else if(ch -> next != NULL) {
				boundChecking(par, curr -> parent);
			}
			ch = ch -> next;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);
			ch = curr -> child -> next;
			curr -> nodeData.lvalueARRStmt -> dataType = ch -> nodeData.AOBExpr -> dataType;
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			emitCodeAST(ch, fname);
			ch = curr -> child;
			if(ch -> nodeData.leaf -> dataType != AST_TYPE_INT) {
				fprintf(stderr, 
				"For loop variable('%s') is not of int type on line %d.\n",
				ch -> nodeData.leaf -> tn -> lex,
				ch -> nodeData.leaf -> tn -> line_num);
				return;
			}

			SymTableFunc* newST = getFuncTable(fname, curr -> localST);
			ASTNode* ch1 = ch -> next;
			if(ch1 == NULL) {
				return;
			}
			ch1 -> localST = newST;
			emitCodeAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			if(ch2 == NULL) {
				return;
			}
			ch2 -> localST = newST;
			emitCodeAST(ch2, fname);
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode* ch = curr -> child;
			emitCodeChildren(ch, fname);
			ch = curr -> child;
			SymTableVar * idNode = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			if(idNode == NULL) {
				fprintf(stderr, 
				"VarIdNum id('%s') not declared before %d\n", ch -> nodeData.leaf -> tn -> lex, ch -> nodeData.leaf -> tn -> line_num);
				return;
			}
			curr -> nodeData.var -> dataType = idNode -> dataType;
			if(curr -> nodeData.var -> dataType == AST_TYPE_ARRAY && ch-> next == NULL && curr -> parent -> type != AST_NODE_ASSIGN) {
				fprintf(stderr, 
				"Array variable('%s') used without index on line %d.\n",
				idNode -> name, ch -> nodeData.leaf -> tn -> line_num);
				return;
			}
			if(curr -> nodeData.var -> dataType != AST_TYPE_ARRAY && ch-> next != NULL) {
				fprintf(stderr, 
				"Non Array variable('%s') used with index line %d.\n", 
				idNode -> name,
				ch -> nodeData.leaf -> tn -> line_num);
			}
			if(ch -> next != NULL) {
				curr -> nodeData.var -> dataType = idNode -> sdt.r -> dataType;
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