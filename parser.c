
#include "parserDef.h"

void parserInit(char * filename) {
	num_rules = 0;
	int i;
	for(i = 0; i < 100; i++) {
		first[i] = 0;
		follow[i] = 0;
	}
	populateHashTable();
	populateGrammar(filename);
}

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
	num_rules = grammar_id;
}

unsigned long long int setUnion {unsigned long long int a, unsigned long long int b} {
	return a | b;
}

int findinSet(unsigned long long int a, int i) {
	unsigned long long int tmp = (unsigned long long int) 1 << i;
	if(tmp & a)
		return 1;
	return 0;
}

unsigned long long int firstSet(nonterminal en) {
	
	/* check this */
	if(first[en] != 0)
		return first[en];
	int i;
	int isEmpty = 0;
	for(i = 0; i < num_rules; i++) {
		if(G[i].left < en)
			continue;
		else if(G[i].left > en)
			break;
		rhsNode * node = G[i].head;
		while(node != NULL) {
			if(node.tag == 0) {
				first[en] = setUnion(first[en], ((unsigned long long int)1 << tag));
				if(first[en] % 2)
					first[en]--;
				break;
			}
			else {
				unsigned long long tmp = firstSet(node.left);
				if(findinSet(tmp, 0)) {
					first[en] = setUnion(first[en], tmp);
					node = node -> next;
					continue;
				}
				else {
					first[en] = setUnion(first[en], tmp);
					if(first[en] % 2)
						first[en]--;
					break;
				}
			}
		}
	}
	return first[en];
}

unsigned long long int followSet(nonterminal en) {

	/* check for indirect right recursion in the grammar */
	if(follow[en] != 0)
		return follow[en];
	int i;
	int isEmpty = 0;
	for(i = 0; i < num_rules; i++) {
		rhsNode * node = G[en].head;
		while(node != NULL) {
			if(node.sym.tag == T) {
				node = node -> next;
				continue;
			}
			else {
				if(node.sym.NT == en) {
					unsigned long long int tmp = firstFollow(node -> next);
					follow[en] = setUnion(follow[en], tmp);
					if(follow[en] % 2)
						follow[en]--;
					if(tmp % 2) {
						if(G[en].left != en)s
							follow[en] = setUnion(follow[en], followSet(G[en].left));
					}
				}
			}
		}
	}
	return follow[en];
}

unsigned long long int firstFollow(rhsNode * node) {
	
	unsigned long long int tmp = 0;
	rhsNode * tmpNode = node;
	while(tmpNode != NULL) {
		if(tmpNode.tag == T) {
			tmp = setUnion(tmp, (unsigned long long int) 1 << (tmp -> sym).T)
			if(tmp % 2)
				tmp--;
			break;
		}
		else {
			tmp = setUnion(tmp, first[(tmpNode -> sym).NT]);
			if(!findinSet(first[(tmpNode -> syn).NT], 0)) {
				if(tmp % 2)
					tmp--;
				break;
			}
			tmpNode = tmpNode -> next;
		}
	}
	return tmp;
}

int main() {
	populateGrammar("grammar.erp");
}