/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */

#include "astDef.h"
#include "n_ary_tree.h"
#include "queue.h"
#include <string.h>

#define AST_FMT_HEADERS "%-20s%-20s%-9s%-23s%-12s%-22s%-10s%-10s%-8s%-12s\n"
#define AST_FMT_LEAF_NUM "%-20s%-20sYes      %-23s%-12d%-22s%-10s----      %-8d%-12d\n"
#define AST_FMT_LEAF_RNUM "%-20s%-20sYes      %-23s%-12d%-22s%-10s----      %-8f%-12d\n"
#define AST_FMT_LEAF_ID "%-20s%-20sYes      %-23s%-12d%-22s%-10s----      ----    %-12d\n"
#define AST_FMT_LEAF_BOOL "%-20s%-20sYes      %-23s%-12d%-22s%-10s----      %-8s%-12d\n"
#define AST_FMT_NON_LEAF "%-20s%-20sNo       %-23s----        %-22s%-10s%-10s----    %-12d\n"

char* astNodeTypeList[] = {
	"Program",
	"Module Declaration",
	"Module List",
	"Module",
	"Input List",
	"Output List",
	"Array",
	"Range Arrays",
	"Statement",
	"IO",
	"Simple Statement",
	"Assign",
	"Which Statement",
	"Module Reuse",
	"ID List",
	"Expression",
	"AOB Expression",
	"Declare Statement",
	"Conditional Statement",
	"Case Statement",
	"Unary",
	"LVAL Arr Statement",
	"Iterative Statement",
	"For",
	"While",
	"Var ID Num",
	"Leaf",
	"\0"
};

char* leafTypeList[] = {
	"INT",
	"RNUM",
	"NUM",
	"BOOL",
	"ID",
	"IDXNUM",
	"IDXID",
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"OR",
	"AND",
	"LT",
	"LE",
	"GT",
	"GE",
	"EQ",
	"NE",
	"TRUE",
	"FALSE",
	"VALNUM",
	"VALTRUE",
	"VALFALSE",
	"VARIDNUM_NUM",
	"VARIDNUM_ID",
	"VARIDNUM_RNUM",
	"BOOLTRUE",
	"BOOLFALSE",
	"UOPPLUS",
	"UOPMINUS",
	"\0"
};

/** 
 * Creates and returns a blank AST root 
 */
ASTNode* getASTNode(astNodeData nodeData, astNodeType t) {
	ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));

	/* Initialize all pointers to NULL */
	node -> parent = NULL;
	node -> child = NULL;
	node -> next = NULL;
	node -> prev = NULL;
	node -> localST = NULL;
	node -> type = t;
	node -> nodeData = nodeData;

	/**
	 * Increment number of AST Nodes by 1 
	 * Add the current size of AST Node to the total AST Size
	 */
	numASTnodes++;
	ASTSize += sizeof(ASTNode);

	/**
	 * Construct AST Node of the type specified in the function argument 
	 * Also update the AST size
	 */
	switch (t) {
		case AST_NODE_PROGRAM: {
			ASTSize += sizeof(programNode);
		}
		break;
		case AST_NODE_MODULEDECLARATION: {
			ASTSize += sizeof(moduleDeclarationNode);
		}
		break;
		case AST_NODE_MODULELIST: {
			ASTSize += sizeof(moduleListNode);
		}
		break;
		case AST_NODE_MODULE: {
			ASTSize += sizeof(moduleNode);
		}
		break;
		case AST_NODE_INPUTLIST: {
			ASTSize += sizeof(inputListNode);
		}
		break;
		case AST_NODE_OUTPUTLIST: {
			ASTSize += sizeof(outputListNode);
		}
		break;
		case AST_NODE_ARRAY: {
			ASTSize += sizeof(dataTypeNode);
			//dataTypeNode is reused for AST_NODE_ARRAY
		}
		break;
		case AST_NODE_RANGEARRAYS: {
			ASTSize += sizeof(rangeArraysNode);
		}
		break;
		case AST_NODE_STATEMENT: {
			ASTSize += sizeof(statementNode);
		}
		break;
		case AST_NODE_IO: {
			ASTSize += sizeof(ioNode);
		}
		break;
		case AST_NODE_SIMPLESTMT: {
			ASTSize += sizeof(simpleStmtNode);
		}
		break;
		case AST_NODE_ASSIGN: {
			ASTSize += sizeof(assignNode);
		}
		break;
		case AST_NODE_MODULEREUSE: {
			ASTSize += sizeof(moduleReuseNode);
		}
		break;
		case AST_NODE_IDLIST: {
			ASTSize += sizeof(idListNode);
		}
		break;
		case AST_NODE_AOBEXPR: {
			ASTSize += sizeof(AOBExprNode);
		} 
		break;
		case AST_NODE_DECLARESTMT: {
			ASTSize += sizeof(declareStmtNode);
		}
		break;
		case AST_NODE_CONDSTMT: {
			ASTSize += sizeof(condStmtNode);
		}
		break;
		case AST_NODE_CASESTMT: {
			ASTSize += sizeof(caseStmtNode);
		}
		break;
		case AST_NODE_UNARY: {
			ASTSize += sizeof(unaryNode);
		}
		break;
		case AST_NODE_LVALARRSTMT: {
			ASTSize += sizeof(lvalueARRStmtNode);
		}
		break;
		case AST_NODE_ITERSTMT: {
			ASTSize += sizeof(iterStmtNode);
		}
		break;
		case AST_NODE_FOR: {
			ASTSize += sizeof(forNode);
		}
		break;
		case AST_NODE_WHILE: {
			ASTSize += sizeof(whileNode);
		}
		break;
		case AST_NODE_VARIDNUM: {
			ASTSize += sizeof(varidnumNode);
		}
		break;
		case AST_NODE_LEAF: {
			ASTSize += sizeof(leafNode);
			ASTSize += sizeof(treeNode);
		}
		break;
	}
	return node;
}

/**
 * Returns Data Type of Expression
 * @param expr: AST Node representing the root of expression subtree
 */
int getExprType(ASTNode * expr) {
	
	if(expr -> type == AST_NODE_LEAF) {
		return expr -> nodeData.leaf -> dataType;
	}
	else if(expr -> type == AST_NODE_VARIDNUM) {
		return expr -> nodeData.var -> dataType;
	}
	else if(expr -> type == AST_NODE_AOBEXPR) {
		return expr -> nodeData.AOBExpr -> dataType;
	}
	else if(expr -> type == AST_NODE_UNARY) {
		return expr -> nodeData.unary -> dataType;
	}
}

/**
 * Assumption: child's 'child' pointer need not be tampered with:
 * It has its own subtree
 * @see ast.h
 */
ASTNode* addChild(ASTNode* parent, ASTNode* child) {

	if(child == NULL)  {
		/* Trivial: child is null */
		return parent;
	}
	if(parent->child == NULL) {
		/* No children yet, add first child to parent */
		parent -> child = child;
		child -> parent = parent;
		child -> prev = NULL;
		child->next = NULL;
	} else {
		/* Some child exists, consider that child too */
		child -> next = parent -> child;
		parent -> child -> prev = child;
		parent -> child = child;
		child -> parent = parent;
	}
	return parent;
}

/** 
 * TODO: call free() to release memory for undesired nodes
 * NOTE: function not defined in header file, as it need not be externally visible
 */

/**
 * Finds the node for the corresponding non-terminal in the Parse Tree among a set of siblings
 * @param curr: The current node among siblings of the parse tree
 * @param nt: The required non-terminal
 * @return The node corresponding to the required non-terminal
 */

treeNode* findinPT(treeNode* curr, nonterminal nt) {

	treeNode* tmp = curr;
	while(tmp != NULL) {
		if(tmp -> tag == NT && tmp -> sym.NT == nt)
			return tmp;
		tmp = tmp -> next;
	}
	return NULL;
}


/**
 * Contruct the entire AST
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
			
			/* Add siblings in reverse order, to regenerate correct order */
			addChild(curr, om2);
			addChild(curr, dm);
			addChild(curr, om1);
			addChild(curr, md);
			curr -> type = AST_NODE_PROGRAM;	
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}
			
		case 1: {// moduleDeclarations : moduleDeclaration moduleDeclarations1
			moduleDeclarationNode* mdNode = (moduleDeclarationNode *) malloc(sizeof(moduleDeclarationNode));
			nodeData.moduleDeclaration = mdNode;
			curr = getASTNode(nodeData, AST_NODE_MODULEDECLARATION);
			
			/* Call siblings one by one */
			ASTNode* md = constructAST(curr, NULL, ch);
			ASTNode* mds = constructAST(curr, md, ch -> next);

			/* Add siblings in reverse order, to regenerate correct order */
			addChild(curr, mds);
			addChild(curr, md);
			curr -> associatedRule = tn -> rule_num;
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

			/* Call siblings one by one */
			ASTNode* mod = constructAST(curr, NULL, ch);
			ASTNode* om1 = constructAST(curr, mod, ch -> next);
			
			/* Add siblings in reverse order, to regenerate correct order */
			addChild(curr, om1);
			addChild(curr, mod);
			curr -> associatedRule = tn -> rule_num;
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

			/* Call sibling and add it */
			ASTNode* modDef = constructAST(curr, NULL, findinPT(ch, moduledef));
			addChild(curr, modDef);
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}

		case 7: {// module : DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
			moduleNode* modNode = (moduleNode *) malloc(sizeof(moduleNode));
			nodeData.module = modNode;
			curr = getASTNode(nodeData, AST_NODE_MODULE);

			/* Call siblings one by one */
			ASTNode* idNode = constructAST(curr, NULL, ch -> next -> next);
			ch = findinPT(ch, input_plist);
			ASTNode* inplist = constructAST(curr, idNode, ch);
			ch = findinPT(ch, ret);
			ASTNode* retNode = constructAST(curr, inplist, ch);
			ch = findinPT(ch, moduledef);
			ASTNode* defNode = constructAST(curr, retNode, ch);
			
			/* Add siblings in reverse order, to regenerate correct order */
			addChild(curr, defNode);
			addChild(curr, retNode);
			addChild(curr, inplist);
			addChild(curr, idNode);

			curr -> associatedRule = tn -> rule_num;
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

			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}
		
		case 17: {// type : REAL
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_RNUM;
			// TODO: add data for leaf
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}

		case 18: {// type : BOOLEAN
			lf = (leafNode *) malloc(sizeof(leafNode));
			nodeData.leaf = lf;
			curr = getASTNode(nodeData, AST_NODE_LEAF);
			lf -> tn = ch;
			lf -> type = AST_LEAF_BOOL;
			// TODO: add data for leaf
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}

		case 21: {// moduleDef : START statements END
			ASTNode * curr = constructAST(parent, NULL, ch -> next);
			if(parent -> type == AST_NODE_MODULELIST) {
				parent -> nodeData.moduleList -> start_line_num = tn -> child -> line_num;
				parent -> nodeData.moduleList -> end_line_num = tn -> child -> next -> next -> line_num;
			}
			else if(parent -> type == AST_NODE_MODULE) {
				parent -> nodeData.module -> start_line_num = tn -> child -> line_num;
				parent -> nodeData.module -> end_line_num = tn -> child -> next -> next -> line_num;
			}
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}

		case 30: {//ioStmt  : PRINT BO var BC SEMICOL
			ioNode* tmp = (ioNode *) malloc(sizeof(ioNode));
			nodeData.io = tmp;
			curr = getASTNode(nodeData, AST_NODE_IO);
			tmp -> type = AST_IO_PRINT;
			ASTNode* vNode = constructAST(curr, NULL, ch -> next -> next);

			addChild(curr, vNode);
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}
		
		case 36: {// simpleStmt : moduleReuseStmt
			simpleStmtNode* simple = (simpleStmtNode *) malloc(sizeof(simpleStmtNode));
			nodeData.simpleStmt = simple;
			curr = getASTNode(nodeData, AST_NODE_SIMPLESTMT);
			simple -> type = AST_STMT_SIMPLE_MODULEREUSE;

			ASTNode* stmt = constructAST(curr, NULL, ch);
			addChild(curr, stmt);
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}
		
		case 38: {//moduleReuseStmt : optional USE MODULE ID WITH PARAMETERS idList SEMICOL
			moduleReuseNode* mrn = (moduleReuseNode *) malloc(sizeof(moduleReuseNode));
			nodeData.moduleReuse = mrn;
			curr = getASTNode(nodeData, AST_NODE_MODULEREUSE);
			curr -> nodeData.moduleReuse -> listCheck = 1;

			ASTNode* opt = constructAST(curr, NULL, ch);
			ch = ch -> next -> next -> next;
			ASTNode* idNode = constructAST(curr, opt, ch);
			ch = findinPT(ch, idlist);
			ASTNode* list = constructAST(curr, idNode, ch);

			addChild(curr, list);
			addChild(curr, idNode);
			addChild(curr, opt);
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}			
	
		case 43: {// n3 : EMPTY
			return NULL;
		}
	
		case 44: {// expression : arithmeticOrBooleanExpr 
			// exprNode* en = (exprNode *) malloc(sizeof(exprNode));
			// nodeData.expr = en;
			// curr = getASTNode(nodeData, AST_NODE_EXPR);
			// en -> type = AST_EXPR_AOB;

			// ASTNode* aob = constructAST(curr, NULL, ch);

			// addChild(curr, aob);
			// return curr;
			return constructAST(parent, NULL, ch);
		}	
		
		case 45: {// expression : u
			// exprNode* en = (exprNode *) malloc(sizeof(exprNode));
			// nodeData.expr = en;
			// curr = getASTNode(nodeData, AST_NODE_EXPR);
			// en -> type = AST_EXPR_UNARY;

			// ASTNode* u = constructAST(curr, NULL, ch);

			// addChild(curr, u);
			// return curr;
			return constructAST(parent, NULL, ch);
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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

			curr -> associatedRule = tn -> rule_num;
			return curr;
		}	
		
		case 76: {// condionalStmt : SWITCH BO ID BC START caseStmts default END
			condStmtNode* csn = (condStmtNode *) malloc(sizeof(condStmtNode));
			csn -> def = 0;
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
			
			ch = tn -> child;
			while(ch != NULL) {
				if(ch -> tag == T && ch -> sym.T == START)
					break;
				ch = ch -> next;
			}
			curr -> nodeData.condStmt -> start_line_num = ch -> line_num;
			while(ch != NULL) {
				if(ch -> tag == T && ch -> sym.T == END)
					break;
				ch = ch -> next;
			}
			curr -> nodeData.condStmt -> end_line_num = ch -> line_num;
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			parent -> nodeData.condStmt -> def = 1;
			parent -> nodeData.condStmt -> def_line_num = ch -> prev -> prev -> line_num;
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
			
			curr -> nodeData.iterStmt -> start_line_num = ch -> prev -> line_num;
			curr -> nodeData.iterStmt -> end_line_num = ch -> next -> line_num;

			ASTNode* stmt = constructAST(curr, range, ch);
				
			addChild(curr, stmt);
			addChild(curr, range);
			addChild(curr, idNode);
			
			curr -> associatedRule = tn -> rule_num;
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

			curr -> nodeData.iterStmt -> start_line_num = ch -> prev -> line_num;
			curr -> nodeData.iterStmt -> end_line_num = ch -> next -> line_num;
			
			ASTNode* stmt = constructAST(curr, aob, ch);

			addChild(curr, stmt);
			addChild(curr, aob);
			curr -> associatedRule = tn -> rule_num;
			return curr;
		}
		
		case 87: {// range : NUM RANGEOP NUM
			rangeArraysNode* ran = (rangeArraysNode *) malloc(sizeof(rangeArraysNode));
			nodeData.rangeArrays = ran;
			curr = getASTNode(nodeData, AST_NODE_RANGEARRAYS);
			
			astNodeData nd1, nd2;

			// left child of range
			leafNode* lf1 = (leafNode *) malloc(sizeof(leafNode));
			nd1.leaf = lf1;
			ASTNode * n1 = getASTNode(nd1, AST_NODE_LEAF);
			lf1 -> tn = ch; 
			lf1 -> type = AST_LEAF_NUM;
			// TODO: add data for leaf

			// right child of range
			leafNode* lf2 = (leafNode *) malloc(sizeof(leafNode));
			nd2.leaf = lf2;
			ASTNode * n2 = getASTNode(nd2, AST_NODE_LEAF);
			lf2 -> tn = ch -> next -> next;
			lf2 -> type = AST_LEAF_NUM;
			// TODO: add data for leaf

			addChild(curr, n2);
			addChild(curr, n1);
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			curr -> associatedRule = tn -> rule_num;
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
			lf -> tn = tn;
			lf -> type = AST_LEAF_ID;
			// TODO: add data for leaf
			return curr;
		}
	
		default: {
			fprintf(stderr, "No rule corresponding to the given Parse Tree Node\n");
		}		
	}
}


/* 
	type (string)
	parent node (string)
	is_leaf (string: Yes/No)
	associated non-terminal/terminal (string)
	lineNumber (if leaf) (int)
	lex (if leaf) (string)
	dataType(id, expr, ) (string)
	val_if_number (int/real)
	ruleNum (int)
*/

/* Print relevant details of AST Node */
void printNode(ASTNode* curr) {
	
	//AST Node Type:
	char nodeType[30];
	strcpy(nodeType, astNodeTypeList[curr -> type]);

	//Parent Type:
	char parentType[30];
	if(curr->parent != NULL) {
		strcpy(parentType, astNodeTypeList[curr->parent->type]);
	} else {
		strcpy(parentType, "----                ");
	}
	
	//isLeaf and Leaf Type:
	int is_leaf = curr -> type == AST_NODE_LEAF;
	char leafType[30];
	strcpy(leafType, "----");
	if(is_leaf)
		strcpy(leafType, leafTypeList[curr -> nodeData.leaf -> type]);
	
	//Line Number:
	int line_num = -1;
	if(is_leaf)
		line_num = curr -> nodeData.leaf -> tn -> line_num;
	
	//Lexeme:
	char lexeme[30];
	strcpy(lexeme, "----");
	if(is_leaf)
		strcpy(lexeme, curr -> nodeData.leaf -> tn -> lex);
	
	int data = 0; /* data false */
	char op[20];
	//Data Type:
	char datatype[20];
	strcpy(datatype, "----");
	strcpy(op, "----");
	int is_op = 0; /* is operator */
	if(curr -> type == AST_NODE_AOBEXPR || curr -> type == AST_NODE_UNARY || 
		curr -> type == AST_NODE_VARIDNUM) {
		strcpy(datatype, typeName[getExprType(curr)]);
		data = 1; /* data: true */
		if (curr -> type == AST_NODE_AOBEXPR) {
			is_op = 1; /* is operator */
			strcpy(op, curr -> child -> next -> nodeData.leaf -> tn -> lex);
		}
	}

	//Value of int, float or bool variable:
	int int_val;
	float float_val;
	char bool_val[10];
	leaf_type t;
	if(curr -> type == AST_NODE_LEAF) {
		t = curr -> nodeData.leaf -> type;
		if(t == AST_LEAF_NUM || t == AST_LEAF_IDXNUM || t == AST_LEAF_VARIDNUM_NUM || t == AST_LEAF_VALNUM) {
			int_val = curr -> nodeData.leaf -> tn -> value.val_int;
		}
		if(t == AST_LEAF_VARIDNUM_RNUM) {
			float_val = curr -> nodeData.leaf -> tn -> value.val_float;
		}
		if(t == AST_LEAF_BOOLTRUE || t == AST_LEAF_BOOLFALSE || t == AST_LEAF_VALTRUE || t == AST_LEAF_VALFALSE
			|| t == AST_LEAF_TRUE || t == AST_LEAF_FALSE)
			strcpy(bool_val, curr -> nodeData.leaf -> tn -> lex);
	}
	
	
	int associatedRule = curr -> associatedRule;
	char associatedNT[20];
	if(curr -> type == AST_NODE_LEAF) 
		strcpy(associatedNT, terminals[curr -> nodeData.leaf -> tn -> sym.T]);
	else
		strcpy(associatedNT, nonterminals[G[associatedRule].left]);

	if(is_leaf) {
		if(t == AST_LEAF_BOOLTRUE ||
			t == AST_LEAF_BOOLFALSE ||
			t == AST_LEAF_VALTRUE || 
			t ==AST_LEAF_VALFALSE || 
			t == AST_LEAF_TRUE || 
			t == AST_LEAF_FALSE) {
			printf(AST_FMT_LEAF_BOOL, nodeType,
				parentType,
				associatedNT,
				line_num,
				lexeme,
				datatype,
				bool_val,
				associatedRule
			);
		} else if(t == AST_LEAF_VARIDNUM_RNUM) {
			printf(AST_FMT_LEAF_RNUM, nodeType,
				parentType,
				associatedNT,
				line_num,
				lexeme,
				datatype,
				float_val,
				associatedRule
			);
		} else if(t == AST_LEAF_NUM || 
			t == AST_LEAF_IDXNUM  || 
			t == AST_LEAF_VARIDNUM_NUM || 
			t == AST_LEAF_VALNUM) {
			printf(AST_FMT_LEAF_NUM, nodeType,
				parentType,
				associatedNT,
				line_num,
				lexeme,
				datatype,
				int_val,
				associatedRule
			);
		} else {
			printf(AST_FMT_LEAF_ID, nodeType,
				parentType,
				associatedNT,
				line_num,
				lexeme,
				datatype,
				associatedRule
			);
		}
	} else {
		/* non-leaf */	
		printf(AST_FMT_NON_LEAF, nodeType, parentType, associatedNT, lexeme, datatype, op, associatedRule);
		
	}
}

/**
 * @see ast.h
 */
void printAST(ASTNode* root){
	if(root->parent == NULL) {
		printf(AST_FMT_HEADERS, "Type", "Parent", "Is Leaf", "Terminal/Non-Terminal", "Line Number", "Lexeme", "Data Type", "Operator", "Value", "Rule Number");
	}
	if(!(root->type == AST_NODE_LEAF 
		&& root->parent->type == AST_NODE_AOBEXPR 
		&& root->parent->child->next == root)) {
		printNode(root);
	}
	ASTNode * ch = root -> child;
	while(ch != NULL) {
		printAST(ch);
		ch = ch -> next;
	}
}