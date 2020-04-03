#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "symbol_table.h"

void traverseChildren(ASTNode* head, char * fname) {
	
	ASTNode* ch = head;
	while(ch != NULL) {
		ch -> localST = curr -> localST;
		traverseAST(ch, fname);
		ch = ch -> next;
	}
}

void boundChecking(SymTableVar * tmp, ASTNode * curr) {

	ASTNode * ch = curr -> child;
	if(strcmp(tmp -> sdt.r.lowId, "") == 0 && strcmp(tmp -> sdt.r.highId, "") == 0) {
		if(ch -> next -> leaf -> type == AST_LEAF_IDXNUM) {
			if((ch -> next -> leaf -> val_int < tmp -> sdt.r.low) || (ch -> next -> leaf -> val_int > tmp -> sdt.r.high)) {
				fprintf(stderr, 
				"Static bound checking failed\n");	
				curr -> nodeData -> b = BOUND_ERROR;
			}
			else
				curr -> nodeData -> b = BOUND_CORRECT;
		}
		else 
			curr -> nodeData -> b = BOUND_RUNTIME;
	}
	else
		curr -> nodeData -> b = BOUND_RUNTIME;	
}

int listTypeMatch(SymTableVar * tmp, ASTNode * node, SymTableFunc * localST) {

	if(node -> type == AST_NODE_LEAF)
		node = NULL;
	while(tmp != NULL && node != NULL) {
		SymTableVar * curr = fetchVarData(localST, node -> ch -> tn -> lex);
		if(curr == NULL) {
			fprintf(stderr, 
			"The parameter %s is not declared.\n", node -> ch -> tn -> lex);
			return 0;
		}
		if(tmp -> dataType != curr -> dataType)
			return 0;
		if(tmp -> dataType == AST_TYPE_ARRAY) {

			if(tmp -> sdt -> dataType != curr -> sdt -> dataType)
				return 0;
			if(strcmp(tmp -> sdt -> lowId, "") == 0 && strcmp(tmp -> sdt -> highId, "") == 0)
				if(strcmp(curr -> sdt -> lowId, "") == 0 && strcmp(curr -> sdt -> highId, "") == 0) {
					if(tmp -> sdt -> low != curr -> sdt -> low)
						return 0;
					if(tmp -> sdt -> high != curr -> sdt -> high)
						return 0;	
				}
		}
		node = node -> ch -> next;
		tmp = next(linkedlisy)
	}
	if(tmp == NULL && node == NULL)
		return 1;
	return 0;
}

void traverseAST(ASTNode * curr, char * fname) {

	switch(curr -> type) {
		case AST_NODE_PROGRAM: {
			ASTNode * ch = curr -> child;
			/* Replace loop by traverseChildren(ch) ? */
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULEDECLARATION: {
			ASTNode * ch = curr -> child;
			/* Use traverseChildren(ch)? */
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode * ch = curr -> child;
			/* Use traverseChildren(ch)? */
			traverseChildren(cf, fname);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode * ch = curr -> child;
			SymTableFunc * tmp;
			char * name;
			/* Use traverseChildren(ch)? */
			while(ch != NULL) {
				if(ch -> prev == NULL) {
					traverseAST(ch, fname);
					tmp = ch -> localST;
					strcpy(name, ch -> tn -> lex);
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
			ASTNode * ch = curr -> child;
			/* Use traverseChildren(ch)? */
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_OUTPUTLIST: {
			ASTNode * ch = curr -> child;
			/* Use traverseChildren(ch)? */
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_ARRAY: {
			ASTNode * ch = curr -> child;
			traverseAST(ch, fname);
			curr -> dataType -> is_static = ch -> rangeArrays -> is_static;
			ch = ch -> next;
			if(ch -> leaf -> type == AST_LEAF_INT)
				curr -> dataType -> type = AST_TYPE_INT;
			else if(ch -> leaf -> type == AST_LEAF_RNUM)
				curr -> dataType -> type = AST_TYPE_REAL;
			else if(ch -> leaf -> type == AST_LEAF_BOOL)
				curr -> dataType -> type = AST_TYPE_BOOL;
		}
		break;

		case AST_NODE_RANGEARRAYS: {
			ASTNode * ch1 = curr -> child;
			ASTNode * ch2 = ch -> next;
			
			if(ch1 -> leaf -> type == AST_LEAF_IDXNUM && ch2 -> leaf -> type == AST_LEAF_IDXNUM)
				curr -> rangeArrays -> is_static = 1;
			else
				curr -> rangeArrays -> is_static = 0;
		}
		break;

		case AST_NODE_STATEMENT: {
			ASTNode * ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_IO: {
			ASTNode * ch = curr -> child;			
			if(curr -> nodeData.io -> type == AST_IO_GETVAL) {
				SymTableVar* tmp = fetchVarData(localST, ch -> tn -> lex);
				if(tmp == NULL) {
					fprintf(stderr, 
					"The variable taken as input is not being declared.\n");
				}
				else {
					tmp -> isAssigned = 1;
				}
			}
			else {
				if(ch -> type == AST_LEAF_ID) {
					SymTableVar* tmp = fetchVarData(localST, ch -> tn -> lex);
					if(tmp == NULL) {
						fprintf(stderr, 
						"The variable taken as input is not being declared.\n");
					}
					else if(ch -> next != NULL && tmp -> dataType != AST_TYPE_ARRAY) {
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
			ASTNode * ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_ASSIGN: {
			ASTNode * ch = curr -> child;
			SymTableVar* tmp = fetchVarData(localST, ch -> tn -> lex);
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
			ASTNode * ch = curr -> child;
			SymTableFunc * tmp = fetchFuncData(globalST, ch -> next -> tn -> lex);
			if(strcmp(fname, tmp -> name) == 0) {
				fprintf(stderr, 
				"Recursion is not supported.\n");
			}
			if(!listTypeMatch(tmp -> output_plist, ch, localST)) {
				fprintf(stderr, 
				"Output list type mismatch.\n");	
			}
			
			/* searching the idList in case 38, optioanal may be NULL */
			ch = ch -> next;
			while(ch -> type != AST_NODE_IDLIST)
				ch = ch -> next;
			
			if(!listTypeMatch(tmp -> input_plist, ch, localST)) {
				fprintf(stderr, 
				"Input list type mismatch.\n");	
			}
		}
		break;

		case AST_NODE_IDLIST: {
			/* no need */
		}
		break;

		case AST_NODE_EXPR: {
			/* no need */
		}
		break;

		case AST_NODE_AOBEXPR: {
			ch -> localST = curr -> localST;
			ch -> next -> next -> localST = curr -> localST;
			traverseAST(ch, fname);
			traverseAST(ch -> next -> next, fname);
			astDataType tl, tr;
			ASTNode * ch = curr -> child;
			tl = ch -> nodeData -> dataType;
			tr = (ch -> next -> next) -> nodeData -> dataType;
			if((ch -> next) -> nodeData -> op == AST_AOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch in the expression.\n");
				}
				else if(tl == AST_TYPE_ARRAY) {
					fprintf(stderr, 
					"Array type variables in arithmetic operation.\n");		
				}
				else if(tl == AST_TYPE_BOOL) {
					fprintf(stderr, 
					"Bool type variables in arithmetic operation.\n");	
				}
				else 
					curr -> dataType = tl;
			}
			else if((ch -> next) -> nodeData -> op == AST_RELOP) {
				if(tl != tr) {
					fprintf(stderr, 
					"Type mismatch in the expression.\n");	
				}
				else if(tl == AST_TYPE_ARRAY) {
					fprintf(stderr, 
					"Array type variables in relational operation.\n");		
				}
				else if(tl == AST_TYPE_BOOL) {
					fprintf(stderr, 
					"Bool type variables in relational operation.\n");	
				}
				curr -> dataType = AST_TYPE_BOOL;
			}
			else if((ch -> next) -> nodeData -> op == AST_LOP) {
				if(tl != AST_TYPE_BOOL) {
					fprintf(stderr, 
					"Left operator of LOP is not boolean type.\n");		
				}
				if(tr != AST_TYPE_BOOL) {
					fprintf(stderr, 
					"Right operator of LOP is not boolean type.\n");	
				}
				curr -> dataType = AST_TYPE_BOOL;
			}
		}
		break;

		case AST_NODE_DECLARESTMT: {
			ASTNode * ch = curr -> child;
			ch -> next -> localST = curr -> localST;
			traverseAST(ch -> next, fname);
			ASTNode * tmp = ch;
			while(tmp != NULL) {

				ASTNode idNode = tmp -> child;
				if(ch -> next -> type = AST_TYPE_ARRAY) {
					ASTNode * lft = (ch -> next) -> child -> child;
					ASTNode * right = lft -> next; 
					astDataType t = (ch -> next) -> child -> next -> dataType;
					addArrToFunction(localST, idNode -> nodeData -> tn -> lex, lft, right, t);
				}
				else {
					addDataToFunction(localST, idNode -> nodeData -> tn -> lex, ch -> next -> nodeData -> dataType);
				}
				tmp = tmp -> child;
				tmp = tmp -> next;
			}
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode * ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			if(ch -> nodeData -> dataType == AST_TYPE_REAL) {
				fprintf(stderr, 
				"switch variable is of real type.\n");
				return;
			}

			SymTableFunc * newST = getFuncTable(fname);
			ASTNode * ch1 = ch -> next;
			ch1 -> localST = newST;
			ch1 -> dataType = ch -> nodeData -> dataType;
			strcpy(ch1 -> switchVar, ch -> nodeData -> tn -> lex);
			traverseAST(ch1, fname);

			ASTNode * ch2 = ch1 -> next;
			if(ch -> nodeData -> dataType == AST_TYPE_BOOL) {
				if(ch2 != NULL) {
					fprintf(stderr, 
					"Default case in bool type.\n");
				}
			}
			else if(ch -> nodeData -> dataType == AST_TYPE_INT) {
				if(ch2 == NULL) {
					fprintf(stderr, 
					"Default case not present in int type.\n");
				}
				else {
					ch2 -> localST = newST;
					ch2 -> dataType = ch -> nodeData -> dataType;
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
			ASTNode * ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);

			ch = ch -> next;
			ch -> localST = curr -> localST;
			ch -> dataType = curr -> dataType;
			strcpy(ch -> switchVar, curr -> switchVar);
			traverseAST(ch, fname);
		}
		break;

		case AST_NODE_UNARY: {
			ASTNode * ch = curr -> child;
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			ASTNode * ch = curr -> child;
			SymTableVar* tmp = fetchVarData(localST, ch -> tn -> lex);
			if(tmp == NULL) {
				fprintf(stderr, 
				"The variable taken as input is not being declared.\n");
			}
			else if(ch -> next != NULL && tmp -> dataType != AST_TYPE_ARRAY) {
				fprintf(stderr, 
				"A non array type variable access using whichId\n");	
			}
			else if(ch -> next != NULL) {
				boundChecking(tmp, curr);
			}
			ch = ch -> next;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode * ch = curr -> child;
			ch -> localST = curr -> localST;
			traverseAST(ch, fname);
			if(ch -> nodeData -> dataType != AST_TYPE_INT) {
				fprintf(stderr, 
				"For loop variable is not of int type.\n");
				return;
			}

			SymTableFunc * newST = getFuncTable(fname);
			ASTNode * ch1 = ch -> next;
			ch1 -> localST = newST;
			traverseAST(ch1, fname);

			ASTNode * ch2 = ch1 -> next;
			ch2 -> localST = newST;
			traverseAST(ch2, fname);
		}
		break;

		case AST_NODE_VARIDNUM: {
			ASTNode * ch = curr -> child;
			traverseChildren(ch, fname);
		}
		break;

		case AST_NODE_LEAF: {
			/* 
				For ID: (As in ast.c)
				CASE: 3, 7, 10, 13, 16, 17, 18 
			*/
			switch(curr -> nodeData -> type) {
				case AST_LEAF_INT: {
					curr -> nodeData -> dataType = AST_TYPE_INT;
					return;
				}
				case AST_LEAF_RNUM: {
					curr -> nodeData -> dataType = AST_TYPE_REAL;
					return;	
				}
				case AST_LEAF_BOOL: {
					curr -> nodeData -> dataType = AST_TYPE_BOOL;
					return;	
				}
				case AST_LEAF_ID: {
					char str[30];
					strcpy(str, curr -> tn -> lex);
					switch(curr -> parent -> type) {
						case AST_NODE_MODULEDECLARATION: {
							insertFuncRecord(str);
							return;
						}
						case AST_NODE_MODULE: {
							SymTableFunc * tmp = fetchFuncData(str);
							if(tmp != NULL && tmp -> isDeclared == 1) {
								fprintf(stderr, 
								"Redundant declaretion of the finction.\n");
							}
							if(tmp == NULL)
								tmp = insertFuncRecord(str);
							insertinputplist();
							insertoutputplist();
						}
						
					}
				}
				case AST_LEAF_IDXNUM: {
					curr -> nodeData -> type = AST_TYPE_INT;
					return;
				}
				case AST_LEAF_IDXID: {
					
				}
				AST_LEAF_PLUS,
				AST_LEAF_MINUS,
				AST_LEAF_MUL,
				AST_LEAF_DIV,
				AST_LEAF_OR,
				AST_LEAF_AND,
				AST_LEAF_LT,
				AST_LEAF_LE,
				AST_LEAF_GT,
				AST_LEAF_GE,
				AST_LEAF_EQ,
				AST_LEAF_NE,
				AST_LEAF_TRUE,
				AST_LEAF_FALSE,
				AST_LEAF_VALNUM,
				AST_LEAF_VALTRUE,
				AST_LEAF_VALFALSE,
				AST_LEAF_VARIDNUM_NUM,
				AST_LEAF_VARIDNUM_ID,
				AST_LEAF_VARIDNUM_RNUM,
				AST_LEAF_BOOLTRUE,
				AST_LEAF_BOOLFALSE,
				AST_LEAF_UOPPLUS,
				AST_LEAF_UOPMINUS
			}
		}
		break;

		default:
		/*
			1. Add function name
			2. Add variables
			3. Add Input Params
			4. Add Output Params
		*/
	}
}