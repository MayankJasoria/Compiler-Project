#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "symbol_table.h"

void traverseChildren(ASTNode* head) {
	ASTNode* ch = head;
	while(ch != NULL) {
		ch -> localST = curr -> localST;
		traverseAST(ch);
		ch = ch -> next;
	}
}

void traverseAST(ASTNode * curr) {

	switch(curr -> type) {

		case AST_NODE_PROGRAM: {
			
			ASTNode * ch = curr -> child;
			/* Replace loop by traverseChildren(ch) ? */
			traverseChildren(ch);
		}
		break;

		case AST_NODE_MODULEDECLARATION: {

			ASTNode * ch = curr -> child;

			/* Use traverseChildren(ch)? */
			traverseChildren(ch);
		}
		break;

		case AST_NODE_MODULELIST: {
			
			ASTNode * ch = curr -> child;

			/* Use traverseChildren(ch)? */
			traverseChildren(ch);
		}
		break;

		case AST_NODE_MODULE: {
			 
			ASTNode * ch = curr -> child;
			SymTableFunc * tmp;
			/* Use traverseChildren(ch)? */
			while(ch != NULL) {
				if(ch -> prev == NULL) {
					traverseAST(ch);
					tmp = ch -> varST;
				}
				else {
					ch -> varST = tmp;
					traverseAST(ch);
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
			traverseChildren(ch);
		}
		break;

		case AST_NODE_OUTPUTLIST: {

			/** 
			 * TODO: Check correctness
			 */

			ASTNode * ch = curr -> child;
			
			/* Use traverseChildren(ch)? */
			traverseChildren(ch);
		}
		break;

		case AST_NODE_ARRAY: {
		/* 
			Every element of the linked list looks like this:

			typedef struct node {
				void* data;
				struct node* next;
				struct node* prev;
			} Node;
		*/
			
			ASTNode * ch = curr -> child;
			
			traverseAST(ch);
			curr -> dataType->is_static = ch -> rangeArrays->is_static;
			ch = ch -> next;
			//insertVarRecord(SymbolTable st, char* name, int width, int offset, astDataType dataType)
			traverseAST(ch);

		}
		break;

		case AST_NODE_RANGEARRAYS:
		break;

		case AST_NODE_STATEMENT:
		break;

		case AST_NODE_IO:
		break;

		case AST_NODE_SIMPLESTMT:
		break;

		case AST_NODE_ASSIGN:
		break;
		case AST_NODE_WHICHSTMT:
		break;
		case AST_NODE_MODULEREUSE:
		break;
		case AST_NODE_IDLIST:
		break;
		case AST_NODE_EXPR:
		break;
		case AST_NODE_AOBEXPR:
		break;
		case AST_NODE_DECLARESTMT:
		break;
		case AST_NODE_CONDSTMT:
		break;
		case AST_NODE_CASESTMT:
		break;
		case AST_NODE_UNARY:
		break;
		case AST_NODE_LVALARRSTMT:
		break;
		case AST_NODE_ITERSTMT:
		break;
		case AST_NODE_FOR:
		break;
		case AST_NODE_WHILE:
		break;
		case AST_NODE_VARIDNUM:
		break;
		case AST_NODE_LEAF: {
			/* 
				For ID: (As in ast.c)
				CASE: 3, 7, 10, 13 
			*/
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