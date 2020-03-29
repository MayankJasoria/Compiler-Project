#include "astDef.h"
#include "n_ary_tree.h"

/**
 * @see ast.h
 */
ASTNode* getASTNode(astNodeData nodeData, astNodeType t) {
	ASNode* node = (ASTNode*) malloc(sizeof(ASTNode));

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

	if(child == NULL)
		return parent;
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

/** 
 * TODO: call free() to release memory for undesired nodes
 * (NOTE: not defined in header file, as this function need not be externally visible)
 * Finds the node for the corresponding non terminal among a set of siblings in the parse tree
 * @param curr	The current node among siblings of the parse tree
 * @param nt	THe required non terminal
 * 
 * @return The node corresponding to the required non terminal
 */
treeNode * findinPT(treeNode * curr, nonterminal nt) {

	treeNode * tmp = curr;
	while(tmp != NULL) {
		if(tmp -> sym.NT == nt)
			return tmp;
		tmp = tmp -> next;
	}
	return NULL;
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
            
			/* add siblings in reverse order, to regenerate correct order */
            addChild(curr, om2);
            addChild(curr, dm);
            addChild(curr, om1);
            addChild(curr, md);
			curr -> type = AST_NODE_PROGRAM;	
            return curr;
            break;
			
        case 1: // moduleDeclarations : moduleDeclaration moduleDeclarations1
            moduleDeclarationNode * mdNode = (moduleDeclarationNode *) malloc(sizeof(moduleDeclarationNode));
            astNodeData nodeData;
            nodeData.moduleDeclaration = mdNode;
            ASTNode * curr = getASTNode(nodeData, AST_NODE_MODULEDECLARATION);
            
            ASTNode * md = constructAST(curr, NULL, ch);
            ASTNode * mds = constructAST(curr, md, ch -> next);

			addChild(curr, mds);
			addChild(curr, md);
			curr -> type = AST_NODE_MODULEDECLARATION;
			return curr;
			break;
			
		case 2: // moduleDeclarations : EMPTY
			return NULL;
			break;
            
		case 3: // moduleDeclaration : DECLARE MODULE ID SEMICOL
			/* syn leaf to top */
			return constructAST(parent, NULL, ch -> next -> next);
			break;
            
		case 4: // otherModules : module otherModules
            
			moduleListNode* omNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			omNode -> type = AST_MODULE_OTHER;
            astNodeData nodeData;
            nodeData.moduleList = omNode;
            ASTNode * curr = getASTNode(nodeData, AST_NODE_MODULELIST);
			ASTNode * mod = constructAST(curr, NULL, ch);
			ASTNode * om1 = constructAST(curr, mod, ch -> next);
			
			addChild(curr, om1);
			addChild(curr, mod);
			curr -> type = AST_NODE_MODULELIST;
			return curr;
			break;

		case 5: // otherModules : EMPTY
            return NULL;
			break;
            
		case 6: // driverModule : DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
            
			moduleListNode * driverNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			driverNode -> type = AST_MODULE_DRIVER;
            astNodeData nodeData;
            nodeData.moduleList = driverNode;
            ASTNode * curr = getASTNode(nodeData, AST_NODE_MODULELIST); 

            ASTNode * modDef = constructAST(curr, NULL, findinPT(ch, moduledef));

            addChild(curr, modDef);
			curr -> type = AST_NODE_MODULELIST;
            return curr;
			break;

		case 7: // module : DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
		
			moduleListNode* modNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			modNode -> type = AST_MODULE_OTHER;
            astNodeData nodeData;
            nodeData.moduleList = modNode;
            ASTNode * curr = getASTNode(nodeData, AST_NODE_MODULELIST);
			ASTNode * idNode = constructAST(curr, NULL, ch -> next -> next);
			ch = findinPT(ch, input_plist);
			ASTNode * inplist = constructAST(curr, idNode, ch);
			ch = findinPT(ch, ret);
			ASTNode * retNode = constructAST(curr, inplist, ch);
			ch = findinPT(ch, moduledef);
			ASTNode * defNode = constructAST(curr, retNode, ch);
			
			addChild(curr, defNode);
			addChild(curr, retNode);
			addChild(curr, inplist);
			addChild(curr, idNode);

			curr -> type = AST_NODE_MODULELIST;
			return curr;
			break;
			
		case 8: // ret : RETURNS SQBO output_plist SQBC SEMICOL
			ch = findinPT(ch, output_plist);
			return constructAST(parent, NULL, ch);
			break;
			
		case 9: // ret : EMPTY
			return NULL;
			break;

		case 10: // input_plist : ID COLON dataType n1 (input_plistnew)
			inputListNode * inNode = (inputListNode *) malloc(sizeof(inputListNode));
			astNodeData nodeData;
			nodeData.inputList = inNode;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_INPUTLIST);
			ASTNode * idNode = constructAST(curr, NULL, ch);
			ch = findinPT(ch, datatype);
			ASTNode * typeNode = constructAST(curr, idNode, ch);
			ch = findinPT(ch, input_plistnew);
			ASTNode * inList = constructAST(curr, typeNode, ch);
			/* remember: during the constructAST we have not created the previous links from siblings */ 
			
			addChild(curr, inList);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			curr -> type = AST_NODE_INPUTLIST;
			return curr;
			break;

		case 11: // n1 : COMMA ID COLON dataType n11
			inputListNode * inNode = (inputListNode *) malloc(sizeof(inputListNode));
			astNodeData nodeData;
			nodeData.inputList = inNode;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_INPUTLIST);
			ASTNode * idNode = constructAST(curr, NULL, ch -> next);
			ch = findinPT(ch, datatype);
			ASTNode* typeNode = constructAST(curr, idNode, ch);
			ch = findinPT(ch, input_plistnew);
			ASTNode* n11 = constructAST(curr, typeNode, ch);
			
			addChild(curr, n11);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			curr -> type = AST_NODE_INPUTLIST;
			return curr;
			break;
			
		case 12: // n1 : EMPTY
			return NULL;
			break;

		case 13: // output_plist : ID COLON type n2 (output_plistnew)
			outputListNode * outNode = (outputListNode *) malloc(sizeof(outputListNode));
			astNodeData nodeData;
			nodeData.outputList = outNode;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_OUTPUTLIST);
			ASTNode * idNode = constructAST(curr, NULL, ch);

			ch = findinPT(ch, type);
			ASTNode * typeNode = constructAST(curr, idNode, ch);

			ch = findinPT(ch, output_plistnew);
			ASTNode * outList = constructAST(curr, typeNode, ch);

			/* remember: during the constructAST we have not created the previous links from siblings */ 
			addChild(curr, outList);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			curr -> type = AST_NODE_OUTPUTLIST;
			return curr;
			break;

		case 14: // n2 : COMMA ID COLON type n21 (output_plistnew)
			outputListNode * outNode = (outputListNode *) malloc(sizeof(outputListNode));
			astNodeData nodeData;
			nodeData.outputList = outNode;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_OUTPUTLIST);
			ASTNode * idNode = constructAST(curr, NULL, ch -> next);
			
			ch = findinPT(ch, type);
			ASTNode* typeNode = constructAST(curr, idNode, ch);
			
			ch = findinPT(ch->next, output_plistnew);
			ASTNode* n21 = constructAST(curr, typeNode, ch);

			addChild(curr, n21);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			curr -> type = AST_NODE_OUTPUTLIST;
			return curr;
			break;

		case 15: // n2 : EMPTY
			return NULL;
			break;

		case 16: // type : INTEGER
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = tn;
			lf -> tag = AST_LEAF_INT;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
			
		case 17: // type : REAL
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = tn;
			lf -> tag = AST_LEAF_RNUM;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;

		case 18: // type : BOOLEAN
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = tn;
			lf -> tag = AST_LEAF_BOOL;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;

		case 19: // dataType : type
			return constructAST(curr, NULL, ch); // directly propagating leaf upwards
			break;
	
		case 20: // dataType : ARRAY SQBO range_arrays SQBC OF type
			dataTypeNode * dtn = (dataTypeNode *) malloc(sizeof(dataTypeNode));
			astNodeData nodeData;
			nodeData.dataType = dtn;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_ARRAY);
			ch = findinPT(ch, range_arrays);
			ASTNode * rangeNode = constructAST(curr, NULL, ch);
			ch = findinPT(ch, type);
			ASTNode * typeNode = constructAST(curr, rangeNode, ch);

			addChild(curr, typeNode);
			addChild(curr, rangeNode);
			curr -> type = AST_NODE_ARRAY;
			return curr;
			break;

		case 21: // moduleDef : START statements END
			return constructAST(parent, NULL, ch -> next);
			break;

		/* CHECK @ everything is ASTNode type, so we don't need a separate type for the AST_NODE_STATEMENT */
		case 22: // statements : statement statements1
			statementNode * sn = (statementNode *) malloc(sizeof(statementNode));
			astNodeData nodeData;
			nodeData.dataType = sn;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_STATEMENT);
			ASTNode * stmtNode = constructAST(curr, NULL, ch);
			ASTNode * stmtsNode = constructAST(curr, NULL, ch -> next);
		
			addChild(curr, stmtsNode);
			addChild(curr, stmtNode);

			curr -> type = AST_NODE_STATEMENT
		
		
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
		case 42: // n3 : COMMA ID n3
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
		case 57: // n5 : op2 factor n5
			break;
		case 58: // n5 : EMPTY
			break;
		case 59: // factor : BO arithmeticOrBooleanExpr BC
			break;
		case 60: // factor : var_id_num
			break;
		case 61: // var : var_id_num
			break;
		case 62: // var : boolConstt
			break;
		case 63: // op1 : PLUS
			break;
		case 64: // op1 : MINUS
			break;
		case 65: // op2 : MUL
			break;
		case 66: // op2 : DIV
			break;
		case 67: // logicalOp : AND
			break;
		case 68: // logicalOp : OR
			break;
		case 69: // relationalOp : LT
			break;
		case 70: // relationalOp : LE
			break;
		case 71: // relationalOp : GT
			break;
		case 72: // relationalOp : GE
			break;
		case 73: // relationalOp : EQ
			break;
		case 74: // relationalOp : NE
			break;
		case 75: // declareStmt : DECLARE idList COLON dataType SEMICOL
			break;
		case 76: // condionalStmt : SWITCH BO ID BC START caseStmts default END
			break;
		case 77: // caseStmts : CASE value COLON statements BREAK SEMICOL n9
			break;
		case 78: // n9 : CASE value COLON statements BREAK SEMICOL n9
			break;
		case 79: // n9 : EMPTY
			break;
		case 80: // value : NUM
			break;
		case 81: // value : TRUE
			break;
		case 82: // value : FALSE
			break;
		case 83: // default : DEFAULT COLON statements BREAK SEMICOL
			break;
		case 84: // default : EMPTY
			break;
		case 85: // iterativeStmt : FOR BO ID IN range BC START statements END
			break;
		case 86: // iterativeStmt : WHILE BO arithmeticOrBooleanExpr BC START statements END
			break;
		case 87: // range : NUM RANGEOP NUM
			break;
		case 88: // range_arrays : index RANGEOP index
			break;
		case 89: // boolConstt : TRUE
			break;
		case 90: // boolConstt : FALSE
			break;
		case 91: // var_id_num : ID whichId
			break;
		case 92: // var_id_num : NUM
			break;
		case 93: // var_id_num : RNUM
			break;
		case 94: // whichStmt : lvalueIDStmt
			break;
		case 95: // whichStmt : lvalueARRStmt
			break;
		case 96: // lvalueIDStmt : ASSIGNOP expression SEMICOL
			break;
		case 97: // lvalueARRStmt : SQBO index SQBC ASSIGNOP expression SEMICOL
			break;
		case 98: // u : unary_op new_NT
			break;
		case 99: // unary_op : PLUS
			break;
		case 100: // unary_op : MINUS
			break;
		case 101: // new_NT : BO arithmeticExpr BC
			break;
		case 102: // new_NT : var_id_num
			break;
		default:
	}
}

