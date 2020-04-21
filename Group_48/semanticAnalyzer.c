/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semanticAnalyzer.h"
#include "symbolTable.h"
#include "ast.h"
#include "utils.h"

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
				typeNode -> nodeData.leaf -> dataType, idNode -> nodeData.leaf -> tn -> line_num);
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

/**
* @param wh	ASTNode corresponding to while cond=struct
* @param ch	ASTNode node corresponding to the while expression
* It initializes the check for the assignment of the while expression variables in the while construct scope.
*/ 
void processWhileExpression(ASTNode * wh, ASTNode * ch) {

	if(ch -> type == AST_NODE_LEAF)
		return;
	else if(ch -> type == AST_NODE_VARIDNUM) {
		ASTNode * idNode = ch -> child;
		SymTableVar * id = fetchVarData(wh -> localST, idNode -> nodeData.leaf -> tn -> lex, wh -> nodeData.iterStmt -> start_line_num);
		if(id != NULL)
			id -> whileNest = globalNest;
	}
	else if(ch -> type == AST_NODE_AOBEXPR) {
		processWhileExpression(wh, ch -> child);
		processWhileExpression(wh, ch -> child -> next -> next);
	}
}

/**
 * @param wh	ASTNode corresponding to while cond=struct
 * @param ch	ASTNode node corresponding to the while expression
 * It checks whether any of the variables(if any) in the while loop expression is assigned in the while scope or not.
 */ 
int checkWhileAssignment(ASTNode * wh, ASTNode * ch) {

	if(ch -> type == AST_NODE_LEAF)
		return 0;
	else if(ch -> type == AST_NODE_VARIDNUM) {
		varPresent = 1;
		ASTNode * idNode = ch -> child;
		SymTableVar * id = fetchVarData(wh -> localST, idNode -> nodeData.leaf -> tn -> lex, idNode -> nodeData.leaf -> tn -> line_num);
		if(id != NULL && id -> whileNest > globalNest)
			return 1;
	}
	else if(ch -> type == AST_NODE_AOBEXPR) {
		if(checkWhileAssignment(wh, ch -> child))
			return 1;
		if(checkWhileAssignment(wh, ch -> child -> next -> next))
			return 1;
	}
	return 0;
}

void boundChecking(SymTableVar * tmp, ASTNode * curr) {
	astNodeType t = curr -> type;
	ASTNode* ch = curr -> child;
	if(strcmp(tmp -> sdt.r -> lowId, "") == 0 && strcmp(tmp -> sdt.r -> highId, "") == 0) {

		if(t == AST_NODE_IO) {
			if(ch -> next -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
				if(ch -> next -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is less than the lower bound %d\n",
					ch -> next -> nodeData.leaf -> tn -> line_num,
					ch -> next -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> low);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
					curr -> nodeData.io -> b = BOUND_ERROR;
				}
				if(ch -> next -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is greater than the upper bound %d\n",
					ch -> next -> nodeData.leaf -> tn -> line_num,
					ch -> next -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> high);	
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
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
				if(ch -> next -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is less than the lower bound %d\n",
					ch -> next -> nodeData.leaf -> tn -> line_num,
					ch -> next -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> low);	
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
					curr -> nodeData.io -> b = BOUND_ERROR;
				}
				if(ch -> next -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is greater than the upper bound %d\n",
					ch -> next -> nodeData.leaf -> tn -> line_num,
					ch -> next -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> high);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);	
					curr -> nodeData.io -> b = BOUND_ERROR;
				}
				else 
					curr -> nodeData.var -> b = BOUND_CORRECT;
			}
			else 
				curr -> nodeData.var -> b = BOUND_RUNTIME;
		}

		if(t == AST_NODE_ASSIGN) {
			if(ch -> next -> child -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
				if(ch -> next -> child -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is lower than the lower bound %d\n",
					ch -> next -> child -> nodeData.leaf -> tn -> line_num,
					ch -> next -> child -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> low);	
					reportError(ch -> next -> child -> nodeData.leaf -> tn -> line_num, message);
					curr -> nodeData.io -> b = BOUND_ERROR;
				}
				if(ch -> next -> child -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- Index %d is greater than the upper bound %d\n",
					ch -> next -> child -> nodeData.leaf -> tn -> line_num,
					ch -> next -> child -> nodeData.leaf -> tn -> value.val_int,
					tmp -> sdt.r -> high);	
					reportError(ch -> next -> child -> nodeData.leaf -> tn -> line_num, message);
					curr -> nodeData.io -> b = BOUND_ERROR;
				}
				else 
					curr -> nodeData.assign -> b = BOUND_CORRECT;
			}
			else 
				curr -> nodeData.assign -> b = BOUND_RUNTIME;
		}
	}
}


int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST) {
	/* check if head or node is NULL */
	if (head == NULL) {
		char message[200];
		sprintf(message, "Line number (%d): semantic error -- Assigning a value from a function which does not return a value\n", node -> child -> nodeData.leaf -> tn -> line_num);
		reportError(node -> child -> nodeData.leaf -> tn -> line_num, message);
		return 0;
	}

	SymTableVar * tmp = (SymTableVar*) (head -> data);
	if(node -> type == AST_NODE_LEAF)
		node = NULL;
	while(head != NULL && node != NULL) {
		tmp = (SymTableVar*) (head -> data);
		SymTableVar* curr = fetchVarData(localST, node -> child -> nodeData.leaf -> tn -> lex, node -> child -> nodeData.leaf -> tn -> line_num);
		if(curr == NULL) {
			char message[200];
			sprintf(message, 
			"Line number (%d): semantic error -- The parameter '%s' is not declared.\n", 
			node -> child -> nodeData.leaf -> tn -> line_num,
			node -> child -> nodeData.leaf -> tn -> lex);
			reportError(node -> child -> nodeData.leaf -> tn -> line_num, message);
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
					return;
				}
				if(ch == NULL)
					return;
				globalNest = 0;
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
			globalNest = 0;
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
			/* Nothing to do*/
		}
		break;

		case AST_NODE_OUTPUTLIST: {
			/* Nothing to do*/
		}
		break;

		case AST_NODE_ARRAY: {
	
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
			/* lower range */
			ASTNode* ch1 = curr -> child;  
			ch1 -> localST = curr -> localST;

			/* Traversing important to validate index types allowed*/
			traverseAST(ch1, fname);

			/* Note whle debugging: ch->next changed to curr -> next -> child*/
			/* upper range */
			ASTNode* ch2 = curr -> child -> next; 
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
				SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex, ch -> nodeData.leaf -> tn -> line_num); //Args: Symbol Table, Name
				if(tmp == NULL) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- variable '%s' taken as input has not been declared.\n", 
					ch -> nodeData.leaf -> tn -> line_num, ch -> nodeData.leaf -> tn -> lex);
					reportError(ch -> nodeData.leaf -> tn -> line_num, message);
				}
				else {
					tmp -> isAssigned = 1;
					tmp -> whileNest = globalNest;
				}
			}
			else { // AST_IO_PRINT
				if(ch -> type == AST_NODE_VARIDNUM) {
					SymTableVar* tmp = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex, ch -> child -> nodeData.leaf -> tn -> line_num); //Args: Symbol Table, Name
					if(tmp == NULL) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- the variable '%s' to be output has not been declared.\n", 
						ch -> child -> nodeData.leaf -> tn -> line_num, ch -> child -> nodeData.leaf -> tn -> lex);
						reportError(ch -> child -> nodeData.leaf -> tn -> line_num, message);
					}
					else if(ch -> child -> next != NULL && tmp -> dataType != AST_TYPE_ARRAY) {   //int a; a[4];  --> error
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- attempt to access non-array type variable %s using index.\n", 
						ch -> child -> nodeData.leaf -> tn -> line_num,ch -> child -> nodeData.leaf -> tn -> lex);
						reportError(ch -> child -> nodeData.leaf -> tn -> line_num, message);
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
			SymTableVar* tmp = fetchVarData(curr->localST, ch -> nodeData.leaf -> tn -> lex, ch -> nodeData.leaf -> tn -> line_num);
			if(tmp == NULL) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- the left-hand-side of assignment statement %s is not defined.\n",
				ch -> nodeData.leaf -> tn -> line_num,
				ch -> nodeData.leaf -> tn -> lex
				);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
			}
			else
				tmp -> whileNest = globalNest;
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
							char message[200];
							sprintf(message, 
							"Line number (%d): semantic error -- type mismatch in assignment statement.\n",
							ch -> child -> next -> child -> nodeData.leaf -> tn -> line_num);
							reportError(ch -> child -> next -> child -> nodeData.leaf -> tn -> line_num, message);
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
							char message[200];
							sprintf(message, 
							"Line number (%d): semantic error -- type mismatch in assignment statement.\n",
							curr -> child -> nodeData.leaf -> tn -> line_num);
							reportError(ch -> child -> nodeData.leaf -> tn -> line_num, message);
						}
					}
				}
				else {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- attempt to access non-array type variable %s using index.\n",
					curr -> child -> nodeData.leaf -> tn -> line_num, curr -> child -> nodeData.leaf -> tn -> lex);
					reportError(curr -> child -> nodeData.leaf -> tn -> line_num, message);
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
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- type mismatch in assignment statement. LHS = %s, RHS = %s\n",
					curr -> child -> nodeData.leaf -> tn -> line_num,
					typeName[tmp->dataType],
					typeName[t]);
					reportError(curr-> child -> nodeData.leaf -> tn -> line_num, message);
					return;		
				}
				if(tmp -> dataType == AST_TYPE_ARRAY) {
					SymTableVar *rhs = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex, ch -> child -> nodeData.leaf -> tn -> line_num);

					if(tmp -> sdt.r -> dataType != rhs -> sdt.r -> dataType) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- type mismatch in assignment statement. LHS = %s, RHS = %s\n",
						curr -> child -> nodeData.leaf -> tn -> line_num,
						typeName[tmp -> sdt.r -> dataType],
						typeName[rhs -> sdt.r -> dataType]);
						reportError(curr -> child 	-> nodeData.leaf -> tn -> line_num, message);
					}
					if(strcmp(tmp -> sdt.r -> lowId, "") == 0 && strcmp(rhs -> sdt.r -> lowId, "") == 0 && tmp -> sdt.r -> low != rhs -> sdt.r -> low) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- Lower bound of array on LHS %d is not equal to lower bound of array on RHS %d in assignment statement\n",
						curr -> child -> nodeData.leaf -> tn -> line_num,
						tmp -> sdt.r -> low,
						rhs -> sdt.r -> low);
						reportError(curr -> child -> nodeData.leaf -> tn -> line_num, message);
					}
					if(strcmp(tmp -> sdt.r -> highId, "") == 0 && strcmp(rhs -> sdt.r -> highId, "") == 0 && tmp -> sdt.r -> high != rhs -> sdt.r -> high) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- Upper bound of array on LHS %d is not equal to upper bound of array on RHS %d in assignment statement\n",
						curr -> child -> nodeData.leaf -> tn -> line_num,
						tmp -> sdt.r -> high,
						rhs -> sdt.r -> high);
						reportError(curr -> child -> nodeData.leaf -> tn -> line_num, message);
					}
				}
			}
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
			ch = curr -> child;

			if(ch -> type == AST_NODE_IDLIST) {
				ch -> localST = curr -> localST;
				traverseAST(ch, fname);
				ch = ch -> next;
			}

			int line_num = ch -> nodeData.leaf -> tn -> line_num;
			SymTableFunc* tmp = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			if(tmp == NULL) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- function called (reused) '%s' is not defined.\n", 
				line_num,
				ch -> nodeData.leaf -> tn -> lex
				);
				reportError(line_num, message);
				return;
			}
			if(strcmp(fname, tmp -> name) == 0) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- recursion (function: %s) is not supported.\n", line_num, fname);
				reportError(line_num, message);
				return;
			}
			/* To be done in pass2 if the function is not defined. */
			if(tmp -> isDefined == 0) {
				curr -> nodeData.moduleReuse -> listCheck = 0;
				return;
			}
			if(ch -> prev != NULL && !listTypeMatch(tmp -> output_plist -> head, ch -> prev, curr -> localST)) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- type mismatch on output parameter name: '%s'.\n", 
				line_num,
				tmp->name 
				);
				reportError(line_num, message);
			}
			if(ch -> prev != NULL && listTypeMatch(tmp -> output_plist -> head, ch -> prev, curr -> localST) == -1) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- number of output parameters mismatch.\n", line_num);
				reportError(line_num, message);
			}

			/* searching the idList in case 38, optioanal may be NULL*/
			ch = ch -> next;
			while(ch -> type != AST_NODE_IDLIST)
				ch = ch -> next;

			if(!listTypeMatch(tmp -> input_plist -> head, ch, curr -> localST)) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- type mismatch on input list name: '%s'.\n", 
				line_num,
				tmp -> name 
				);
				reportError(line_num, message);
			}
			if(listTypeMatch(tmp -> input_plist -> head, ch, curr -> localST) == -1) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- number of input parameters mismatch.\n", line_num);
				reportError(line_num, message);
			}
		}
		break;

		case AST_NODE_IDLIST: {

			if(curr -> parent -> type == AST_NODE_MODULEREUSE && curr -> prev == NULL) {
				ASTNode * tmp = curr;
				while(tmp != NULL) {
					SymTableVar * id = fetchVarData(curr -> localST, tmp -> child -> nodeData.leaf -> tn -> lex, tmp -> child -> nodeData.leaf -> tn -> line_num);
					if(id != NULL)
						id -> whileNest = globalNest;
					tmp = tmp -> child -> next;
				}
			}
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
					SymTableVar * var = fetchVarData(curr -> localST, ch -> child -> nodeData.leaf -> tn -> lex, ch -> child -> nodeData.leaf -> tn -> line_num);
					tl = var -> sdt.r -> dataType;
				}
				else if(ch -> type == AST_NODE_VARIDNUM){
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- array type variable '%s' in arithmetic operation.\n", 
					ch -> child -> nodeData.leaf -> tn -> line_num,
					ch -> child -> nodeData.leaf -> tn -> lex 
					);
					reportError(ch -> child -> nodeData.leaf -> tn -> line_num, message);
					return;
				}
			}
			if(tr == AST_TYPE_ARRAY) {
				if(ch -> next -> next -> type == AST_NODE_VARIDNUM && ch -> next -> next -> child -> next != NULL) {
					SymTableVar * var = fetchVarData(curr -> localST, ch -> next -> next -> child -> nodeData.leaf -> tn -> lex, ch -> next -> next -> child -> nodeData.leaf -> tn -> line_num);
					tr = var -> sdt.r -> dataType;
				}
				else {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- array type variable '%s' in arithmetic operation.\n", 
					ch -> next -> next -> child -> nodeData.leaf -> tn -> line_num,
					ch -> next -> next -> child -> nodeData.leaf -> tn -> lex 
					);
					reportError(ch -> next -> next -> child -> nodeData.leaf -> tn -> line_num, message);
					return;
				}
			}
			// tr = (ch -> next -> next) -> nodeData.AOBExpr -> dataType;
			if((ch -> next) -> nodeData.leaf -> op == AST_AOP) {
				if(tl != tr) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- type mismatch in the expression: type on left = %s, type on right = %s.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num,
					typeName[tl], 
					typeName[tr]
					);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- boolean type sub-expression in arithmetic operation.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
				}
				else 
					curr -> nodeData.AOBExpr -> dataType = tl;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_RELOP) {
				if(tl != tr) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- type mismatch in the expression: type on left = %s, type on right = %s.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num,
					typeName[tl], 
					typeName[tr]);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- boolean type variable in arithmetic operation.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
				}
				curr -> nodeData.AOBExpr -> dataType = AST_TYPE_BOOLEAN;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_LOP) {
				if(tl != AST_TYPE_BOOLEAN) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- left operand of logical operator is not of boolean type.\n", 
					(ch -> next) -> nodeData.leaf -> tn -> line_num);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);	
				}
				if(tr != AST_TYPE_BOOLEAN) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- right operand of logical operator is not of boolean type.\n",
					(ch -> next) -> nodeData.leaf -> tn -> line_num);
					reportError(ch -> next -> nodeData.leaf -> tn -> line_num, message);
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
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- switch variable '%s' is of real type.\n", 
				ch -> nodeData.leaf -> tn -> line_num,
				ch -> nodeData.leaf -> tn -> lex
				);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
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
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- default case in switch statement on boolean variable.\n", curr -> nodeData.condStmt -> def_line_num);
					reportError(curr -> nodeData.condStmt -> def_line_num, message);
				}
				if(ch2 == NULL)
					return;
				ch2 -> localST = newST;
				traverseAST(ch2, fname);
			}
			else if(ch -> nodeData.leaf -> dataType == AST_TYPE_INT) {
				if(curr -> nodeData.condStmt -> def == 0) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- default case not present in switch statement on integer variable.\n", 
					curr -> nodeData.condStmt -> end_line_num);
					reportError(curr -> nodeData.condStmt -> end_line_num, message);
				}
				else {
					if(ch2 == NULL) {
						return;
					}
					ch2 -> localST = newST;
					traverseAST(ch2, fname);
				}
			}
			else {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- switch variable is not of feasible type.\n", 
				ch -> nodeData.leaf -> tn -> line_num);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
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
			SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex, ch -> nodeData.leaf -> tn -> line_num);
			SymTableVar* par = fetchVarData(curr -> localST, curr -> parent -> child -> nodeData.leaf -> tn -> lex, curr -> parent -> child -> nodeData.leaf -> tn -> line_num);
			if(par == NULL) {
				// "Lvalue The variable taken as input is not being declared.\n");
				/* already been taken care of */
			}
			else if(par -> dataType != AST_TYPE_ARRAY) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- attempt to access non-array type variable '%s' using index.\n", 
					ch -> nodeData.leaf -> tn -> line_num,
					par -> name
				);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);	
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
			if(curr -> nodeData.iterStmt -> type == AST_ITER_WHILE) {
				processWhileExpression(curr, ch);
				globalNest++;
			}
			traverseAST(ch, fname);
			ch = curr -> child;
			if(curr -> nodeData.iterStmt -> type == AST_ITER_FOR) {
				if(ch -> nodeData.leaf -> dataType != AST_TYPE_INT) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- for loop variable '%s' is not of integer type.\n",
					ch -> nodeData.leaf -> tn -> line_num,
					ch -> nodeData.leaf -> tn -> lex
					);
					reportError(ch -> nodeData.leaf -> tn -> line_num, message);
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
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- while loop expression is not of boolean type.\n",
					curr -> nodeData.iterStmt -> start_line_num);
					reportError(curr -> nodeData.iterStmt -> start_line_num, message);
				}
			}

			SymTableFunc* newST = getFuncTable(fname, curr -> localST);

			newST -> start_line_num = curr -> nodeData.iterStmt -> start_line_num;
			newST -> end_line_num = curr -> nodeData.iterStmt -> end_line_num;

			if(curr -> nodeData.iterStmt -> type == AST_ITER_WHILE) {

				ASTNode * ch1 = ch -> next;
				if(ch1 != NULL) {
					ch1 -> localST = newST;
					traverseAST(ch1, fname);
				}
				globalNest--;
				varPresent = 0;
				if(checkWhileAssignment(curr, ch) == 0 && varPresent > 0) {
					char message[200];
					sprintf(message, 
					"Line number (%d): semantic error -- none of the while loop expression variables are assigned within the scope.\n",
					curr -> nodeData.iterStmt -> end_line_num);
					reportError(curr -> nodeData.iterStmt-> end_line_num, message);
				}
				return;
			}

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
			SymTableVar * idNode = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex, ch -> nodeData.leaf -> tn -> line_num);
			if(idNode == NULL) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- variable '%s' not declared before line %d.\n", 
				ch -> nodeData.leaf -> tn -> line_num,
				ch -> nodeData.leaf -> tn -> lex,
				ch -> nodeData.leaf -> tn -> line_num 
				);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
				return;
			}
			curr -> nodeData.var -> dataType = idNode -> dataType;
			if(curr -> nodeData.var -> dataType == AST_TYPE_ARRAY && ch-> next == NULL && curr -> parent -> type != AST_NODE_ASSIGN) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- array variable '%s' used without index.\n",
				ch -> nodeData.leaf -> tn -> line_num,
				idNode -> name 
				);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
				return;
			}
			if(curr -> nodeData.var -> dataType != AST_TYPE_ARRAY && ch-> next != NULL) {
				char message[200];
				sprintf(message, 
				"Line number (%d): semantic error -- attempt to access non-array type variable '%s' using index.\n", 
				ch -> nodeData.leaf -> tn -> line_num,
				idNode -> name);
				reportError(ch -> nodeData.leaf -> tn -> line_num, message);
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
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- redeclaration of module '%s'.\n", 
								curr -> nodeData.leaf -> tn -> line_num, str);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
							}
							return;
						}
						break;
						case AST_NODE_MODULE: {
							SymTableFunc* tmp = fetchFuncData(str);
							if(tmp != NULL && tmp -> isDeclared == 1) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- redundant declaration of function '%s'.\n", 
								curr -> nodeData.leaf -> tn -> line_num,
								str 
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
							}
							if(tmp != NULL && tmp -> isDefined == 1) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- multiple definitions for the function '%s'.\n", 
								curr -> nodeData.leaf -> tn -> line_num,
								str
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
								return;
							}
							if(tmp == NULL) {
								tmp = insertFuncRecord(str);
								tmp -> isDeclared = 0;
								tmp -> isDefined = 1;
							}
							if(tmp != NULL) {
								tmp -> start_line_num = curr -> parent -> nodeData.module -> start_line_num;
								tmp -> end_line_num = curr -> parent -> nodeData.module -> end_line_num;
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
								SymTableVar* idx = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
								if(idx == NULL) {
									char message[200];
									sprintf(message, 
									"Line number (%d): semantic error -- index variable '%s' not defined.\n",
									curr -> nodeData.leaf -> tn -> line_num,
									str
									);
									reportError(curr -> nodeData.leaf -> tn -> line_num, message);
									return;
								}
								if(idx -> dataType != AST_TYPE_INT) {
									char message[200];
									sprintf(message, 
									"Line number (%d): semantic error -- index variable '%s' is not an integer.\n", 
									curr -> nodeData.leaf -> tn -> line_num,
									str
									);
									reportError(curr -> nodeData.leaf -> tn -> line_num, message);
								}
								curr -> nodeData.leaf -> dataType = idx -> dataType;
							}
							else {
								SymTableVar* tmp = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
								if(tmp == NULL) {
									// char message[200];
									// "The identifier('%s') not declared on line %d.\n", str, 
									// curr -> nodeData.leaf -> tn -> line_num);
									return;
								}
								curr -> nodeData.leaf -> dataType = tmp -> dataType;
							}
						}
						break;
						case AST_NODE_LVALARRSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
							if(idx == NULL) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- index variable '%s' not defined.\n", 
								curr -> nodeData.leaf -> tn -> line_num,
								str
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
								return;
							}
							if(idx -> dataType != AST_TYPE_INT) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- range arrays variable '%s' is not integer.\n", 
								curr -> nodeData.leaf -> tn -> line_num,
								str
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
							}
						}
						break;
						case AST_NODE_ASSIGN: {
							return;
						}
						break;
						case AST_NODE_MODULEREUSE: {
							SymTableFunc* func = fetchFuncData(str);
							if(func == NULL) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- module used (called) '%s' is not declared or defined.\n", 
								curr -> nodeData.leaf -> tn -> line_num,
								str
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
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
							SymTableVar* idx = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
							if(idx == NULL) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- switch variable '%s' is not defined.\n",
								curr -> nodeData.leaf -> tn -> line_num,
								str
								);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
								return;
							}
							else {
								curr -> nodeData.leaf -> dataType = idx -> dataType;
							}
						}
						break;
						case AST_NODE_ITERSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
							if(idx == NULL) {
								char message[200];
								sprintf(message, 
								"Line number (%d): semantic error -- Loop variable '%s' is not defined.\n",
								curr -> nodeData.leaf -> tn -> line_num, str);
								reportError(curr -> nodeData.leaf -> tn -> line_num, message);
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
						SymTableVar* arr = fetchVarData(curr -> localST, curr -> parent -> child -> nodeData.leaf -> tn -> lex, curr -> parent -> child -> nodeData.leaf -> tn -> line_num);
						if(arr == NULL) { 
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
					SymTableVar* idx = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
					ASTNode * tmp = curr -> parent;
					if(tmp != NULL)
						tmp = tmp -> parent;
					if(tmp != NULL)
						tmp = tmp -> parent;
					if(idx == NULL && tmp != NULL && tmp -> type != AST_NODE_INPUTLIST) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- index variable '%s' not defined.\n", 
						curr -> nodeData.leaf -> tn -> line_num, curr->nodeData.leaf->tn->lex);
						reportError(curr -> nodeData.leaf -> tn -> line_num, message);
						return;
					}
					if(idx == NULL)
						return;
					if(idx -> dataType != AST_TYPE_INT) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- index variable '%s' in range arrays not an integer.\n", 
						curr -> nodeData.leaf -> tn -> line_num,
						idx->name
						);
						reportError(curr -> nodeData.leaf -> tn -> line_num, message);
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
					SymTableVar* tmp = fetchVarData(curr -> localST, str, curr -> nodeData.leaf -> tn -> line_num);
					if(tmp == NULL) {
						char message[200];
						sprintf(message, 
						"Line number (%d): semantic error -- undeclared identifier '%s'.\n",
						curr -> nodeData.leaf -> tn -> line_num,
						str
						);
						reportError(curr -> nodeData.leaf -> tn -> line_num, message);
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