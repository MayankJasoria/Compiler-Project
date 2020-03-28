#include "astDef.h"
#include "n_ary_tree.h"

/**
 * @see ast.h
 */
ASTNode* getASTNode(astNodeData nodeData, astNodeType t) {
	ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));

	/* define all pointers as NULL */
	node -> parent = NULL;
	node -> child = NULL;
	node -> next = NULL;
	node -> prev = NULL;
    
    node -> type = t;
	node -> nodeData = nodeData;

	return node;
}

/**
 * Assumption: child's 'child' pointer need not be tampered with:
 * It has its own subtree
 * @see ast.h
 */
ASTNode* addChild(ASTNode* parent, ASTNode* child) {
	if(parent->child == NULL) {
		/* no children yet, add first child to parent */
		parent -> child = child;
		child -> parent = parent;
		child -> prev = NULL;
		child->next = NULL;
	} else {
		/* some child exists, consider that child too */
		child -> next = parent -> child;
		parent -> child -> prev = child;
		parent -> child = child;
		child -> parent = parent;
	}
	return parent;
}


/* Parse tree node: PT (global) */
    /* High level logic */

//  typedef struct treeNode {
// 	symbol sym;
// 	typeOfSymbol tag;
// 	int rule_num;
// 	int line_num;
// 	union {
// 		int val_int;
// 		float val_float;
// 	} value;
// 	char lex[25];
// 	int depth;
// 	int id;
// 	struct treeNode * parent;
// 	struct treeNode * prev;
// 	struct treeNode * next;
// 	struct treeNode * child;
// 	token * tok;
// 	boolean isLeaf;
// } treeNode;

/* -- Template for writing logic -- 
    ASTNode* ast(treeNode * curr, ASTNode* parent, ASTNode* prev_sibling) {

    ASTNode* ret ;

    // first ever call: NULL 
    // subsequent calls:
    ASTNode* ret = malloc();
    // assign whatever needed for inheritance 

    ASTNode * p1 = ast(curr->child, ret, NULL);
    ASTNode * p2 = ast(curr->child->next, ret, stmt);

    addChild (ret, p1, p2);
    // assign whatever needed for synthesis 
    
    return p1;
}
*/
ASTNode* constructAST(ASTNode* parent, ASTNode* prev_sibling, treeNode * tn) {
	
    treeNode * ch = tn -> child;
	switch (tn -> rule_num) {
		case 0: // program : moduleDeclarations otherModules driverModule otherModules
            programNode* progNode = (programNode*) malloc(sizeof(programNode));
			astNodeData nodeData;			
            nodeData.program = progNode;
            ASTNode* curr = getASTNode(nodeData, AST_NODE_PROGRAM);
    
            /* Call siblings one by one */
                        ASTNode* md = constructAST(curr, NULL, ch);
            ASTNode* om1 = constructAST(curr, md, ch -> next);
            ASTNode* dm = constructAST(om1, md, ch -> next -> next);
            ASTNode* om2 = constructAST(dm, md, ch -> next -> next -> next);
            
            addChild(curr, om2);
            addChild(curr, dm);
            addChild(curr, om1);
            addChild(curr, md); 
            return curr;
            
            break;
        case 1: // moduleDeclarations : moduleDeclaration moduleDeclarations1
            moduleDeclationNode * mdNode = (moduleDeclaration *) malloc(sizeof(moduleDecarationNode));
            astNodeData nodeData;
            nodeData.moduleDeclaration = mdNode;
            ASTNode * curr = getASTNode(mdNode, AST_NODE_MODULEDECLARATION);
            
			break;
		case 2: // moduleDeclarations : EMPTY
			break;
		case 3: // moduleDeclaration : DECLARE MODULE ID SEMICOL
			break;
		case 4: // otherModules : module otherModules1
			break;
		case 5: // otherModules : EMPTY
			break;
		case 6: // driverModule : DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
			break;
		case 7: // module : DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
			break;
		case 8: // ret : RETURNS SQBO output_plist SQBC SEMICOL
			break;
		case 9: // ret : EMPTY
			break;
		case 10: // input_plist : ID COLON dataType n1
			break;
		case 11: // n1 : COMMA ID COLON dataType n11
			break;
		case 12: // n1 : EMPTY
			break;
		case 13: // output_plist : ID COLON type n2
			break;
		case 14: // n2 : COMMA ID COLON type n21
			break;
		case 15: // n2 : EMPTY
			break;
		case 16: // type : INTEGER
			break;
		case 17: // type : REAL
			break;
		case 18: // type : BOOLEAN
			break;
		case 19: // dataType : type
			break;
		case 20: // dataType : ARRAY SQBO range_arrays SQBC OF type
			break;
		case 21: // moduleDef : START statements END
			break;
		case 22: // statements : statement statements1
			break;
		case 23: // statements : EMPTY
			break;
		case 24: // statement : ioStmt
			break;
		case 25: // statement : simpleStmt
			break;
		case 26: // statement : declareStmt
			break;
		case 27: // statement : condionalStmt
			break;
		case 28: // statement : iterativeStmt
			break;
		case 29: // ioStmt : GET_VALUE BO ID BC SEMICOL
			break;
		case 30: //ioStmt  : PRINT BO var BC SEMICOL
			break;
		case 31: // whichId : SQBO index SQBC
			break;
		case 32: // whichId : EMPTY
			break;
		case 33: // index : NUM
			break;
		case 34: // index : ID
			break;
		case 35: // simpleStmt : assignmentStmt
			break;
		case 36: // simpleStmt : moduleReuseStmt
			break;
		case 37: // assignmentStmt : ID whichStmt
			break;
		case 38: //moduleReuseStmt : optional USE MODULE ID WITH PARAMETERS idList SEMICOL
			break;
		case 39: // optional : SQBO idList SQBC ASSIGNOP
			break;
		case 40: // optional : EMPTY
			break;
		case 41: // idList : ID n3
			break;
		case 42: // n3 : COMMA ID n31
			break;
		case 43: // n3 : EMPTY
			break;
		case 44: // expression : arithmeticOrBooleanExpr 
			break;
		case 45: // expression : u
			break;
		case 46: // arithmeticOrBooleanExpr : anyTerm n7
			break;
		case 47: // n7 : logicalOp anyTerm n7
			break;
		case 48: // n7 : EMPTY
			break;
		case 49:c // anyTerm : arithmeticExpr n8
			break;
		case 50: // anyTerm : boolConstt
			break;
		case 51: // n8 : relationalOp arithmeticExpr
			break;
		case 52: // n8 : EMPTY 
			break;
		case 53: // arithmeticExpr : term n4
			break;
		case 54: // n4 : op1 term n4
			break;
		case 55: // n4 : EMPTY
			break;
		case 56: // term : factor n5
			break;
		default:
	}
}

