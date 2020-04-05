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

void insertplist(ASTNode * curr, char * str) {
	
	int paramType;
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
		if(ch -> next -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
			if((ch -> next -> nodeData.leaf -> tn -> value.val_int < tmp -> sdt.r -> low) ||
				(ch -> next -> nodeData.leaf -> tn -> value.val_int > tmp -> sdt.r -> high)) {
				fprintf(stderr, 
				"Static bound checking failed\n");	
				if(t == AST_NODE_IO)
					curr -> nodeData.io -> b = BOUND_ERROR;
					
			}
			else {
				if(t == AST_NODE_IO)
					curr -> nodeData.io -> b = BOUND_CORRECT;
			}
		}
		else {
			if(t == AST_NODE_IO)
				curr -> nodeData.io -> b = BOUND_RUNTIME;
		}
	}
	else {
		if(t == AST_NODE_IO)
			curr -> nodeData.io -> b = BOUND_RUNTIME;	
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

	SymTableVar * tmp = (SymTableVar*) head -> data;
	if(node -> type == AST_NODE_LEAF)
		node = NULL;
	while(head != NULL && node != NULL) {
		tmp = (SymTableVar*) head -> data;
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
			if(strcmp(tmp -> sdt.r -> lowId, "") == 0 && strcmp(tmp -> sdt.r -> highId, "") == 0) {
				if(strcmp(curr -> sdt.r -> lowId, "") == 0 && strcmp(curr -> sdt.r -> highId, "") == 0) {
					if(tmp -> sdt.r -> low != curr -> sdt.r -> low)
						return 0;
					if(tmp -> sdt.r -> high != curr -> sdt.r -> high)
						return 0;	
				}
			}
		}
		node = node -> child -> next;
		head = head -> next;
	}
	if(tmp == NULL && node == NULL)
		return 1;
	fprintf(stderr, 
	"Different number of parameters.\n");
	return 0;
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
				ch -> localST = tmp;
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
					/* Report topmost error; ignore nested errors*/
					if(tmp == NULL)
						return;
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
			/**
			*  TODO: leaf
			*  1. Access ID of each node while (ch->next->child!=NULL)
			*  2. call addParamToFunction(SymbolTable st, char* funcName, int paramType, char* varName, int varWidth, astDataType varDataType);
			*/
			// ASTNode* ch = curr -> child;
			// /* Use traverseChildren(ch)?*/
			// traverseChildren(ch, fname);
			/* Verify: nothing to do*/
		}
		break;

		case AST_NODE_OUTPUTLIST: {
			// ASTNode* ch = curr -> child;
			// /* Use traverseChildren(ch)?*/
			// traverseChildren(ch, fname);
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
					"The variable taken as input is not being declared.\n");
				}
				else {
					tmp -> isAssigned = 1;
				}
			}
			else { // AST_IO_PRINT
				if(ch -> type == AST_LEAF_ID) {
					SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex); //Args: Symbol Table, Name
					if(tmp == NULL) {
						fprintf(stderr, 
						"The variable taken as input is not being declared.\n");
					}
					else if(ch -> next != NULL && tmp -> dataType != AST_TYPE_ARRAY) {   //int a; a[4];  --> error
						fprintf(stderr, 
						"A non array type variable access using whichId\n");	
					}
					else if(ch -> next != NULL) {
						boundChecking(tmp, curr);
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
				"The lhs of the Assignment statement is not defined.\n");
			}
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
			ch = curr -> child;

			if(ch -> type == AST_NODE_IDLIST)
				ch = ch -> next;

			SymTableFunc* tmp = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			if(strcmp(fname, tmp -> name) == 0) {
				fprintf(stderr, 
				"Recursion is not supported.\n");
				return;
			}
			if(!listTypeMatch(tmp -> output_plist -> head, ch -> prev, curr -> localST)) {
				fprintf(stderr, 
				"Output list type mismatch.\n");	
			}
			
			/* searching the idList in case 38, optioanal may be NULL*/
			ch = ch -> next;
			while(ch -> type != AST_NODE_IDLIST)
				ch = ch -> next;

				typedef struct node {
	void* data;
	struct node* next;
	struct node* prev;
} Node;
			
			if(!listTypeMatch(tmp -> input_plist -> head, ch, curr -> localST)) {
				fprintf(stderr, 
				"Input list type mismatch.\n");	
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
			traverseAST(ch, fname);
			traverseAST(ch -> next -> next, fname);
			astDataType tl, tr;
			ch = curr -> child;
			tl = ch -> nodeData.AOBExpr -> dataType;
			tr = (ch -> next -> next) -> nodeData.AOBExpr -> dataType;
			if((ch -> next) -> nodeData.leaf -> op == AST_AOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch in the expression.\n");
				}
				else if(tl == AST_TYPE_ARRAY) {
					fprintf(stderr, 
					"Array type variables in arithmetic operation.\n");		
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Bool type variables in arithmetic operation.\n");	
				}
				else 
					curr -> type = tl;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_RELOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch in the expression.\n");	
				}
				else if(tl == AST_TYPE_ARRAY) {
					fprintf(stderr, 
					"Array type variables in relational operation.\n");		
				}
				else if(tl == AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Bool type variables in relational operation.\n");	
				}
				curr -> nodeData.AOBExpr -> dataType = AST_TYPE_BOOLEAN;
			}
			else if((ch -> next) -> nodeData.leaf -> op == AST_LOP) {
				if(tl != AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Left operator of LOP is not boolean type.\n");		
				}
				if(tr != AST_TYPE_BOOLEAN) {
					fprintf(stderr, 
					"Right operator of LOP is not boolean type.\n");	
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
					addDataToFunction(curr -> localST, fname, idNode -> nodeData.leaf -> tn -> lex, ch -> next -> nodeData.leaf -> dataType);
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
				"switch variable is of real type.\n");
				return;
			}

			SymTableFunc* newST = getFuncTable(fname, curr -> localST);
			ASTNode* ch1 = ch -> next;
			ch1 -> localST = newST;
			ch1 -> nodeData.dataType = ch -> nodeData.dataType;
			strcpy(ch1 -> nodeData.caseStmt -> switchVar, ch -> nodeData.leaf -> tn -> lex);
			traverseAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			if(ch -> nodeData.leaf -> dataType == AST_TYPE_BOOLEAN) {
				if(ch2 != NULL) {
					fprintf(stderr, 
					"Default case in bool type.\n");
				}
			}
			else if(ch -> nodeData.leaf -> dataType == AST_TYPE_INT) {
				if(ch2 == NULL) {
					fprintf(stderr, 
					"Default case not present in int type.\n");
				}
				else {
					ch2 -> localST = newST;
					// ch2 -> nodeData.statement -> type = ch -> nodeData.leaf -> dataType;
					traverseAST(ch2, fname);
				}
			}
			else {
				fprintf(stderr, 
				"Switch variable not of feasible type.\n");
			}
		}
		break;
		
		case AST_NODE_CASESTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
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
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			ASTNode* ch = curr -> child;
			SymTableVar* tmp = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			SymTableVar* par = fetchVarData(curr -> localST, curr -> parent -> child -> nodeData.leaf -> tn -> lex);
			if(tmp == NULL) {
				fprintf(stderr, 
				"The variable taken as input is not being declared.\n");
			}
			else if(par -> dataType != AST_TYPE_ARRAY) {
				fprintf(stderr, 
				"A non array type variable access using whichId\n");	
			}
			else if(ch -> next != NULL) {
				boundChecking(par, curr -> parent);
			}
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode* ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			if(ch -> nodeData.dataType != AST_TYPE_INT) {
				fprintf(stderr, 
				"For loop variable is not of int type.\n");
				return;
			}

			SymTableFunc* newST = getFuncTable(fname, curr -> localST);
			ASTNode* ch1 = ch -> next;
			ch1 -> localST = newST;
			traverseAST(ch1, fname);

			ASTNode* ch2 = ch1 -> next;
			ch2 -> localST = newST;
			traverseAST(ch2, fname);
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode* ch = curr -> child;
			traverseChildren(ch, fname);
			ch = curr -> child;
			
			if(ch -> nodeData.leaf -> dataType == AST_TYPE_ARRAY && ch-> next == NULL) {
				fprintf(stderr, 
				"Array variable used without index.\n");
			}
			if(ch -> nodeData.leaf -> dataType != AST_TYPE_ARRAY && ch-> next != NULL) {
				fprintf(stderr, 
				"Non Array variable used with index.\n");
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
				case AST_LEAF_RNUM: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_REAL;
					return;	
				}
				case AST_LEAF_BOOL: {
					curr -> nodeData.leaf -> dataType = AST_TYPE_BOOLEAN;
					return;	
				}
				case AST_LEAF_ID: {
					char str[30];
					strcpy(str, curr -> nodeData.leaf -> tn -> lex);
					switch(curr -> parent -> type) {
						case AST_NODE_MODULEDECLARATION: {
							insertFuncRecord(str);
							return;
						}
						case AST_NODE_MODULE: {
							SymTableFunc* tmp = fetchFuncData(str);
							if(tmp != NULL && tmp -> isDeclared == 1) {
								fprintf(stderr, 
								"Redundant declaration of the function.\n");
								return;
							}
							if(tmp != NULL && tmp -> isDefined == 1) {
								fprintf(stderr, 
								"Multiple definitions for the function.\n");
								return;
							}
							if(tmp == NULL) {
								tmp = insertFuncRecord(str);
								tmp -> isDeclared = 0;
								tmp -> isDefined = 1;
							}
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
									"Index variable is not defined.\n");
									return;
								}
								if(idx -> dataType != AST_TYPE_INT) {
									fprintf(stderr, 
									"Index variable is not Integer.\n");
								}
							}
						}
						break;
						case AST_NODE_LVALARRSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Index variable is not defined.\n");
								return;
							}
							if(idx -> dataType != AST_TYPE_INT) {
								fprintf(stderr, 
								"Index variable in range arrays is not Integer.\n");
							}
						}
						break;
						case AST_NODE_ASSIGN: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"The variable to be assigned is not declared.\n");
								return;
							}
						}
						case AST_NODE_MODULEREUSE: {
							SymTableFunc* func = fetchFuncData(str);
							if(func == NULL) {
								fprintf(stderr, 
								"The function used is not declared and defined.\n");
								return;
							}
							if(func -> isDefined == 0) {
								func -> isDeclared++;
							}
						}
						case AST_NODE_IDLIST: {
							/* handled above in typelistmatch()*/
						}
						break;
						case AST_NODE_CONDSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Switch variable is not defined.\n");
								return;
							}
						}
						case AST_NODE_ITERSTMT: {
							SymTableVar* idx = fetchVarData(curr -> localST, str);
							if(idx == NULL) {
								fprintf(stderr, 
								"Switch variable is not defined.\n");
								/* not declared, still giving it a type*/
								curr -> nodeData.dataType = AST_TYPE_INT;
								return;
							}	
						}
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
						boundChecking(arr, curr -> parent);
					}
					return;
				}
				case AST_LEAF_IDXID: {
					char str[30];
					strcpy(str, curr -> nodeData.leaf -> tn -> lex);
					SymTableVar* idx = fetchVarData(curr -> localST, str);
					if(idx == NULL) {
						fprintf(stderr, 
						"Index variable is not defined.\n");
						return;
					}
					if(idx -> dataType != AST_TYPE_INT) {
						fprintf(stderr, 
						"Index variable in range arrays is not Integer.\n");
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