#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "st.h"
#include "ast.h"
#include "pass1.h"

/*
void addParamToFunction(SymTableFunc* funcData, int paramType, char* varName, astDataType varDataType)
void addArrParamToFunction(SymTableFunc * funcData, int paramType, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType)
*/

/* names of types required while error reporting */
char typeName[][20] = {"Integer", "Real", "Boolean", "Array", "Pointer"};

void insertplist(ASTNode * curr, char * str) {
	
	int paramType;
	if(curr == NULL)
		return;
	if(curr -> type == AST_NODE_INPUTLIST)
		paramType = 0;
	else if(curr -> type == AST_NODE_OUTPUTLIST)
		paramType = 1; 
	else
		return;

	while(curr != NULL) {
		ASTNode * idNode = curr -> child;
		ASTNode * typeNode = idNode -> next;
		traverseAST(typeNode, str);
		SymTableFunc * func = fetchFuncData(str);
		char* varName = idNode -> nodeData.leaf -> tn -> lex;
		if(typeNode -> type == AST_NODE_ARRAY) {
			addArrParamToFunction(func, paramType, varName, 
				typeNode -> child -> child, typeNode -> child -> child -> next, 
				(typeNode -> child -> next) -> nodeData.leaf -> dataType);
		}
		else {
			addParamToFunction(func, paramType, varName, 
				typeNode -> nodeData.leaf -> dataType);
		}
		curr = curr -> child -> next -> next;
	}

}

void traverseChildren(ASTNode * head, char * fname) {
	
	ASTNode* ch = head;
	while(ch != NULL) {
		ch -> localST = ch -> parent -> localST;
		traverseAST(ch, fname);
		ch = ch -> next;
	}
}

void boundChecking(SymTableVar * tmp, ASTNode * curr) {
	astNodeType t = curr -> type;
	ASTNode* ch = curr -> child;
	if(strcmp(tmp -> sdt.r -> lowId, "") == 0 && strcmp(tmp -> sdt.r -> highId, "") == 0) {

		if(t == AST_NODE_IO) {
			if(ch -> next -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
				if((ch -> next -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) ||
					(ch -> next -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high)) {
					fprintf(stderr, 
					"Static bound checking failed on line number %d\n", ch -> next -> nodeData.leaf -> tn -> line_num);	
						curr -> nodeData.io -> b = BOUND_ERROR;
				}
				else 
					curr -> nodeData.io -> b = BOUND_CORRECT;
			}
			else 
				curr -> nodeData.io -> b = BOUND_RUNTIME;
		}

		if(t == AST_NODE_VARIDNUM) {
			if(ch -> next -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
				if((ch -> next -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) ||
					(ch -> next -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high)) {
					fprintf(stderr, 
					"Static bound checking failed on line number %d\n", ch -> next -> nodeData.leaf -> tn -> line_num);	
						curr -> nodeData.var -> b = BOUND_ERROR;
				}
				else 
					curr -> nodeData.var -> b = BOUND_CORRECT;
			}
			else 
				curr -> nodeData.var -> b = BOUND_RUNTIME;
		}

		if(t == AST_NODE_ASSIGN) {
			if(ch -> next -> child -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
				if((ch -> next -> child -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) ||
					(ch -> next -> child -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high)) {
					fprintf(stderr, 
					"Static bound checking failed on line number %d\n", ch -> next -> child -> nodeData.leaf -> tn -> line_num);	
						curr -> nodeData.assign -> b = BOUND_ERROR;
				}
				else 
					curr -> nodeData.assign -> b = BOUND_CORRECT;
			}
			else 
				curr -> nodeData.assign -> b = BOUND_RUNTIME;
		}
	}
}

/*
typedef struct node {
	void* data;
	struct node* next;
	struct node* prev;
} Node;
*/
//head: plist Node, node: AST
int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST) {
	/* check if head or node is NULL */
	if (head == NULL) {
		fprintf(stderr, "Assigning a value from a function which does not return a value\n");
		return 0;
	}

	SymTableVar * tmp = (SymTableVar*) (head -> data);
	if(node -> type == AST_NODE_LEAF)
		node = NULL;
	while(head != NULL && node != NULL) {
		tmp = (SymTableVar*) (head -> data);
		SymTableVar* curr = fetchVarData(localST, node -> child -> nodeData.leaf -> tn -> lex);
		if(curr == NULL) {
			fprintf(stderr, 
			"The parameter %s is not declared.\n", node -> child -> nodeData.leaf -> tn -> lex);
			return 0;
		}
		if(tmp -> dataType != curr -> dataType)
			return 0;
		if(tmp -> dataType == AST_TYPE_ARRAY) {

			if(tmp -> sdt.r -> dataType != curr -> sdt.r -> dataType)
				return 0;

			if(strcmp(tmp -> sdt.r -> lowId, "") == 0 && strcmp(curr -> sdt.r -> lowId, "") == 0 && (tmp -> sdt.r -> low != curr -> sdt.r -> low))
				return 0;

			if(strcmp(tmp -> sdt.r -> highId, "") == 0 && strcmp(curr -> sdt.r -> highId, "") == 0 && (tmp -> sdt.r -> high != curr -> sdt.r -> high))
				return 0;
				// {
				// if(strcmp(curr -> sdt.r -> lowId, "") == 0 && strcmp(curr -> sdt.r -> highId, "") == 0) {
				// 	if(tmp -> sdt.r -> low != curr -> sdt.r -> low)
				// 		return 0;
				// 	if(tmp -> sdt.r -> high != curr -> sdt.r -> high)
				// 		return 0;	
				// }
			// }
		}
		node = node -> child -> next;
		head = head -> next;
	}
	if(head == NULL && node == NULL)
		return 1;
	return -1;
}

void traverseAST(ASTNode* curr, char* fname) {

	switch(curr -> type) {
		case AST_NODE_PROGRAM: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULEDECLARATION: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.moduleList -> type == AST_MODULE_DRIVER) {
				SymTableFunc * tmp = insertFuncRecord("driver");
				if(tmp == NULL) {
					fprintf(stderr, "Multiple driver functions.");
					return;
				}
				if(ch == NULL)
					return;
				ch -> localST = tmp;
				tmp -> start_line_num = curr -> nodeData.moduleList -> start_line_num;
				tmp -> end_line_num = curr -> nodeData.moduleList -> end_line_num;
				traverseAST(ch, "driver");
			}
			else
				traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			SymTableFunc* tmp;
			char name[30];
			while(ch != NULL) {
				if(ch -> prev == NULL) {
					ch -> localST = curr -> localST;
					traverseAST(ch, fname);
					tmp = ch -> localST;
					if(tmp == NULL)
						return;
					tmp -> start_line_num = curr -> nodeData.module -> start_line_num;
					tmp -> end_line_num = curr -> nodeData.module -> end_line_num;
					/* Report topmost error; ignore nested errors*/
					strcpy(name, ch -> nodeData.leaf -> tn -> lex);
				}
				else {
					ch -> localST = tmp;
					traverseAST(ch, name);
				}                
				ch = ch -> next;
			}
		}
		break;

		case AST_NODE_INPUTLIST: {
			/* Verify: nothing to do*/
		}
		break;

		case AST_NODE_OUTPUTLIST: {
			/* Verify: nothing to do*/
		}
		break;

		case AST_NODE_ARRAY: {
			/**
			* TODO: replace dataNode->type with:
			*  dataNode->type_cat = AST_TYPE_CAT_PRIM / AST_TYPE_CAT_ARRAY
			*/
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			curr -> nodeData.dataType -> is_static = ch -> nodeData.rangeArrays -> is_static;
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			curr -> nodeData.dataType -> dataType = ch -> nodeData.leaf -> dataType;
		}
		break;

		case AST_NODE_RANGEARRAYS: {
			ASTNode* ch1 = curr -> child;  //lower range
			ch1 -> localST = curr -> localST;

			/* Traversing important to validate index types allowed*/
			traverseAST(ch1, fname);
			/* Note whle debugging: ch->next changed to curr -> next -> child*/
			ASTNode* ch2 = curr -> child -> next; //upper range
			ch2 -> localST = curr -> localST;
			/* Traversing important to validate index types allowed*/
			traverseAST(ch2, fname);
			
			if(ch1 -> nodeData.leaf -> type == AST_LEAF_IDXNUM && ch2 -> nodeData.leaf -> type == AST_LEAF_IDXNUM)
				curr -> nodeData.rangeArrays -> is_static = 1; // [num ... num]
			else if(ch1 -> nodeData.leaf -> type == AST_LEAF_NUM && ch2 -> nodeData.leaf -> type == AST_LEAF_NUM)
				curr -> nodeData.rangeArrays -> is_static = 1; // [num ... num]
			else
				curr -> nodeData.rangeArrays -> is_static = 0; // [id ... id] || [id ... num] || [num ... id]
		}
		break;

		case AST_NODE_STATEMENT: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_IO: {
			ASTNode* ch = curr -> child;	
			ch -> localST = curr -> localST;		
			if(curr -> nodeData.io -> type == AST_IO_GETVAL) {
				SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex); //Args: Symbol Table, Name
				if(tmp == NULL) {
					fprintf(stderr, 
					"The variable taken as input is not being declared line %d.\n", ch -> nodeData.leaf -> tn -> line_num);
				}
				else {
					tmp -> isAssigned = 1;
				}
			}
			else { // AST_IO_PRINT
				if(ch -> type == AST_NODE_VARIDNUM) {
					SymTableVar* tmp = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex); //Args: Symbol Table, Name
					if(tmp == NULL) {
						fprintf(stderr, 
						"The variable to be output is not declared line %d.\n", ch -> child -> nodeData.leaf -> tn -> line_num);
					}
					else if(ch -> child -> next != NULL && tmp -> dataType != AST_TYPE_ARRAY) {   //int a; a[4];  --> error
						fprintf(stderr, 
						"A non array type variable access using whichId on line %d\n", ch -> child -> nodeData.leaf -> tn -> line_num);
					}
					else if(ch -> child ->next != NULL) {
						boundChecking(tmp, curr -> child);
					}
				} 
			}
		}
		break;

		case AST_NODE_SIMPLESTMT: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_ASSIGN: {
			ASTNode* ch = curr -> child;
			SymTableVar* tmp = fetchVarData(curr->localST, ch -> nodeData.leaf -> tn -> lex);
			if(tmp == NULL) {
				fprintf(stderr, 
				"The lhs of the Assignment statement %s on line %d is not defined.\n",
				ch -> nodeData.leaf -> tn -> lex,
				ch -> nodeData.leaf -> tn -> line_num);
			}

			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			if(tmp == NULL)
				return;
			ch = curr -> child -> next;
			if(ch -> type == AST_NODE_LVALARRSTMT) {
				if(tmp -> dataType == AST_TYPE_ARRAY){
					if(ch -> child -> next -> type == AST_NODE_VARIDNUM) {
						if(tmp -> sdt.r -> dataType != ch -> child -> next -> nodeData.var -> dataType) {
							fprintf(stderr, 
							"Type mismatch1 in assignment statement on line %d.\n",
							ch -> child -> next -> child -> nodeData.leaf -> tn -> line_num);
						}
					}
					else {
						astDataType t;
						if(ch -> child -> next -> type == AST_NODE_LEAF)
							t = ch -> child -> next -> nodeData.leaf -> dataType;
						if(ch -> child -> next -> type == AST_NODE_AOBEXPR)
							t = ch -> child -> next -> nodeData.AOBExpr -> dataType;
						if(ch -> child -> next -> type == AST_NODE_UNARY)
							t = ch -> child -> next -> nodeData.unary -> dataType;	
						if(tmp -> sdt.r -> dataType != t) { 
							fprintf(stderr, 
							"Type mismatch2 in assignment statement on line %d.\n",
							curr -> child -> nodeData.leaf -> tn -> line_num);
						}
					}
				}
				else {
					fprintf(stderr, 
					"Non array type element accessed with index on line %d.\n",
					curr -> child -> nodeData.leaf -> tn -> line_num);
				}
			}
			else {
				astDataType t;
				if(ch -> type == AST_NODE_VARIDNUM)
					t = ch -> nodeData.var -> dataType;
				else if(ch -> type == AST_NODE_LEAF)
					t = ch -> nodeData.leaf -> dataType;
				else if(ch -> type == AST_NODE_AOBEXPR)
					t = ch -> nodeData.AOBExpr -> dataType;
				else if(ch -> type == AST_NODE_UNARY)
					t = ch -> nodeData.unary -> dataType;
				if(tmp -> dataType != t) {
					fprintf(stderr, 
					"Type mismatch3 in assignment statement on line %d.\n",
					curr -> child -> nodeData.leaf -> tn -> line_num);
					return;
				}
				if(tmp -> dataType == AST_TYPE_ARRAY) {
					SymTableVar *rhs = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex);
					if((tmp -> sdt.r -> dataType != rhs -> sdt.r -> dataType)||
						(tmp -> sdt.r -> low != rhs -> sdt.r -> low)||
						(tmp -> sdt.r -> high != rhs -> sdt.r -> high)) {
						fprintf(stderr, 
						"Type mismatch4 in assignment statement on line %d.\n",
						curr -> child -> nodeData.leaf -> tn -> line_num);
						return;
					}
				}
			}
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
			ch = curr -> child;

			if(ch -> type == AST_NODE_IDLIST)
				ch = ch -> next;

			int line_num = ch -> nodeData.leaf -> tn -> line_num;
			SymTableFunc* tmp = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			if(tmp == NULL) {
				fprintf(stderr, 
				"Function called (reused)'%s' is not defined on line %d.\n", ch -> nodeData.leaf -> tn -> lex, line_num);
				return;
			}
			if(strcmp(fname, tmp -> name) == 0) {
				fprintf(stderr, 
				"Recursion is not supported on line %d.\n", line_num);
				return;
			}
			/* To be done in pass2 if the function is not defined. */
			if(tmp -> isDefined == 0) {
				curr -> nodeData.moduleReuse -> listCheck = 0;
				return;
			}
			if(ch -> prev != NULL && !listTypeMatch(tmp -> output_plist -> head, ch -> prev, curr -> localST)) {
				fprintf(stderr, 
				"Output list type mismatch on line %d.\n", line_num);
			}
			if(ch -> prev != NULL && listTypeMatch(tmp -> output_plist -> head, ch -> prev, curr -> localST) == -1) {
				fprintf(stderr, 
				"Number of output parameters mismatch on line %d.\n", line_num);
			}

			/* searching the idList in case 38, optioanal may be NULL*/
			ch = ch -> next;
			while(ch -> type != AST_NODE_IDLIST)
				ch = ch -> next;

			if(!listTypeMatch(tmp -> input_plist -> head, ch, curr -> localST)) {
				fprintf(stderr, 
				"Input list type mismatch name : %s on line %d.\n", tmp -> name, line_num);
			}
			if(listTypeMatch(tmp -> input_plist -> head, ch, curr -> localST) == -1) {
				fprintf(stderr, 
				"Number of input parameters mismatch on line %d.\n", line_num);
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
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			ch -> next -> next -> localST = curr -> localST;
			ch -> next -> localST = curr -> localST;
			traverseAST(ch, fname);
			traverseAST(ch -> next, fname);
			traverseAST(ch -> next -> next, fname);
			astDataType tl, tr;
			ch = curr -> child;
			if(ch -> type == AST_NODE_LEAF) {
				tl = ch -> nodeData.leaf -> dataType;
			}
			else if(ch -> type == AST_NODE_AOBEXPR) {
				tl = ch -> nodeData.AOBExpr -> dataType;
			}
			else if(ch -> type == AST_NODE_VARIDNUM) {
				tl = ch -> nodeData.var -> dataType;
			}
			if(ch -> next -> next -> type == AST_NODE_LEAF) {
				tr = ch -> next -> next -> nodeData.leaf -> dataType;
			}
			else if(ch -> next -> next -> type == AST_NODE_AOBEXPR) {
				tr = ch -> next -> next -> nodeData.AOBExpr -> dataType;
			}
			else if(ch -> next -> next -> type == AST_NODE_VARIDNUM) {
				tr = ch -> next -> next -> nodeData.var -> dataType;
			}
			if(tl == AST_TYPE_ARRAY) {
				if(ch -> type == AST_NODE_VARIDNUM && ch -> child -> next != NULL) {
					SymTableVar * var = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex);
					tl = var -> sdt.r -> dataType;
				}
				else if(ch -> type == AST_NODE_VARIDNUM){
					fprintf(stderr, 
					"Array type variable '%s' in arithmetic operation on line %d.\n", ch -> child -> nodeData.leaf -> tn -> lex, ch -> child -> nodeData.leaf -> tn -> line_num);
					return;
				}
			}
			if(tr == AST_TYPE_ARRAY) {
				if(ch -> next -> next -> type == AST_NODE_VARIDNUM && ch -> next -> next -> child -> next != NULL) {
					SymTableVar * var = fetchVarData(curr -> localST, ch -> next -> next -> child -> nodeData.leaf -> tn -> lex);
					tr = var -> sdt.r -> dataType;
				}
				else {
					fprintf(stderr, 
					"Array type variable '%s' in arithmetic operation on line %d.\n", ch -> next -> next -> child -> nodeData.leaf -> tn -> lex, ch -> next -> next -> child -> nodeData.leaf -> tn -> line_num);
					return;
				}
			}
			// tr = (ch -> next -> next) -> nodeData.AOBExpr -> dataType;
			if((ch -> next) -> nodeData.leaf -> op == AST_AOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch1 in the expression line %d, tl = %s, tr = %s.\n", (ch -> next) -> nodeData.leaf -> tn -> line_num,
						typeName[tl], typeName[tr]);
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Bool type variables in arithmetic operation on line %d.\n", (ch -> next) -> nodeData.leaf -> tn -> line_num);
				}
				else 
					curr -> nodeData.AOBExpr -> dataType = tl;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_RELOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch2 in the expression line %d, tl = %s, tr = %s.\n", (ch -> next) -> nodeData.leaf -> tn -> line_num,
						typeName[tl], typeName[tr]);
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Bool type variables in arithmetic operation on line %d.\n", (ch -> next) -> nodeData.leaf -> tn -> line_num);
				}
				curr -> nodeData.AOBExpr -> dataType = AST_TYPE_BOOLEAN;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_LOP) {
				if(tl != AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Left operator of LOP is not boolean type line %d.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num);		
				}
				if(tr != AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Right operator of LOP is not boolean type line %d.\n",
					(ch -> next) -> nodeData.leaf -> tn -> line_num);
				}
				curr -> nodeData.AOBExpr -> dataType = AST_TYPE_BOOLEAN;
			}
		}
		break;

		case AST_NODE_DECLARESTMT: {
			ASTNode* ch = curr -> child;
			ch -> next -> localST = curr -> localST;
			traverseAST(ch -> next, fname);
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
			traverseAST(ch, fname);
			if((ch -> nodeData).leaf -> dataType == AST_TYPE_REAL) {
				fprintf(stderr, 
				"Switch variable('%s') is of real type on line %d.\n", ch -> nodeData.leaf -> tn -> lex,
					ch -> nodeData.leaf -> tn -> line_num);
				return;
			}
			SymTableFunc* newST = getFuncTable(fname, curr -> localST);
			newST -> start_line_num = curr -> nodeData.condStmt -> start_line_num;
			newST -> end_line_num = curr -> nodeData.condStmt -> end_line_num;
			ASTNode* ch1 = ch -> next;
			ch1 -> localST = newST;
			ch1 -> nodeData.dataType = ch -> nodeData.dataType;
			strcpy(ch1 -> nodeData.caseStmt -> switchVar, ch -> nodeData.leaf -> tn -> lex);
			traverseAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			if(ch -> nodeData.leaf -> dataType == AST_TYPE_BOOLEAN) {
				if(curr -> nodeData.condStmt -> def == 1) {
					fprintf(stderr, 
					"Default case in bool type switch statement on line %d.\n", curr -> nodeData.condStmt -> def_line_num);
				}
				if(ch2 == NULL)
					return;
				ch2 -> localST = newST;
				traverseAST(ch2, fname);
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
					traverseAST(ch2, fname);
				}
			}
			else {
				fprintf(stderr, 
				"Switch variable not of feasible type on line %d.\n", ch -> nodeData.leaf -> tn -> line_num);
				if(ch2 == NULL)
					return;
				ch2 -> localST = newST;
				traverseAST(ch2, fname);
			}
		}
		break;
		
		case AST_NODE_CASESTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
			if(ch == NULL)
				return;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
			if(ch == NULL) {
				return;
			}

			ch -> localST = curr -> localST;
			ch -> nodeData.dataType = curr -> nodeData.dataType;
			strcpy(ch -> nodeData.caseStmt -> switchVar, curr -> nodeData.caseStmt -> switchVar);
			traverseAST(ch, fname);
		}
		break;

		case AST_NODE_UNARY: {
			ASTNode* ch = curr -> child;
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
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
			traverseAST(ch, fname);
			ch = curr -> child -> next;
			curr -> nodeData.lvalueARRStmt -> dataType = ch -> nodeData.AOBExpr -> dataType;
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			ch = curr -> child;
			if(curr -> nodeData.iterStmt -> type == AST_ITER_FOR) {
				if(ch -> nodeData.leaf -> dataType != AST_TYPE_INT) {
					fprintf(stderr, 
					"For loop variable('%s') is not of int type on line %d.\n",
					ch -> nodeData.leaf -> tn -> lex,
					ch -> nodeData.leaf -> tn -> line_num);
					return;
				}
			}
			else {
				astDataType t;
				if(ch -> type == AST_NODE_VARIDNUM)
					t = ch -> nodeData.var -> dataType;
				else if(ch -> type == AST_NODE_AOBEXPR)
					t = ch -> nodeData.AOBExpr -> dataType;
				else if(ch -> type == AST_NODE_LEAF)
					t = ch -> nodeData.leaf -> dataType;
				if(t != AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"While loop expression is not of boolean type on line %d.\n",
					curr -> nodeData.iterStmt -> start_line_num);
				}
			}

			SymTableFunc* newST = getFuncTable(fname, curr -> localST);

			newST -> start_line_num = curr -> nodeData.iterStmt -> start_line_num;
			newST -> end_line_num = curr -> nodeData.iterStmt -> end_line_num;

			ASTNode* ch1 = ch -> next;
			if(ch1 == NULL) {
				return;
			}
			ch1 -> localST = newST;
			traverseAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			if(ch2 == NULL) {
				return;
			}
			ch2 -> localST = newST;
			traverseAST(ch2, fname);
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
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
					ASTNode * tmp = curr -> parent;
					if(tmp != NULL)
						tmp = tmp -> parent;
					if(tmp != NULL)
						tmp = tmp -> parent;
					if(idx == NULL && tmp != NULL && tmp -> type != AST_NODE_INPUTLIST) {
						fprintf(stderr, 
						"Index variable is not defined on line %d.\n", curr -> nodeData.leaf -> tn -> line_num);
						return;
					}
					if(idx == NULL)
						return;
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