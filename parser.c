
#include "parserDef.h"

void insertElement (int idx, char * str, typeOfSymbol t, nonterminal e) {
	symbol s;
	s.NT = e;
	HT[idx].sym = s;
	strcpy(HT[idx].str, str);
	HT[idx].tag = t;
}

void populateHashTable() {

	char * nonterminals[] = { 
		"program",
		"moduleDeclarations",
		"moduleDeclaration",
		"otherModules",
		"driverModule",
		"module",
		"ret",
		"input_plist",
		"input_plistNew",
		"output_plist",
		"output_plistNew",
		"type",
		"dataType",
		"moduleDef",
		"statements",
		"statement",
		"ioStmt",
		"whichId",
		"index",
		"simpleStmt",
		"assignmentStmt",
		"modulereuseStmt",
		"optional",
		"idList",
		"idListNew",
		"expression",
		"arithOrBoolExpr",
		"arithOrBoolExprNew",
		"relopExpr",
		"relopExprNew",
		"arithmeticExpr",	
		"arithmeticExprNew",
		"term",
		"termNew",
		"factor",
		"var",
		"pm",
		"md",
		"logicalOp",
		"relationalOp",
		"declareStmt",
		"condionalStmt",
		"caseStmts",
		"caseStmtsNew",
		"value",
		"default",
		"iterativeStmt",
		"range"
	};
	int i;
	for(i = 0; i < 48; i++) {
		int idx = hash(nonterminals[i]);
		insertElement(idx, nonterminals[i], NT, i);
	}

	char * terminals[] = {
		"EMPTY",
		"INTEGER",
		"REAL",
		"BOOLEAN",
		"OF",
		"ARRAY",
		"START",
		"END",
		"DECLARE",
		"MODULE",
		"DRIVER",
		"PROGRAM",
		"GET_VALUE",
		"PRINT",
		"USE",
		"WITH",
		"PARAMETERS",
		"TRUE",
		"FALSE",
		"TAKES",
		"INPUT",
		"AND",
		"OR",
		"FOR",
		"IN",
		"SWITCH",
		"CASE",
		"BREAK",
		"DEFAULT",
		"WHILE",
		"PLUS",
		"MINUS",
		"MUL",
		"DIV",
		"LT",
		"LE",
		"GT",
		"GE",
		"EQ",
		"NE",
		"DEF",
		"ENDDEF",
		"RANGEOP",
		"SEMICOL",
		"COMMA",
		"ASSIGNOP",
		"SQBO",
		"SQBC",
		"BO",
		"BC",
		"NUM",
		"RNUM",
		"ID",
		"DRIVERDEF",
		"DRIVERENDDEF"
	};
	for(i = 0; i < 55; i++) {
		int idx = hash(terminals[i]);
		insertElement(idx, terminals[i], T, i);
	}
}

rhsNode * make_rhsNode(char * str, rhsNode * prev, int id) {
	rhsNode * r = (rhsNode *)malloc(sizeof(rhsNode));
	int idx = hash(str);
	r -> sym = HT[idx].sym;
	r -> tag = HT[idx].tag;
	r -> next = NULL;
	if(prev == NULL)
		G[id].head = r;
	else
		prev -> next = r;
	return r;
}

void populateGrammar(char * filename) {

	FILE * fp = fopen(filename, "r");
	char str[201];
	int lhs = 1;
	int grammar_id = 0;
	while(fgets(str, 200, fp) != NULL) {
		char * tok = strtok(str, " \t\n");
		int idx = hash(tok);
		G[grammar_id].left = HT[idx].sym.NT;
		rhsNode * prev = (rhsNode *)malloc(sizeof(rhsNode));
		prev = NULL;
		while(tok != NULL) {
			if(strcmp(tok, ":")) {
				rhsNode * r = make_rhsNode(tok, prev, grammar_id);
				prev = r;
			}
			else if(strcmp(tok, "|")) {
				prev = NULL;
				grammar_id++;
				G[grammar_id].left = HT[idx].sym.NT;
			}
			tok = strtok(NULL, " \t\n");
		}
		grammar_id++;
	}
}

void firstSet(int en) {
	
	int i;
	



}

int main() {
	populateGrammar("grammar.erp");
}