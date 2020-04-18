/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include "parserDef.h"

#define ull unsigned long long int

void sdsd(void* data) {
	stackElement * tmp = data;
	// printf("%d %s %s",stackElement->tag, terminals[stackElement->sym.T], nonterminals[stackElement->sym.NT]);
	if(tmp->tag == T) {
		printf("%d %s", tmp->tag, terminals[tmp->sym.T]);	
	} else {
		printf("%d %s", tmp->tag, nonterminals[tmp->sym.T]);
	}
}

char * nonterminals[] = { 
			"program",
			"moduleDeclarations",
			"moduleDeclaration",
			"otherModules",
			"driverModule",
			"module",
			"ret",
			"input_plist",
			"n1",
			"output_plist",
			"n2",
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
			"n3",
			"expression",
			"arithmeticOrBooleanExpr",
			"n7",
			"anyTerm",
			"n8",
			"arithmeticExpr",	
			"n4",
			"term",
			"n5",
			"factor",
			"var",
			"op1",
			"op2",
			"logicalOp",
			"relationalOp",
			"declareStmt",
			"condionalStmt",
			"caseStmts",
			"n9",
			"value",
			"default",
			"iterativeStmt",
			"range",
			"range_arrays",
			"boolConstt",
			"var_id_num",
			"whichStmt",
			"lvalueIDStmt",
			"lvalueARRStmt",
			"u",
			"unary_op",
			"new_NT"
		};
	
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

terminal delim[] = {SEMICOL, END, ENDDEF, DRIVERENDDEF, BC, SQBC, DOLLAR, COMMA, COLON};

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

	int i;
	for(i = 0; i < NUM_NONTERM; i++) {
		int idx = hash(nonterminals[i]);
		insertElement(idx, nonterminals[i], NT, i);
	}

	for(i = 0; i < NUM_TERM; i++) {
		int idx = hash(terminals[i]);
		insertElement(idx, terminals[i], T, i);
	}
}

rhsNode * make_rhsNode(char * str, rhsNode * prev, int id) {
	rhsNode * r = (rhsNode *)malloc(sizeof(rhsNode));
	int idx = hash(str);
	hashNode * lookup = hashLookup(idx, str);
	if(str[0] <= 'Z')
		(r -> sym).T = (lookup -> sym).T;
	else
		(r -> sym).NT = (lookup -> sym).NT;
	r -> tag = lookup -> tag;
	r -> next = NULL;
	if(prev == NULL) {
		G[id].head = r;
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
		char * tok = strtok(str, " \t\n\r");
		int idx = hash(tok);
		hashNode * lookup = hashLookup(idx, tok);
		G[grammar_id].left = (lookup -> sym).NT;
		rhsNode * prev = (rhsNode *)malloc(sizeof(rhsNode));
		prev = NULL;
		while(tok != NULL) {
			tok = strtok(NULL, " \t\n\r");
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
	}
	for(i = 0; i < NUM_NONTERM; i++) {
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
		unsigned long long int first_set = firstFollow(G[i].head); 
		unsigned long long int follow_set = F[left].followset;
		for(j = 1; j < NUM_TERM; j++) {
			if(findinSet(first_set, j))
				parseTable[left][j] = i;
		}
		for(j = 1; j < NUM_TERM; j++) {
			if(findinSet(first_set, 0) && findinSet(follow_set, j))
				parseTable[left][j] = i;
			else if((findinSet(first_set, 0) == 0) && (findinSet(follow_set, j)) && (parseTable[left][j] < 0))
				parseTable[left][j] = -2;
		}
	}
}

token * syntaxError(token * tok, Stack *S, FILE * fp) {

	syntacticallyCorrect = False;
	stackElement * st = top(*S);
	// printf(KRED "Syntax Error " KNRM "on line " KMAG "%d" KNRM ": \n", tok -> line_num);
	printf("Line number (%d): syntax error ", line_num);
	int num_delim = sizeof(delim)/sizeof(delim[0]);
	terminal del;
	int i;
	boolean miss = False;
	if(st -> tag == T) {
		printf(KYEL "-- missing ");
		miss = true;
	}
	while(st -> tag == T) {
		if(st -> sym.T == tok -> id) {
			printf("\n");
			return tok;
		}
		printf(KCYN " '%s'" KNRM, terminals[st -> sym.T]);
		st -> tn -> tok = tok;
		*S = pop(*S);
		if(numElementsInStack(*S) == 0)
			return tok;
		st = top(*S);
	}
	if(miss) {
		printf(" ");
	}

	ull follow_set = F[st -> sym.NT].followset;
	ull first_set = F[st -> sym.NT].firstset;

	boolean unexp = False;
	while(tok -> id != 57) {
		if((findinSet(follow_set, tok -> id))) {
			*S = pop(*S);
			printf(" ");
			printf(KYEL "-- expected one of: ");
			for(i = 0; i < NUM_TERM; i++) {
				if(findinSet(first_set, i)) {
					printf(KCYN "'%s' " KNRM, terminals[i]);
				}
			}
			printf("\n");
			return tok;
			break;
		}
		if(findinSet(first_set, tok -> id)) {
			printf("\n");
			return tok;
		}
		else {
			if(!unexp) {
				printf(KYEL "-- unexpected ");
				unexp = True;
			}
			printf(KCYN "'%s' " KNRM, tok->lex);
		}
		tok = getNextToken(fp);
		if(tok -> id == DOLLAR) {
			*S = pop(*S);
			break;
		}
	}
	printf("\n");
	return tok;
}

void parseInputSourceCode(char *testcaseFile) {
	
	/* Fetching the tokens from the lexer by reading blocks from the source code file */
	FILE * fp = fopen(testcaseFile, "r");

	/* Check if the fp is valid */
	if (!fp) {
		printf("Error: source file '%s' could not be opened, exiting...\n", testcaseFile);

		/* Exiting right away, since there is no point returning to the main menu */
		exit(0); 
	}
	lexerinit();
	
	Stack S = getStack();

	/* pushing Dollar and <program> onto the stack */
	stackElement * s = (stackElement *)malloc(sizeof(stackElement));
	s -> sym.T = DOLLAR;
	s -> tag = T;
	s -> tn = NULL;
	S = push(S, s);

	s = (stackElement *)malloc(sizeof(stackElement));
	s -> sym.NT = program;
	s -> tag = NT;
	S = push(S, s);
	PT = (treeNode *)getTree(s);

	token * nextToken = getNextToken(fp);
	while(numElementsInStack(S) > 0) {
		// printf("%d\n", numElementsInStack(S));
		// printStack(S, sdsd);
		if(numElementsInStack(S) == 1 && syntacticallyCorrect) {
			printf(KGRN "Input source code is syntactically correct.\n" KNRM);
			break;
		}
	
		stackElement * Top = top(S);
		terminal t = nextToken -> id;
		// printf("%s\n", terminals[t]);
		// printf("%s\n", terminals[t]);
		if(Top -> tag == T) {
			if(t == (Top -> sym).T) {
				if(Top -> sym.T == DOLLAR) {
					if(syntacticallyCorrect) {
						printf(KGRN "Input source code is syntactically correct.\n" KNRM);
						break;
					} 
					else {
						printf(KRED "Compilation ended with errors.\n" KNRM);
						break;
						// error
					}
				}
				Top -> tn -> tok = nextToken;
				Top -> tn -> line_num = nextToken -> line_num;
				if(Top -> sym.T == 54) {
					strcpy(Top -> tn -> lex, nextToken -> lex); 
				}
				else if(Top -> sym.T == 52) {
					Top -> tn -> value.val_int = nextToken -> val.val_int;
				}
				else if(Top -> sym.T == 53) {
					Top -> tn -> value.val_float = nextToken -> val.val_float;
				}
				nextToken = getNextToken(fp);
				if(numElementsInStack(S) > 0)
					// printf("%s\n", terminals[((stackElement *)top(S)) -> sym.T]);
					S = pop(S);
			}
			else {
				nextToken = syntaxError(nextToken, &S, fp);
				if(nextToken -> id == DOLLAR && numElementsInStack(S) > 1) {
					printf(KRED "Compilation ended with errors.\n" KNRM);
					break;
				}
				printf("\n");
			}
		}
		else {
			unsigned long long int first_set = F[(Top -> sym).NT].firstset;
			unsigned long long int follow_set = F[(Top -> sym).NT].followset;
			
			int parseTableVal = parseTable[(Top -> sym).NT][nextToken -> id];
			
			if(parseTableVal >= 0) {
				rhsNode * node = G[parseTableVal].head;
				insertChildren(Top -> tn, node);
				treeNode * ch = Top -> tn -> child;
				Top -> tn -> rule_num = parseTableVal;
				S = pop(S);
				while(ch -> next != NULL) {
						ch = ch -> next;
				}
				// if(ch -> tag == T)
				// 	printf("%s\t", terminals[ch -> sym.T]);
				// else
				// 	printf("%s\t", nonterminals[ch -> sym.NT]);
				// printf("\n");
				while(ch != NULL) {
					stackElement * new = (stackElement *)malloc(sizeof(stackElement));
					new -> sym = ch -> sym;
					new -> tag = ch -> tag;
					new -> tn = ch;
					ch = ch -> prev;
					if((new -> tag == T)&&(new -> sym.T == 0)) {
						continue;
					}
					S = push(S, new);
				}
				/* Remember : after popping from stack the memory get deallocated */
			}
			else {
				nextToken = syntaxError(nextToken, &S, fp);
				if(nextToken -> id == DOLLAR && numElementsInStack(S) > 1) {
					printf(KRED "Compilation ended with errors.\n" KNRM);
						break;
				}
				printf("\n");
			}
		}
	}
}

void inorder(Tree root) {

	if(root -> tag == T) {
		
		char * tokName;
		if(root -> sym.T == 0)
			tokName = "EMPTY";
		else
			tokName = terminals[root -> tok -> id];
		char isleaf = (root -> isLeaf)?'y':'n';
		char * s = (root -> tag == T)?terminals[root -> sym.T]:nonterminals[root -> sym.NT];
		if (root->line_num != -1) {
			if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2,root -> lex, root -> line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else if(root -> tag == T && root -> sym.T == 53) {
				printf(PRINT_FORMAT_BODY3,root -> lex, root -> line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else {
				printf(PRINT_FORMAT_BODY1, root -> lex, root -> line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);	
			}
		} else {

			char *line_num = "----";
			if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2_LINE_STR, root -> lex, line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else if(root -> tag == T && root -> sym.T == 53) {
				printf(PRINT_FORMAT_BODY3_LINE_STR, root -> lex, line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else {
				printf(PRINT_FORMAT_BODY1_LINE_STR, root -> lex, line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);	
			}

		}
		return;
	}
	treeNode * t = root -> child;
	if(t == NULL) {
		char * tokName;
		
		tokName = "----";
		char isleaf = (root -> isLeaf)?'y':'n';
		char * s = nonterminals[root -> sym.NT];
		if (root->line_num != -1) {
			if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2,root -> lex, root -> line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else if(root -> tag == T && root -> sym.T == 53) {
				printf(PRINT_FORMAT_BODY3,root -> lex, root -> line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else {
				printf(PRINT_FORMAT_BODY1, root -> lex, root -> line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);	
			}
		} else {

			char *line_num = "----";

			if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2_LINE_STR,root -> lex, line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else if(root -> tag == T && root -> sym.T == 53) {
				printf(PRINT_FORMAT_BODY3_LINE_STR,root -> lex, line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
			}
			else {
				printf(PRINT_FORMAT_BODY1_LINE_STR, root -> lex, line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);	
			}
		}
		return;
	}
	int i = 0;
	while(t != NULL) {
		inorder(t);
		if(i == 0) {

			char * tokName = (root -> tag == T)?terminals[root -> tok -> id]:"----";
			char isleaf = (root -> isLeaf)?'y':'n';
			char * s = (root -> tag == T)?terminals[root -> sym.T]:nonterminals[root -> sym.NT];
			if (root->line_num != -1) {
				if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2, root -> lex, root -> line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
				}
				else if(root -> tag == T && root -> sym.T == 53) {
					printf(PRINT_FORMAT_BODY3, root -> lex, root -> line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
							, isleaf, s, root->rule_num);
				}
				else if(root -> tag == NT && root -> sym.NT == 0) {
					printf(PRINT_FORMAT_BODY1, root -> lex, root -> line_num, tokName, "----", "[ROOT]"
							, isleaf, s, root->rule_num);	
				}
				else {
					printf(PRINT_FORMAT_BODY1, root -> lex, root -> line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
							, isleaf, s, root->rule_num);	
				}
			} else {
				char *line_num = "----";

				if(root -> tag == T && root -> sym.T == 52) {
				printf(PRINT_FORMAT_BODY2_LINE_STR, root -> lex, line_num, tokName, root -> value.val_int, nonterminals[root -> parent -> sym.NT]
						, isleaf, s, root->rule_num);
				}
				else if(root -> tag == T && root -> sym.T == 53) {
					printf(PRINT_FORMAT_BODY3_LINE_STR, root -> lex, line_num, tokName, root -> value.val_float, nonterminals[root -> parent -> sym.NT]
							, isleaf, s, root->rule_num);
				}
				else if(root -> tag == NT && root -> sym.NT == 0) {
					printf(PRINT_FORMAT_BODY1_LINE_STR, root -> lex, line_num, tokName, "----", "[ROOT]"
							, isleaf, s, root->rule_num);	
				}
				else {
					printf(PRINT_FORMAT_BODY1_LINE_STR, root -> lex, line_num, tokName, "----", nonterminals[root -> parent -> sym.NT]
							, isleaf, s, root->rule_num);	
				}
			}

			// if(root -> tag == T)
			// 	printf("%s %d\n", terminals[root -> sym.T], root -> id);
			// else 
			// 	printf("%s %d\n", nonterminals[root -> sym.NT], root -> id);
		}
		i++;
		t = t -> next;
	}
}

void printParseTree(Tree PT) {

	// FILE * fp = fopen(outfile, "w");

	printf(PRINT_FORMAT_HEADER, "Lexeme", "Lineno", "tokenName", "valIfNumber", "parentNodeSymbol", "IsLeafNode(y/n)", "nodeSymbol", "RuleNum");

	inorder(PT);
	// fclose(fp);
}


void parserInit(char * filename) {
	num_rules = 0;
	syntacticallyCorrect = 1;
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
