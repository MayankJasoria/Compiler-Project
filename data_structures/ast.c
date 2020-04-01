/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */

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
treeNode* findinPT(treeNode* curr, nonterminal nt) {

	treeNode* tmp = curr;
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
ASTNode* constructAST(ASTNode* parent, ASTNode* prev_sibling, treeNode* tn) {
	
    treeNode* ch = tn -> child;
    ASTNode* curr;
    astNodeData nodeData;
    leafNode* lf;
	switch (tn -> rule_num) {
		case 0: {// program : moduleDeclarations otherModules driverModule otherModules
				programNode* progNode = (programNode*) malloc(sizeof(programNode));	
				nodeData.program = progNode;
				curr = getASTNode(nodeData, AST_NODE_PROGRAM);
		
				/* Call siblings one by one */
				ASTNode* md = constructAST(curr, NULL, ch);
				ASTNode* om1 = constructAST(curr, md, ch -> next);
				ASTNode* dm = constructAST(curr, om1, ch -> next -> next);
				ASTNode* om2 = constructAST(curr, dm, ch -> next -> next -> next);
				
				/* add siblings in reverse order, to regenerate correct order */
				addChild(curr, om2);
				addChild(curr, dm);
				addChild(curr, om1);
				addChild(curr, md);
				curr -> type = AST_NODE_PROGRAM;	
				return curr;
			}
            
        case 1: {// moduleDeclarations : moduleDeclaration moduleDeclarations1
			moduleDeclarationNode* mdNode = (moduleDeclarationNode *) malloc(sizeof(moduleDeclarationNode));
			nodeData.moduleDeclaration = mdNode;
			curr = getASTNode(nodeData, AST_NODE_MODULEDECLARATION);
			
			ASTNode* md = constructAST(curr, NULL, ch);
			ASTNode* mds = constructAST(curr, md, ch -> next);

			addChild(curr, mds);
			addChild(curr, md);
			return curr;
		}
			
		case 2: {// moduleDeclarations : EMPTY
			return NULL;
		}
            
		case 3: {// moduleDeclaration : DECLARE MODULE ID SEMICOL
			/* syn leaf to top */
			return constructAST(parent, NULL, ch -> next -> next);
		}
			
		case 4: {// otherModules : module otherModules
			moduleListNode* omNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			omNode -> type = AST_MODULE_OTHER;
			nodeData.moduleList = omNode;
			curr = getASTNode(nodeData, AST_NODE_MODULELIST);
			ASTNode* mod = constructAST(curr, NULL, ch);
			ASTNode* om1 = constructAST(curr, mod, ch -> next);
			
			addChild(curr, om1);
			addChild(curr, mod);
			return curr;
		}
			
		case 5: {// otherModules : EMPTY
			return NULL;
		}
            
		case 6: {// driverModule : DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
			moduleListNode* driverNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			driverNode -> type = AST_MODULE_DRIVER;
			nodeData.moduleList = driverNode;
			curr = getASTNode(nodeData, AST_NODE_MODULELIST); 

			ASTNode* modDef = constructAST(curr, NULL, findinPT(ch, moduledef));

			addChild(curr, modDef);
			return curr;
		}

		case 7: {// module : DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
			moduleListNode* modNode = (moduleListNode *) malloc(sizeof(moduleListNode));
			modNode -> type = AST_MODULE_OTHER;
			nodeData.moduleList = modNode;
			curr = getASTNode(nodeData, AST_NODE_MODULELIST);
			ASTNode* idNode = constructAST(curr, NULL, ch -> next -> next);
			ch = findinPT(ch, input_plist);
			ASTNode* inplist = constructAST(curr, idNode, ch);
			ch = findinPT(ch, ret);
			ASTNode* retNode = constructAST(curr, inplist, ch);
			ch = findinPT(ch, moduledef);
			ASTNode* defNode = constructAST(curr, retNode, ch);
			
			addChild(curr, defNode);
			addChild(curr, retNode);
			addChild(curr, inplist);
			addChild(curr, idNode);

			return curr;
		}	
			
		case 8: {// ret : RETURNS SQBO output_plist SQBC SEMICOL
			ch = findinPT(ch, output_plist);
			return constructAST(parent, NULL, ch);
		}
			
		case 9: {// ret : EMPTY
			return NULL;
		}
			
		case 10: {// input_plist : ID COLON dataType n1 (input_plistnew)
			inputListNode* inNode = (inputListNode *) malloc(sizeof(inputListNode));
			nodeData.inputList = inNode;
			curr = getASTNode(nodeData, AST_NODE_INPUTLIST);
			ASTNode* idNode = constructAST(curr, NULL, ch);
			ch = findinPT(ch, datatype);
			ASTNode* typeNode = constructAST(curr, idNode, ch);
			ch = findinPT(ch, input_plistnew);
			ASTNode* inList = constructAST(curr, typeNode, ch);
			/* remember: during the constructAST we have not created the previous links from siblings */ 
			
			addChild(curr, inList);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			return curr;
		}

		case 11: {// n1 : COMMA ID COLON dataType n11
			inputListNode* inNode = (inputListNode *) malloc(sizeof(inputListNode));
			nodeData.inputList = inNode;
			curr = getASTNode(nodeData, AST_NODE_INPUTLIST);
			ASTNode* idNode = constructAST(curr, NULL, ch -> next);
			ch = findinPT(ch, datatype);
			ASTNode* typeNode = constructAST(curr, idNode, ch);
			ch = findinPT(ch, input_plistnew);
			ASTNode* n11 = constructAST(curr, typeNode, ch);
			
			addChild(curr, n11);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			return curr;
		}
			
		case 12: {// n1 : EMPTY
			return NULL;
		}

		case 13: {// output_plist : ID COLON type n2 (output_plistnew)
			outputListNode* outNode = (outputListNode *) malloc(sizeof(outputListNode));
			nodeData.outputList = outNode;
			curr = getASTNode(nodeData, AST_NODE_OUTPUTLIST);
			ASTNode* idNode = constructAST(curr, NULL, ch);

			ch = findinPT(ch, type);
			ASTNode* typeNode = constructAST(curr, idNode, ch);

			ch = findinPT(ch, output_plistnew);
			ASTNode* outList = constructAST(curr, typeNode, ch);

			/* remember: during the constructAST we have not created the previous links from siblings */ 
			addChild(curr, outList);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			return curr;
		}

		case 14: {// n2 : COMMA ID COLON type n21 (output_plistnew)
			outputListNode* outNode = (outputListNode *) malloc(sizeof(outputListNode));
			nodeData.outputList = outNode;
			curr = getASTNode(nodeData, AST_NODE_OUTPUTLIST);
			ASTNode* idNode = constructAST(curr, NULL, ch -> next);
			
			ch = findinPT(ch, type);
			ASTNode* typeNode = constructAST(curr, idNode, ch);
			
			ch = findinPT(ch->next, output_plistnew);
			ASTNode* n21 = constructAST(curr, typeNode, ch);

			addChild(curr, n21);
			addChild(curr, typeNode);
			addChild(curr, idNode);
			return curr;
		}
			
		case 15: { // n2 : EMPTY
			return NULL;
		}

		case 16: {// type : INTEGER
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_INT;
			// TODO: add data for leaf
			return curr;
		}
			
		case 17: {// type : REAL
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_RNUM;
			// TODO: add data for leaf
			return curr;
		}

		case 18: {// type : BOOLEAN
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_BOOL;
			// TODO: add data for leaf
			return curr;
		}

		case 19: {// dataType : type
			return constructAST(curr, NULL, ch); // directly propagating leaf upwards
		}
			
		case 20: {// dataType : ARRAY SQBO range_arrays SQBC OF type
			dataTypeNode* dtn = (dataTypeNode *) malloc(sizeof(dataTypeNode));
			nodeData.dataType = dtn;
			curr = getASTNode(nodeData, AST_NODE_ARRAY);
			ch = findinPT(ch, range_arrays);
			ASTNode* rangeNode = constructAST(curr, NULL, ch);
			ch = findinPT(ch, type);
			ASTNode* typeNode = constructAST(curr, rangeNode, ch);

			addChild(curr, typeNode);
			addChild(curr, rangeNode);
			return curr;
		}

		case 21: {// moduleDef : START statements END
			return constructAST(parent, NULL, ch -> next);
		}

		/* CHECK @ everything is ASTNode type, so we don't need a separate type for the AST_NODE_STATEMENT */
		case 22: {// statements : statement statements
			statementNode* sn = (statementNode *) malloc(sizeof(statementNode));
			nodeData.statement = sn;
			curr = getASTNode(nodeData, AST_NODE_STATEMENT);
			ASTNode* stmtNode = constructAST(curr, NULL, ch);
			ASTNode* stmtsNode = constructAST(curr, NULL, ch -> next);
		
			addChild(curr, stmtsNode);
			addChild(curr, stmtNode);
			return curr;
		}	

		case 23: {// statements : EMPTY
			return NULL;
		}

		case 24: {// statement : ioStmt
			return constructAST(parent, NULL, ch);
		}

		case 25: {// statement : simpleStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 26: {// statement : declareStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 27: {// statement : condionalStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 28: {// statement : iterativeStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 29: {// ioStmt : GET_VALUE BO ID BC SEMICOL
			ioNode* tmp = (ioNode *) malloc(sizeof(ioNode));
			nodeData.io = tmp;
			curr = getASTNode(nodeData, AST_NODE_IO);
			tmp -> type = AST_IO_GETVAL;
			ASTNode* idNode = constructAST(curr, NULL, ch -> next -> next);

			addChild(curr, idNode);
			return curr;
		}

		case 30: {//ioStmt  : PRINT BO var BC SEMICOL
			ioNode* tmp = (ioNode *) malloc(sizeof(ioNode));
			nodeData.io = tmp;
			curr = getASTNode(nodeData, AST_NODE_IO);
			tmp -> type = AST_IO_PRINT;
			ASTNode* vNode = constructAST(curr, NULL, ch -> next -> next);

			addChild(curr, vNode);
			return curr;
		}
		
		case 31: {// whichId : SQBO index SQBC
			return constructAST(curr, NULL, ch -> next);
		}
		
		case 32: {// whichId : EMPTY
			return NULL;
		}
		
		case 33: {// index : NUM
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_IDXNUM;
			// TODO: add data for leaf
			return curr;
		}
				
		case 34: {// index : ID
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_IDXID;
			// TODO: add data for leaf
			return curr;
		}

		case 35: {// simpleStmt : assignmentStmt
			simpleStmtNode* simple = (simpleStmtNode *) malloc(sizeof(simpleStmtNode));
			nodeData.simpleStmt = simple;
			curr = getASTNode(nodeData, AST_NODE_SIMPLESTMT);
			simple -> type = AST_STMT_SIMPLE_ASSIGN;

			ASTNode* stmt = constructAST(curr, NULL, ch);
			addChild(curr, stmt);
			return curr;
		}
		
		case 36: {// simpleStmt : moduleReuseStmt
			simpleStmtNode* simple = (simpleStmtNode *) malloc(sizeof(simpleStmtNode));
			nodeData.simpleStmt = simple;
			curr = getASTNode(nodeData, AST_NODE_SIMPLESTMT);
			simple -> type = AST_STMT_SIMPLE_MODULEREUSE;

			ASTNode* stmt = constructAST(curr, NULL, ch);
			addChild(curr, stmt);
			return curr;
		}
		
		case 37: {// assignmentStmt : ID whichStmt
			assignNode* an = (assignNode *) malloc(sizeof(assignNode));
			nodeData.assign = an;
			curr = getASTNode(nodeData, AST_NODE_ASSIGN);

			ASTNode* idNode = constructAST(curr, NULL, ch);
			ASTNode* wNode = constructAST(curr, idNode, ch -> next);

			addChild(curr, wNode);
			addChild(curr, idNode);
			return curr;
		}
		
		case 38: {//moduleReuseStmt : optional USE MODULE ID WITH PARAMETERS idList SEMICOL
			moduleReuseNode* mrn = (moduleReuseNode *) malloc(sizeof(moduleReuseNode));
			nodeData.moduleReuse = mrn;
			curr = getASTNode(nodeData, AST_NODE_MODULEREUSE);

			ASTNode* opt = constructAST(curr, NULL, ch);
			ch = ch -> next -> next -> next;
			ASTNode* idNode = constructAST(curr, opt, ch);
			ch = findinPT(ch, idlist);
			ASTNode* list = constructAST(curr, idNode, ch);

			addChild(curr, list);
			addChild(curr, idNode);
			addChild(curr, opt);
			return curr;
		}
		
		case 39: {// optional : SQBO idList SQBC ASSIGNOP
			return constructAST(parent, NULL, ch -> next);
		}
		
		case 40: {// optional : EMPTY
			return NULL;
		}
		
		case 41: {// idList : ID n3 
			idListNode* iln = (idListNode *) malloc(sizeof(idListNode));
			nodeData.idList = iln;
			curr = getASTNode(nodeData, AST_NODE_IDLIST);

			ASTNode* idNode = constructAST(curr, NULL, ch);
			ASTNode* n3 = constructAST(curr, idNode, ch -> next);

			addChild(curr, n3);
			addChild(curr, idNode);
			return curr;
		}
	
		case 42: {// n3 : COMMA ID n3
			idListNode* iln = (idListNode *) malloc(sizeof(idListNode));
			nodeData.idList = iln;
			curr = getASTNode(nodeData, AST_NODE_IDLIST);

			ASTNode* idNode = constructAST(curr, NULL, ch -> next);
			ch = findinPT(ch -> next, idlistnew);
			ASTNode* n3 = constructAST(curr, idNode, ch);

			addChild(curr, n3);
			addChild(curr, idNode);
			return curr;
		}			
	
		case 43: {// n3 : EMPTY
			return NULL;
		}
	
		case 44: {// expression : arithmeticOrBooleanExpr 
			exprNode* en = (exprNode *) malloc(sizeof(exprNode));
			nodeData.expr = en;
			curr = getASTNode(nodeData, AST_NODE_EXPR);
			en -> type = AST_EXPR_AOB;

			ASTNode* aob = constructAST(curr, NULL, ch);

			addChild(curr, aob);
			return curr;
		}	
		
		case 45: {// expression : u
			exprNode* en = (exprNode *) malloc(sizeof(exprNode));
			nodeData.expr = en;
			curr = getASTNode(nodeData, AST_NODE_EXPR);
			en -> type = AST_EXPR_UNARY;

			ASTNode* u = constructAST(curr, NULL, ch);

			addChild(curr, u);
			return curr;
		}
		
		/* TODO: CHECK @ In expressions, the adress of anyTerm node is passed in the call of 'n7'(inherited)
		 * and it maybe stored in the ASTNode corresponding to n7 
		 * ALso verify the left recursion part */

		case 46: {// arithmeticOrBooleanExpr : anyTerm n7
			ASTNode* at = constructAST(parent, NULL, ch);
			return constructAST(parent, at, ch -> next);
		}
		
		case 47: {// n7 : logicalOp anyTerm n7
			AOBExprNode* aob = (AOBExprNode *) malloc(sizeof(AOBExprNode));
			nodeData.AOBExpr = aob;
			curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode* lop = constructAST(curr, NULL, ch);
			ASTNode* at = constructAST(curr, lop, ch -> next);

			addChild(curr, at);												
			addChild(curr, lop);				
			addChild(curr, prev_sibling);

			ch = findinPT(ch, arithorboolexprnew);
			return constructAST(parent, curr, ch);
		}															

		case 48: {// n7 : EMPTY
			return prev_sibling;
		}	
		
		/* To do: Check for the tags required in the AOBExprNode */
		case 49: {// anyTerm : arithmeticExpr n8
			ASTNode* ae = constructAST(parent, NULL, ch);
			return constructAST(parent, ae, ch -> next);
		}	
		
		case 50: {// anyTerm : boolConstt
			return constructAST(parent, NULL, ch);
		}
			
		case 51: {// n8 : relationalOp arithmeticExpr
			AOBExprNode* aob = (AOBExprNode *) malloc(sizeof(AOBExprNode));
			nodeData.AOBExpr = aob;
			curr = getASTNode(nodeData, AST_NODE_AOBEXPR);

			ASTNode* relop = constructAST(curr, NULL, ch);
			ASTNode* ae = constructAST(curr, relop, ch -> next);

			addChild(curr, ae);
			addChild(curr, relop);
			addChild(curr, prev_sibling);
			return curr;
		}
		
		case 52: {// n8 : EMPTY 
			return prev_sibling;
		}
		
		case 53: {// arithmeticExpr : term n4
			ASTNode* term = constructAST(parent, NULL, ch);
			return constructAST(parent, term, ch -> next);
		}
		
		case 54: {// n4 : op1 term n4
			AOBExprNode* aob = (AOBExprNode *) malloc(sizeof(AOBExprNode));
			nodeData.AOBExpr = aob;
			curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode* op1 = constructAST(curr, NULL, ch);
			ASTNode* term = constructAST(curr, op1, ch -> next);

			addChild(curr, term);
			addChild(curr, op1);
			addChild(curr, prev_sibling);

			ch = findinPT(ch, arithmeticexprnew);
			return constructAST(parent, curr, ch);
		}	
		
		case 55: {// n4 : EMPTY
			return prev_sibling;
		}
		
		case 56: {// term : factor n5
			ASTNode* fact = constructAST(parent, NULL, ch);
			return constructAST(parent, fact, ch -> next);
		}
			
		case 57: {// n5 : op2 factor n5
			AOBExprNode* aob = (AOBExprNode *) malloc(sizeof(AOBExprNode));
			nodeData.AOBExpr = aob;
			curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode* op2 = constructAST(curr, NULL, ch);
			ASTNode* fact = constructAST(curr, op2, ch -> next);

			addChild(curr, fact);
			addChild(curr, op2);
			addChild(curr, prev_sibling);

			ch = findinPT(ch, termnew);
			return constructAST(parent, curr, ch);
		}	
		
		case 58: {// n5 : EMPTY
			return prev_sibling;
		}	
		
		case 59: {// factor : BO arithmeticOrBooleanExpr BC
			return constructAST(parent, NULL, ch -> next);
		}	
		
		/* CHECK @ different from the AST Rules we submitted, here all the 
		 * nodes are of the same type, so we don't need the jugglery we did 
		 * using the NULL pointers */
		case 60: {// factor : var_id_num
			return constructAST(parent, NULL, ch);
		}
		
		case 61: {// var : var_id_num
			return constructAST(parent, NULL, ch);
		}
		
		case 62: {// var : boolConstt
			return constructAST(parent, NULL, ch);
		}
		
		case 63: {// op1 : PLUS	
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_PLUS;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 64: { // op1 : MINUS
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_MINUS;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 65: {// op2 : MUL
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_MUL;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 66:{ // op2 : DIV
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_DIV;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 67:{ // logicalOp : AND
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_AND;
			// TODO: add data for leaf
			return curr;		
		}

		case 68: {// logicalOp : OR
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_OR;
			// TODO: add data for leaf
			return curr;
		}
			
		case 69: {// relationalOp : LT
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_LT;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 70: {// relationalOp : LE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_LE;
			// TODO: add data for leaf
			return curr;
		}
			
		case 71: {// relationalOp : GT	
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_GT;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 72: {// relationalOp : GE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_GE;
			// TODO: add data for leaf
			return curr;
		}
			
		case 73: {// relationalOp : EQ
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_EQ;
			// TODO: add data for leaf
			return curr;
		}	
		
		case 74: {// relationalOp : NE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_NE;
			// TODO: add data for leaf
			return curr;
		}
			
		case 75: {// declareStmt : DECLARE idList COLON dataType SEMICOL
			declareStmtNode* dsn = (declareStmtNode *) malloc(sizeof(declareStmtNode));
			nodeData.declareStmt = dsn;
			curr = getASTNode(nodeData, AST_NODE_DECLARESTMT);
			ch = findinPT(ch, idlist);
			ASTNode* list = constructAST(curr, NULL, ch);
			ch = findinPT(ch, datatype);
			ASTNode* type = constructAST(curr, list, ch);

			addChild(curr, type);
			addChild(curr, list);

			return curr;
		}	
		
		case 76: {// condionalStmt : SWITCH BO ID BC START caseStmts default END
			condStmtNode* csn = (condStmtNode *) malloc(sizeof(condStmtNode));
			nodeData.condStmt = csn;
			curr = getASTNode(nodeData, AST_NODE_CONDSTMT);
			
			ASTNode* idNode = constructAST(curr, NULL, ch -> next -> next);
			ch = findinPT(ch, casestmts);
			ASTNode* cs = constructAST(curr, idNode, ch);
			ch = findinPT(ch, _default);
			ASTNode* def = constructAST(curr, cs, ch);

			addChild(curr, def);
			addChild(curr, cs);
			addChild(curr, idNode);
			return curr;
		}	
		
		case 77: {// caseStmts : CASE value COLON statements BREAK SEMICOL n9
			caseStmtNode* csn = (caseStmtNode *) malloc(sizeof(caseStmtNode));
			nodeData.caseStmt = csn;
			curr = getASTNode(nodeData, AST_NODE_CASESTMT);
			
			ch = findinPT(ch, value);
			ASTNode* val = constructAST(curr, NULL, ch);
			ch = findinPT(ch, statements);
			ASTNode* stmt = constructAST(curr, val, ch);
			ch = findinPT(ch, casestmtsnew);
			ASTNode* n9 = constructAST(curr, stmt, ch);

			addChild(curr, n9);
			addChild(curr, stmt);
			addChild(curr, val);
			return curr;
		}	
		
		case 78: {// n9 : CASE value COLON statements BREAK SEMICOL n9
			caseStmtNode* csn = (caseStmtNode *) malloc(sizeof(caseStmtNode));
			nodeData.caseStmt = csn;
			curr = getASTNode(nodeData, AST_NODE_CASESTMT);
			
			ch = findinPT(ch, value);
			ASTNode* val = constructAST(curr, NULL, ch);
			ch = findinPT(ch, statements);
			ASTNode* stmt = constructAST(curr, val, ch);
			ch = findinPT(ch, casestmtsnew);
			ASTNode* n9 = constructAST(curr, stmt, ch);

			addChild(curr, n9);
			addChild(curr, stmt);
			addChild(curr, val);
			return curr;
		}	
		
		case 79: {// n9 : EMPTY
			return NULL;
		}

		case 80: {// value : NUM
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_VALNUM;
			// TODO: add data for leaf
			return curr;
		}
		
		case 81: {// value : TRUE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_VALTRUE;
			// TODO: add data for leaf
			return curr;
		}
		
		case 82: {// value : FALSE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_VALFALSE;
			// TODO: add data for leaf
			return curr;
		}
		
		case 83: {// default : DEFAULT COLON statements BREAK SEMICOL
			ch = findinPT(ch, statements);
			return constructAST(parent, NULL, ch);
		}
		
		case 84: {// default : EMPTY
			return NULL;
		}
		
		case 85: {// iterativeStmt : FOR BO ID IN range BC START statements END
			iterStmtNode* isn = (iterStmtNode *) malloc(sizeof(iterStmtNode));
			nodeData.iterStmt = isn;
			curr = getASTNode(nodeData, AST_NODE_ITERSTMT);
			isn -> type = AST_ITER_FOR;

			ASTNode* idNode = constructAST(curr, NULL, ch -> next -> next);
			ch = findinPT(ch, range);
			ASTNode* range = constructAST(curr, idNode, ch);
			ch = findinPT(ch, statements);
			ASTNode* stmt = constructAST(curr, range, ch);

			addChild(curr, stmt);
			addChild(curr, range);
			addChild(curr, idNode);
			return curr;
		}
		
		case 86: {// iterativeStmt : WHILE BO arithmeticOrBooleanExpr BC START statements END
			iterStmtNode* isn = (iterStmtNode *) malloc(sizeof(iterStmtNode));
			nodeData.iterStmt = isn;
			curr = getASTNode(nodeData, AST_NODE_ITERSTMT);
			isn -> type = AST_ITER_WHILE;

			ch = findinPT(ch, arithorboolexpr);
			ASTNode* aob = constructAST(curr, NULL, ch);
			ch = findinPT(ch, statements);
			ASTNode* stmt = constructAST(curr, aob, ch);

			addChild(curr, stmt);
			addChild(curr, aob);
			return curr;
		}
		
		case 87: {// range : NUM RANGEOP NUM
			rangeArraysNode* ran = (rangeArraysNode *) malloc(sizeof(rangeArraysNode));
			nodeData.rangeArrays = ran;
			curr = getASTNode(nodeData, AST_NODE_RANGEARRAYS);

			ASTNode* n1 = constructAST(curr, NULL, ch);
			ASTNode* n2 = constructAST(curr, n1, ch -> next -> next);

			addChild(curr, n2);
			addChild(curr, n1);
			return curr;
		}
		
		case 88: {// range_arrays : index RANGEOP index
			rangeArraysNode* ran = (rangeArraysNode *) malloc(sizeof(rangeArraysNode));
			nodeData.rangeArrays = ran;
			curr = getASTNode(nodeData, AST_NODE_RANGEARRAYS);

			ASTNode* i1 = constructAST(curr, NULL, ch);
			ASTNode* i2 = constructAST(curr, i1, ch -> next -> next);

			addChild(curr, i2);
			addChild(curr, i1);
			return curr;
		}
		
		case 89: {// boolConstt : TRUE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_BOOLTRUE;
			// TODO: add data for leaf
			return curr;
		}
		
		case 90: {// boolConstt : FALSE
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_BOOLFALSE;
			// TODO: add data for leaf
			return curr;
		}
	
		case 91: {// var_id_num : ID whichId
			varidnumNode* ran = (varidnumNode *) malloc(sizeof(varidnumNode));
			nodeData.var = ran;
			curr = getASTNode(nodeData, AST_NODE_VARIDNUM);

			ASTNode* idNode = constructAST(curr, NULL, ch);
			ASTNode* whichid = constructAST(curr, idNode, ch -> next);

			addChild(curr, whichid);
			addChild(curr, idNode);
			return curr;
		}
		
		case 92: {// var_id_num : NUM
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_VARIDNUM_NUM;
			// TODO: add data for leaf
			return curr;
		}
		
		case 93: {// var_id_num : RNUM
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_VARIDNUM_RNUM;
			// TODO: add data for leaf
			return curr;
		}
		
		case 94: {// whichStmt : lvalueIDStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 95: {// whichStmt : lvalueARRStmt
			return constructAST(parent, NULL, ch);
		}
		
		case 96: {// lvalueIDStmt : ASSIGNOP expression SEMICOL
			return constructAST(parent, NULL, ch -> next);
		}
		
		case 97: {// lvalueARRStmt : SQBO index SQBC ASSIGNOP expression SEMICOL
			lvalueARRStmtNode* lval = (lvalueARRStmtNode *) malloc(sizeof(lvalueARRStmtNode));
			nodeData.lvalueARRStmt = lval;
			curr = getASTNode(nodeData, AST_NODE_LVALARRSTMT);

			ch = findinPT(ch, _index);
			ASTNode* idx = constructAST(curr, NULL, ch);
			ch = findinPT(ch, expression);
			ASTNode* expr = constructAST(curr, idx, ch);

			addChild(curr, expr);
			addChild(curr, idx);
			return curr;
		}
		
		case 98: {// u : unary_op new_NT
			unaryNode* un = (unaryNode *) malloc(sizeof(unaryNode));
			nodeData.unary = un;
			curr = getASTNode(nodeData, AST_NODE_UNARY);

			ASTNode* uop = constructAST(curr, NULL, ch);
			ASTNode* new = constructAST(curr, uop, ch -> next);

			addChild(curr, new);
			addChild(curr, uop);
			return curr;
		}
		
		case 99: {// unary_op : PLUS
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_UOPPLUS;
			// TODO: add data for leaf
			return curr;
		}
		
		case 100: {// unary_op : MINUS
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_UOPMINUS;
			// TODO: add data for leaf
			return curr;
		}
		
		case 101: {// new_NT : BO arithmeticExpr BC
			return constructAST(parent, NULL, ch -> next);
		}
		
		case 102: {// new_NT : var_id_num
			return constructAST(parent, NULL, ch);
		}

		case -1: {
			/**
			 * TODO: Check if all case -1 actually produce ID
			 */ 
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_ID;
			// TODO: add data for leaf
			return curr;
		}
	
		default: {
			fprintf(stderr, "No rule corresponding to the given Parse Tree Node\n");
		}		
	}
}