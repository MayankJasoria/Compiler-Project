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
			lf -> tn = ch;
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
			lf -> tn = ch;
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
			lf -> tn = ch;
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

			curr -> type = AST_NODE_STATEMENT;
			return curr;
			break;

		case 23: // statements : EMPTY
			return NULL;
			break;

		case 24: // statement : ioStmt
			return constructAST(parent, NULL, ch);
			break;

		case 25: // statement : simpleStmt
			return constructAST(parent, NULL, ch);
			break;
		
		case 26: // statement : declareStmt
			return constructAST(parent, NULL, ch);
			break;
		
		case 27: // statement : condionalStmt
			return constructAST(parent, NULL, ch);
			break;
		
		case 28: // statement : iterativeStmt
			return constructAST(parent, NULL, ch);
			break;
		
		case 29: // ioStmt : GET_VALUE BO ID BC SEMICOL
			ioNode * tmp = (ioNode *)malloc(sizeof(ioNode));
			astNodeData nodeData;
			nodeData.io = tmp;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_IO);
			tmp -> tag = AST_IO_GETVAL;
			ASTNode * idNode = constructAST(curr, NULL, ch -> next -> next);

			addChild(curr, idNode);
			curr -> type = AST_NODE_IO;
			return curr;
			break;

		case 30: //ioStmt  : PRINT BO var BC SEMICOL
			ioNode * tmp = (ioNode *)malloc(sizeof(ioNode));
			astNodeData nodeData;
			nodeData.io = tmp;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_IO);
			tmp -> tag = AST_IO_PRINT;
			ASTNode * vNode = constructAST(curr, NULL, ch -> next -> next);

			addChild(curr, vNode);
			curr -> type = AST_NODE_IO;
			return curr;
			break;
		
		case 31: // whichId : SQBO index SQBC
			return constructAST(curr, NULL, ch -> next);
			break;
		
		case 32: // whichId : EMPTY
			return NULL;
			break;
		
		case 33: // index : NUM
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_IDXNUM;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 34: // index : ID
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_IDXID;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 35: // simpleStmt : assignmentStmt
			simpleStmtNode * simple = (simpleStmtNode *) malloc(sizeof(simpleStmtNode));
			astNodeData nodeData;
			nodeData.simpleStmt = simple;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_SIMPLESTMT);
			simple -> tag = AST_SIMPLE_ASSIGN;

			ASTNode * stmt = constructAST(curr, NULL, ch);
			addChild(curr, stmt);
			curr -> type = AST_NODE_SIMPLESTMT;
			return curr;
			break;
		
		case 36: // simpleStmt : moduleReuseStmt
			simpleStmtNode * simple = (simpleStmtNode *) malloc(sizeof(simpleStmtNode));
			astNodeData nodeData;
			nodeData.simpleStmt = simple;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_SIMPLESTMT);
			simple -> tag = AST_SIMPLE_MODULEREUSE;

			ASTNode * stmt = constructAST(curr, NULL, ch);
			addChild(curr, stmt);
			curr -> type = AST_NODE_SIMPLESTMT;
			return curr;
			break;
		
		case 37: // assignmentStmt : ID whichStmt
			assignNode * an = (assignNode *)malloc(sizeof(assignNode));
			astNodeData nodeData;
			nodeData.assign = an;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_ASSIGN);

			ASTNode * idNode = constructAST(curr, NULL, ch);
			ASTNode * wNode = constructAST(curr, idNode, ch -> next);

			addChild(curr, wNode);
			addChild(curr, idNode);
			curr -> type = AST_NODE_ASSIGN;
			return curr;
			break;
		
		case 38: //moduleReuseStmt : optional USE MODULE ID WITH PARAMETERS idList SEMICOL
			moduleReuseNode * mrn = (moduleReuseNode *)malloc(sizeof(moduleReuseNode));
			astNodeData nodeData;
			nodeData.moduleReuse = mrn;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_MODULEREUSE);

			ASTNode * opt = constructAST(curr, NULL, ch);
			ch = ch -> next -> next -> next;
			ASTNode * idNode = constructAST(curr, opt, ch);
			ch = findinPT(ch, idlist);
			ASTNode * list = constructAST(curr, idNode, ch);

			addChild(curr, list);
			addChild(curr, idNode);
			addChild(curr, opt);
			curr -> type = AST_NODE_MODULEREUSE;
			return curr;
			break;
		
		case 39: // optional : SQBO idList SQBC ASSIGNOP
			return constructAST(parent, NULL, ch -> next);
			break;
		
		case 40: // optional : EMPTY
			return NULL;
			break;
		
		case 41: // idList : ID n3 
			idListNode * iln = (idListNode *)malloc(sizeof(idListNode));
			astNodeData nodeData;
			nodeData.idList = iln;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_IDLIST);

			ASTNode * idNode = constructAST(curr, NULL, ch);
			ASTNode * n3 = constructAST(curr, idNode, ch -> next);

			addChild(curr, n3);
			addChild(curr, idNode);
			curr -> type = AST_NODE_IDLIST;
			return curr;
			break;
		
		case 42: // n3 : COMMA ID n3
			idListNode * iln = (idListNode *)malloc(sizeof(idListNode));
			astNodeData nodeData;
			nodeData.idList = iln;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_IDLIST);

			ASTNode * idNode = constructAST(curr, NULL, ch -> next);
			ch = findinPT(ch -> next, idlistnew);
			ASTNode * n3 = constructAST(curr, idNode, ch);

			addChild(curr, n3);
			addChild(curr, idNode);
			curr -> type = AST_NODE_IDLIST;
			return curr;
			break;
		
		case 43: // n3 : EMPTY
			return NULL;
			break;
		
		case 44: // expression : arithmeticOrBooleanExpr 
			exprNode * en = (exprNode *)malloc(sizeof(exprNode));
			astNodeData nodeData;
			nodeData.expr = en;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_EXPR);
			en -> tag = AST_EXPR_AOB;

			ASTNode * aob = constructAST(curr, NULL, ch);

			addChild(curr, aob);
			curr -> type = AST_NODE_EXPR;
			return curr;
			break;
		
		case 45: // expression : u
			exprNode * en = (exprNode *)malloc(sizeof(exprNode));
			astNodeData nodeData;
			nodeData.expr = en;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_EXPR);
			en -> tag = AST_EXPR_UNARY;

			ASTNode * u = constructAST(curr, NULL, ch);

			addChild(curr, u);
			curr -> type = AST_NODE_EXPR;
			return curr;
			break;
		
		/* TODO: CHECK @ In expressions, the adress of anyTerm node is passed in the call of 'n7'(inherited)
		 * and it maybe stored in the ASTNode corresponding to n7 
		 * ALso verify the left recursion part */

		case 46: // arithmeticOrBooleanExpr : anyTerm n7
			ASTNode * at = constructAST(parent, NULL, ch);
			return constructAST(parent, at, ch -> next);
			break;
		
		case 47: // n7 : logicalOp anyTerm n7
			AOBExprNode * aob = (AOBExprNode *)malloc(sizeof(AOBExprNode));
			astNodeData nodeData;
			nodeData.AOBExpr = aob;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode * lop = constructAST(curr, NULL, ch);
			ASTNode * at = constructAST(curr, lop, ch -> next);

			addChild(curr, at);
			addChild(curr, lop);
			addChild(curr, prev_sibling);

			ch = findinPT(ch, arithorboolexprnew);
			curr -> type = AST_NODE_AOBEXPR;
			return constructAST(parent, curr, ch);
			break;
		
		case 48: // n7 : EMPTY
			return prev_sibling;
			break;
		
		/* To do: Check for the tags required in the AOBExprNode */
		case 49: // anyTerm : arithmeticExpr n8
			ASTNode * ae = constructAST(parent, NULL, ch);
			return constructAST(parent, ae, ch -> next);
			break;
		
		case 50: // anyTerm : boolConstt
			return constructAST(parent, NULL, ch);
			break;
		
		case 51: // n8 : relationalOp arithmeticExpr
			AOBExprNode * aob = (AOBExprNode *)malloc(sizeof(AOBExprNode));
			astNodeData nodeData;
			nodeData.AOBExpr = aob;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_AOBEXPR);

			ASTNode * relop = constructAST(curr, NULL, ch);
			ASTNode * ae = constructAST(curr, relop, ch -> next);

			addChild(curr, ae);
			addChild(curr, relop);
			addChild(curr, prev_sibling);
			curr -> type = AST_NODE_AOBEXPR;
			return curr;
			break;
		
		case 52: // n8 : EMPTY 
			return prev_sibling;
			break;
		
		case 53: // arithmeticExpr : term n4
			ASTNode * term = constructAST(parent, NULL, ch);
			return constructAST(parent, term, ch -> next);
			break;
		
		case 54: // n4 : op1 term n4
			AOBExprNode * aob = (AOBExprNode *)malloc(sizeof(AOBExprNode));
			astNodeData nodeData;
			nodeData.AOBExpr = aob;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode * op1 = constructAST(curr, NULL, ch);
			ASTNode * term = constructAST(curr, op1, ch -> next);

			addChild(curr, term);
			addChild(curr, op1);
			addChild(curr, prev_sibling);

			ch = findinPT(ch, arithmeticexprnew);
			curr -> type = AST_NODE_AOBEXPR;
			return constructAST(parent, curr, ch);
			break;
		
		case 55: // n4 : EMPTY
			return prev_sibling;
			break;
		
		case 56: // term : factor n5
			ASTNode * fact = constructAST(parent, NULL, ch);
			return constructAST(parent, fact, ch -> next);
			break;
		
		case 57: // n5 : op2 factor n5
			AOBExprNode * aob = (AOBExprNode *)malloc(sizeof(AOBExprNode));
			astNodeData nodeData;
			nodeData.AOBExpr = aob;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_AOBEXPR);
			ASTNode * op2 = constructAST(curr, NULL, ch);
			ASTNode * fact = constructAST(curr, op2, ch -> next);

			addChild(curr, fact);
			addChild(curr, op2);
			addChild(curr, prev_sibling);

			ch = findinPT(ch, termnew);
			curr -> type = AST_NODE_AOBEXPR;
			return constructAST(parent, curr, ch);
			break;
		
		case 58: // n5 : EMPTY
			return prev_sibling;
			break;
		
		case 59: // factor : BO arithmeticOrBooleanExpr BC
			return constructAST(parent, NULL, ch -> next);
			break;
		
		/* CHECK @ different from the AST Rules we submitted, here all the 
		 * nodes are of the same type, so we don't need the jugglery we did 
		 * using the NULL pointers */
		case 60: // factor : var_id_num
			return constructAST(parent, NULL, ch);
			break;
		
		case 61: // var : var_id_num
			return constructAST(parent, NULL, ch);
			break;
		
		case 62: // var : boolConstt
			return constructAST(parent, NULL, ch);
			break;
		
		case 63: // op1 : PLUS
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_PLUS;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 64: // op1 : MINUS
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_MINUS;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 65: // op2 : MUL
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_MUL;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 66: // op2 : DIV
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_DIV;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 67: // logicalOp : AND
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_AND;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 68: // logicalOp : OR
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_OR;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 69: // relationalOp : LT
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_LT;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 70: // relationalOp : LE
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_LE;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 71: // relationalOp : GT
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_GT;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 72: // relationalOp : GE
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_GE;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 73: // relationalOp : EQ
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_EQ;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
			break;
		
		case 74: // relationalOp : NE
			leafNode * lf = (leafNode *) malloc(sizeof(leafNode));
			astNodeData nodeData;
			nodeData.leaf = lf;
			ASTNode * curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> tag = AST_LEAF_NE;
			// TODO: add data for leaf
			curr -> type = AST_NODE_LEAF;
			return curr;
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
