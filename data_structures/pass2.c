#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "st.h"
#include "ast.h"
#include "pass1.h"

void pass2Children(ASTNode * head, char * fname) {
	
	ASTNode* ch = head;
	while(ch != NULL) {
		pass2AST(ch, fname);
		ch = ch -> next;
	}
}

void pass2AST(ASTNode* curr, char* fname) {
	
	switch(curr -> type) {
		case AST_NODE_PROGRAM: {
			ASTNode* ch = curr -> child;
			pass2Children(ch, fname);
		}
		break;

		case AST_NODE_MODULEDECLARATION: {
			ASTNode* ch = curr -> child;
			pass2Children(ch, fname);
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.moduleList -> type == AST_MODULE_DRIVER) {
				if(ch == NULL)
					return;
				pass2AST(ch, "driver");
			}
			else
				pass2Children(ch, fname);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			pass2Children(ch, fname);
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
			/* do nothing */
		}
		break;

		case AST_NODE_RANGEARRAYS: {
			/* do nothing */
		}
		break;

		case AST_NODE_STATEMENT: {
			ASTNode* ch = curr -> child;
			pass2Children(ch, fname);
		}
		break;

		case AST_NODE_IO: {
			/* do nothing */
			if(curr -> nodeData.io -> type == AST_IO_GETVAL) {
				ASTNode * ch = curr -> child;
				if(lookupDependentVar(curr -> localST, ch -> nodeData.leaf -> tn -> lex)) {
					fprintf(stderr, 
					"For loop variable '%s' re-assigned using get_value on line %d.\n", 
					ch -> nodeData.leaf -> tn -> lex,
					ch -> nodeData.leaf -> tn -> line_num);
				}
			}
		}
		break;

		case AST_NODE_SIMPLESTMT: {
			ASTNode* ch = curr -> child;
			pass2Children(ch, fname);
		}
		break;

		case AST_NODE_ASSIGN: {
			/* nothing needed */
			ASTNode * ch = curr -> child;
			if(lookupDependentVar(curr -> localST, ch -> nodeData.leaf -> tn -> lex)) {
				fprintf(stderr, 
				"For loop variable '%s' re-assigned on line %d.\n", 
				ch -> nodeData.leaf -> tn -> lex,
				ch -> nodeData.leaf -> tn -> line_num);
			}
		}
		break;
		
		case AST_NODE_MODULEREUSE: {
			ASTNode* ch = curr -> child;
			if(ch -> type == AST_NODE_IDLIST)
				ch = ch -> next;
			int line_num = ch -> nodeData.leaf -> tn -> line_num;
			SymTableFunc* tmp = fetchFuncData(ch -> nodeData.leaf -> tn -> lex);
			if(tmp == NULL) {
				return;
			}
			if(strcmp(fname, tmp -> name) == 0) {
				return;
			}

			ASTNode * ch2 = curr -> child;
			if(ch2 -> type == AST_NODE_IDLIST) {
				while(ch2 != NULL) {
					char str[30];
					strcpy(str, ch2 -> child -> nodeData.leaf -> tn -> lex);
					if(lookupDependentVar(curr -> localST, str)) {
						fprintf(stderr, 
						"For loop variable '%s' re-assigned using moduleReuse on line %d.\n", 
						str,
						ch2 -> child -> nodeData.leaf -> tn -> line_num);
					}
					ch2 = ch2 -> child -> next;
				}
			}

			/* To be done in pass2 if the function is not defined. */
			if(curr -> nodeData.moduleReuse -> listCheck)
				return;
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
				"Number of input parameters mismatch name : %s on line %d.\n", tmp -> name, line_num);
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
			/* no need */
		}
		break;

		case AST_NODE_DECLARESTMT: {
			/* no need */
			ASTNode* ch = curr -> child;
			ASTNode* tmp = ch;
			while(tmp != NULL) {
				ASTNode* idNode = tmp -> child;
				if(lookupDependentVar(curr -> localST, idNode -> nodeData.leaf -> tn -> lex)) {
					fprintf(stderr, 
					"Dependent variable '%s' declared on line %d.\n",
					idNode -> nodeData.leaf -> tn -> lex,
					idNode -> nodeData.leaf -> tn -> line_num);
				}
				tmp = tmp -> child;
				tmp = tmp -> next;
			}
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode* ch = curr -> child;
			SymTableVar* idx = fetchVarData(curr -> localST, ch -> nodeData.leaf -> tn -> lex);
			if(idx == NULL) {
				return;
			}
			
			if((ch -> nodeData).leaf -> dataType == AST_TYPE_REAL) {
				return;
			}
			ASTNode* ch1 = ch -> next;
			ASTNode* ch2 = ch1 -> next;
			strcpy(ch1 -> localST -> dependentVar, (ch -> nodeData).leaf -> tn -> lex);
			ch1 -> localST -> scope = SCOPE_COND;
			pass2AST(ch1, fname);
			if(ch2 == NULL) {
				return;
			}
			pass2AST(ch2, fname);
		}
		break;
		
		case AST_NODE_CASESTMT: {
			ASTNode* ch = curr -> child;
			astDataType t = ch -> nodeData.leaf -> dataType;
			SymTableVar * v = fetchVarData(curr -> localST, curr -> localST -> dependentVar);
			if(t != v -> dataType) {
				fprintf(stderr, 
				"Case value doen't match the switch variable type on line %d.\n", ch -> nodeData.leaf -> tn -> line_num);
			}
			ch = ch -> next;
			if(ch == NULL)
				return;
			pass2AST(ch, fname);

			ch = ch -> next;
			if(ch == NULL) {
				return;
			}
			pass2AST(ch, fname);
		}
		break;

		case AST_NODE_UNARY: {
			ASTNode* ch = curr -> child;
			ch = ch -> next;
			pass2AST(ch, fname);
		}
		break;
		
		case AST_NODE_LVALARRSTMT: {
			/* nothing needed */
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode* ch = curr -> child;
			pass2AST(ch, fname);
			ch = curr -> child;
			if(ch -> nodeData.leaf -> dataType != AST_TYPE_INT) {
				return;
			}

			ASTNode* ch1 = ch -> next;
			if(curr -> nodeData.iterStmt -> type == AST_ITER_FOR) {
				strcpy(ch1 -> localST -> dependentVar, (ch -> nodeData).leaf -> tn -> lex);
				ch1 -> localST -> scope = SCOPE_FOR;
			}
			if(ch1 == NULL) {
				return;
			}
			pass2AST(ch1, fname);

			ASTNode * ch2 = ch1 -> next;
			if(ch2 == NULL) {
				return;
			}
			pass2AST(ch2, fname);
		}
		break;

		case AST_NODE_VARIDNUM: {
			/* no need */
		}
		break;

		case AST_NODE_LEAF: {
			/* no need */
		}
		break;
		default: {
			fprintf(stderr, "Default error!\n");
		}
	}
}