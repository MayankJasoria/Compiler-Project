
#include "parserDef.h"

terminal * delimit[] = {SEMICOL};

void insertElement (int idx, char * str, typeOfSymbol t, int en) {
	hashNode * prev = NULL, * curr = NULL;
	
	/* initializing the new Node to be inserted */
	hashNode * new = (hashNode *)malloc(sizeof(hashNode));
	symbol s;
	if(t == T)
		s.T = en;
	else
		s.NT = en;
	new -> sym = s;
	strcpy(new -> str, str);
	new -> tag = t;
	new -> next = NULL;

	curr = HT[idx].head;
	
	if(HT[idx].count == 0) {
		HT[idx].head = new;
		HT[idx].count++;
		return;
	}
	
	while(curr != NULL) {
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = new;
	HT[idx].count++;
}

hashNode * hashLookup(int idx, char * str) {

	hashNode * curr = HT[idx].head;
	while(curr != NULL) {
		if(strcmp(curr -> str, str) == 0)
			break;
		curr = curr -> next;
	}
	return curr;
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
		"moduleReuseStmt",
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
		"RETURNS",
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
		"GE",
		"GT",
		"EQ",
		"NE",
		"DEF",
		"ENDDEF",
		"COLON",
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
		"DRIVERENDDEF",
		"DOLLAR"
	};
	for(i = 0; i < 58; i++) {
		int idx = hash(terminals[i]);
		insertElement(idx, terminals[i], T, i);
	}
}

rhsNode * make_rhsNode(char * str, rhsNode * prev, int id) {
	rhsNode * r = (rhsNode *)malloc(sizeof(rhsNode));
	int idx = hash(str);
	hashNode * lookup = hashLookup(idx, str);
	if(str[0] >= 'A')
		(r -> sym).T = (lookup -> sym).T;
	else
		(r -> sym).NT = (lookup -> sym).NT;
	r -> tag = lookup -> tag;
	r -> next = NULL;
	if(prev == NULL) {
		G[id].head = r;
		// printf("HEAD:       %d   %d   %d       %s\n", idx, (r -> sym).T, r -> tag, str);
	}
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
		hashNode * lookup = hashLookup(idx, tok);
		G[grammar_id].left = (lookup -> sym).NT;
		rhsNode * prev = (rhsNode *)malloc(sizeof(rhsNode));
		prev = NULL;
		while(tok != NULL) {
			tok = strtok(NULL, " \t\n");
			if(tok == NULL)
				break;
			if(strcmp(tok, "|") == 0) {
				prev = NULL;
				grammar_id++;
				G[grammar_id].left = (lookup -> sym).NT;
			}
			else if(strcmp(tok, ":") ) {
				rhsNode * r = make_rhsNode(tok, prev, grammar_id);
				prev = r;
			}
		}
		grammar_id++;
	}
	num_rules = grammar_id;
}

unsigned long long int setUnion (unsigned long long int a, unsigned long long int b) {
	return a | b;
}

int findinSet(unsigned long long int a, int i) {
	unsigned long long int tmp = (unsigned long long int) 1 << i;
	if(tmp & a)
		return 1;
	return 0;
}

unsigned long long int firstSet(nonterminal nonT) {
	
	/* check this */
	if(first[nonT] != 0)
		return first[nonT];
	int i;
	int isEmpty = 0;
	for(i = 0; i < num_rules; i++) {
		if(G[i].left < nonT)
			continue;
		else if(G[i].left > nonT)
			break;
		rhsNode * node = G[i].head;
		while(node != NULL) {
			if(node -> tag == T) {
				first[nonT] = setUnion(first[nonT], ((unsigned long long int)1 << (node -> sym).T));
				if((first[nonT] % 2) && ((node -> sym).T != 0)) {
					first[nonT]--;
				}
				break;
			}
			else {
				unsigned long long tmp = firstSet((node -> sym).NT);
				if(findinSet(tmp, 0)) {
					first[nonT] = setUnion(first[nonT], tmp);
					node = node -> next;
					continue;
				}
				else {
					first[nonT] = setUnion(first[nonT], tmp);
					if(first[nonT] % 2)
						first[nonT]--;
					break;
				}
			}
		}
	}
	return first[nonT];
}

unsigned long long int firstFollow(rhsNode * node) {
	
	unsigned long long int tmp = 0;
	rhsNode * tmpNode = node;
	while(tmpNode != NULL) {
		if(tmpNode -> tag == T) {
			tmp = setUnion(tmp, (unsigned long long int) 1 << (tmpNode -> sym).T);
			if((tmp % 2) && ((tmpNode -> sym).T != 0))
				tmp--;
			break;
		}
		else {
			tmp = setUnion(tmp, first[(tmpNode -> sym).NT]);
			if(!findinSet(first[(tmpNode -> sym).NT], 0)) {
				if(tmp % 2)
					tmp--;
				break;
			}
			tmpNode = tmpNode -> next;
		}
	}
	return tmp;
}

unsigned long long int followSet(nonterminal nonT) {

	/* check for indirect right recursion in the grammar */
	if(follow[nonT] != 0 && nonT != 0)
		return follow[nonT];
	if(nonT == 0)
		follow[nonT] = setUnion(follow[nonT], (unsigned long long int) 1 << 57);
	int i;
	int isEmpty = 0;
	for(i = 0; i < num_rules; i++) {
		rhsNode * node = G[i].head;
		while(node != NULL) {
			if(node -> tag == T) {
				node = node -> next;
				continue;
			}
			else {
				if((node -> sym).NT == nonT) {
					unsigned long long int tmp = 0;
					if(node -> next != NULL)
						tmp = firstFollow(node -> next);
					follow[nonT] = setUnion(follow[nonT], tmp);
					if(follow[nonT] % 2)
						follow[nonT]--;
					if(tmp % 2 || (node -> next == NULL)) {
						if(G[i].left != nonT)
							follow[nonT] = setUnion(follow[nonT], followSet(G[i].left));
					}
					node = node -> next;
				}
				else
					node = node -> next;
			}
		}
	}
	return follow[nonT];
}

void ComputeFirstAndFollowSets() {
	int i = 0;
	for(i = 0; i < NUM_NONTERM; i++) {
		firstSet(i);
		followSet(i);
		F[i].firstset = first[i];
		F[i].followset = follow[i];
	}
}

void createParseTable() {
	/* i denotes the rule number */
	/*
		-1 : syntactic error
		-2 : syn
		otherwise : corresponding rule number
	*/
	int i, j;
	for(i = 0; i < NUM_NONTERM; i++)
        for(j = 0; j < NUM_TERM; j++)
            parseTable[i][j] = -1;
	for(i = 0; i < num_rules; i++) {
		nonterminal left = G[i].left;
		unsigned long long int first_set = F[left].firstset;
		unsigned long long int follow_set = F[left].followset;
		for(j = 1; j < NUM_TERM; j++) {
			if(findinSet(first_set, j))
				parseTable[left][j] = i;
		}
		for(j = 1; j < NUM_TERM; j++) {
			if(findinSet(first_set, 0) && findinSet(follow_set, j))
				parseTable[left][j] = i;
			else if(findinSet(follow_set, j))
				parseTable[left][j] = -2;
		}
	}
}

void parseInputSourceCode(char *testcaseFile) {

	/* Fetching the tokens from the lexer by reading blocks from the source code file */
	FILE * fp = fopen(testcaseFile, "r");
	lexerinit();
	while(endofLexer == 0) {
		fp = getStream(fp);
	}
	Stack S = getStack();

	/* pushing Dollar and <program> onto the stack */
	stackElement * s = (stackElement *)malloc(sizeof(stackElement));
	s -> sym.T = DOLLAR;
	s -> tag = T;
	S = push(S, s);

	s = (stackElement *)malloc(sizeof(stackElement));
	s -> sym.NT = program;
	s -> tag = NT;
	S = push(S, s);

	/* pushing DOLLAR at the end of the token Stream. */
	if(ntokens >= tokenStream_cap) {
		tokenStream = realloc(tokenStream, 2*tokenStream_cap*sizeof(token *));
		tokenStream_cap *= 2;
	}
	token * endToken = makeNewToken(57);
	tokenStream[ntokens] = endToken;
	ntokens++;

	/* declaring the lookAhead pointer */
	int lookAhead = 0;
	while(lookAhead < ntokens) {
		stackElement * Top = top(S);
		token * nextToken = tokenStream[lookAhead];
		terminal t = nextToken -> id;
		if(Top -> tag == T) {
			if(t == (Top -> sym).T) {
				lookAhead++;
				S = pop(S);
			}
			else {
				/* only took SEMICOL as a delimiter */
				while(lookAhead < ntokens && t != (Top -> sym).T && t != SEMICOL) {
					lookAhead++;
					nextToken = tokenStream[lookAhead];
					t = nextToken -> id;
				} 
			}
		}
		int ptEntry = parseTable[Top -> ]
	}
}

void parserInit(char * filename) {
	num_rules = 0;
	int i;
	for(i = 0; i < 100; i++) {
		first[i] = 0;
		follow[i] = 0;
	}
	for(i = 0; i < HASH_TABLE_SIZE; i++) {
		HT[i].head = NULL;
		HT[i].count = 0;
	}
	populateHashTable();
	populateGrammar(filename);
}

// int main() {
// 	populateGrammar("grammar.erp");
// }