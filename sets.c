// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef enum nts {
//     PROGRAM,	
//     MODULEDECLARATIONS,
//     MODULEDECLARATION,	
//     OTHERMODULES,			
//     DRIVERMODULE,			
//     MODULE,			
//     RET,				
//     INPUT_PLIST,			
//     INPUT_PLISTNEW,	
//     OUTPUT_PLIST,			
//     OUTPUT_PLISTNEW,	
//     TYPE,					
//     DATATYPE,				
//     MODULEDEF,				
//     STATEMENTS,			
//     STATEMENT,				
//     IOSTMT,				
//     WHICHID,				
//     INDEX,					
//     SIMPLESTMT,		
//     ASSIGNMENTSTMT,	
//     MODULEREUSESTMT,		
//     OPTIONAL,				
//     IDLIST,				
//     IDLISTNEW,				
//     EXPRESSION,			
//     ARITHORBOOLEXPR,
//     ARITHORBOOLEXPRNEW,
//     RELOPEXPR,
//     RELOPEXPRNEW,
//     ARITHMETICEXPR,	
//     ARITHMETICEXPRNEW,		
//     TERM,					
//     TERMNEW,				
//     FACTOR,			
//     VARNEW,				
//     VAR,				
//     PM,				
//     MD,				
//     LOGICALOP,				
//     RELATIONALOP,			
//     DECLARESTMT,			
//     CONDIONALSTMT,			
//     CASESTMTS,				
//     CASESTMTSNEW,			
//     VALUE,					
//     DEFAULT,			
//     ITERATIVESTMT,			
//     RANGE				
// } nts;

// struct entry {
//     nts term;
//     char *val;
// };

// struct entry map[] = {
//     PROGRAM,            "program",		
//     MODULEDECLARATIONS, "moduleDeclarations",
//     MODULEDECLARATION,	"moduleDeclaration",
//     OTHERMODULES,       "otherModules",		
//     DRIVERMODULE,       "driverModule",		
//     MODULE,             "module",	
//     RET,                "ret",				
//     INPUT_PLIST,        "input_plist",			
//     INPUT_PLISTNEW,     "input_plistNew",
//     OUTPUT_PLIST,		"output_plist",	
//     OUTPUT_PLISTNEW,	"output_plistNew",
//     TYPE,	            "type",				
//     DATATYPE,			"dataType",	
//     MODULEDEF,			"moduleDef",	
//     STATEMENTS,			"statements",
//     STATEMENT,			"statement",	
//     IOSTMT,				"ioStmt",
//     WHICHID,			"whichId",	
//     INDEX,				"index",	
//     SIMPLESTMT,		    "simpleStmt",
//     ASSIGNMENTSTMT,	    "assignmentStmt",
//     MODULEREUSESTMT,	"moduleReuseStmt",	
//     OPTIONAL,			"optional",	
//     IDLIST,				"idList",
//     IDLISTNEW,			"idListNew",	
//     EXPRESSION,			"expression",
//     ARITHORBOOLEXPR,    "arithOrBoolExpr",
//     ARITHORBOOLEXPRNEW, "arithOrBoolExprNew",
//     RELOPEXPR,          "RelopExpr",
//     RELOPEXPRNEW,       "RelopExprNew",
//     ARITHMETICEXPR,	    "arithmeticExpr",
//     ARITHMETICEXPRNEW,	"arithmeticExprNew",	
//     TERM,				"term",	
//     TERMNEW,			"termNew",	
//     FACTOR,			    "factor",
//     VARNEW,				"varNew",
//     VAR,				"var",
//     PM,				    "pm",
//     MD,				    "md",
//     LOGICALOP,			"logicalOp",	
//     RELATIONALOP,		"relationalOp",	
//     DECLARESTMT,		"declareStmt",	
//     CONDIONALSTMT,		"condionalStmt",	
//     CASESTMTS,			"caseStmts",	
//     CASESTMTSNEW,		"caseStmtsNew",	
//     VALUE,				"value",	
//     DEFAULT,			"default",
//     ITERATIVESTMT,		"iterativeStmt",	
//     RANGE,				"range"
// };

// struct symbol {
//     union {
//         char* token;
//         nts non_term;
//     };
//     /* when set, indicates non-terminal, else a token */
//     unsigned tag:1;
//     struct symbol* next;
// };

// /* assumes input string of form "<([a-z]|[A-Z]|[0-9])*>" */
// nts lookup_nt(const char* key) {
    
//     int i = 0;
//     char *name = map[i].val;
//     while (name) {
//         if (strlen(name) != (strlen(key)-2)) {
//             name = map[++i].val;
//             continue;
//         }
//         if (strncmp(name, key+1, strlen(key)-2) == 0)
//             return map[i].term;
//         name = map[++i].val;
//     }
//     return 0;
// } 

// void mov_next(struct symbol** curr) {
//     while (*curr && !(((*curr)->tag == 0) && (strcmp((*curr)->token, "|")==0))) {
//         *curr = (*curr)->next;
//     } 
// }

// int first_set(struct symbol** table, int index) {
//     // firt of which NT : index
//     char *name = map[index].val;
//     int term = map[index].term;

//     //printf("First set for %s: {", name);
//     /* Compute first set for this term */

//     struct symbol* next = table[term];

//     int glob_e = 0;
//     while (next) {

//         if (next->tag==0) {
//             /* we have a token */
//             printf(",%s",next->token);
//             if (strcmp(next->token, "E")==0) {
//                 glob_e = 1;
//             }
//         } else {
//             /* we have a term, recurse into it and find out whether it can be empty */
//             int pos_e = 1;
//             while (pos_e && next && !((next->tag==0)&&(strcmp(next->token, "|")==0))) {
//                 if (next->tag==0) {
//                     printf(",%s",next->token);
//                     pos_e = 0;
//                     break;
//                 } 

//                 if (next->non_term == term) {
//                     pos_e = 0;
//                     break;
//                 }
//                 pos_e = first_set(table, next->non_term);
//                 next = next->next;
//             }
//             if (pos_e) 
//                 glob_e = 1;
//         }

//         mov_next(&next);
//         if (next)
//             next = next->next;
//         else break;    
//     }

//     return glob_e;

// }

// void follow_set(struct symbol** table, int table_size, int index) {
//     char *name = map[index].val;
//     int term = map[index].term;

//     /* look for wherever this NT is appearing */
//     for (int i=0; i<table_size; i++) {
//         if (i == term) continue;

//         struct symbol* next = table[i];

//         while (next) {
//             int mov= 0;
//             if (next->tag && (next->non_term == term)) {
//                 /* then follow it ? */
//                 if (next->next) {
//                     next = next->next;
//                     if (next->tag) {
//                         first_set(table, next->non_term);
//                     } else {
//                         /* it maybe a | */
//                         if (strcmp(next->token, "|")==0) {
//                             mov = 1;
//                             break;
//                         }
//                         printf(", %s", next->token);
//                     }
//                 } else {
//                     /* nothing follows this, so just follow whatever derives it */
//                     first_set(table, i);
//                 }
//             }
//             if (mov) {
//                 mov_next(&next);
//             }
//             else {
//                 next = next->next;
//             }
//         }
//     }
// }

// int main(void) {


//     FILE * fp;
//     char * line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     int num_lines = 0;

//     fp = fopen("erplag", "r");
//     if (fp == NULL)
//         exit(EXIT_FAILURE);

//     while ((read = getline(&line, &len, fp)) != -1) {
//         /* line of length read */
//         num_lines++;
//     }    

//     fseek(fp, 0, SEEK_SET);
//     struct symbol **table = malloc(num_lines*(sizeof(struct symbol *)));

//     while ((read = getline(&line, &len, fp)) != -1) {
//         /* line of length read */

//         /* tokenize each line str -> line*/
//         char *tok;
//         printf ("Splitting string \"%s\" into tokens:\n",line);
//         tok = strtok (line," ,.-\t\n");
//         int first = 1;
//         struct symbol* prev = NULL;
//         int rule_ptr = 0;
//         while (tok != NULL)
//         {
//             printf ("%s\n",tok);
//             if (first) {
//                 first = 0;
//                 rule_ptr = lookup_nt(tok);
//                 tok = strtok(NULL, " ,.-\t\n");
//                 tok = strtok(NULL, " ,.-\t\n");
//                 continue;
//             } else {
        
//                 struct symbol* new_symbol = malloc(sizeof(struct symbol));

//                 if (tok[0] == '<') {
//                     /* it is a NT */
//                     new_symbol->tag = 1;
//                     new_symbol->non_term = lookup_nt(tok);
//                 } else {
//                     /* it is a term */
//                     new_symbol->tag = 0;
//                     new_symbol->token = malloc(strlen(tok));
//                     strcpy(new_symbol->token, tok);
//                 }
                
//                 if (prev == NULL) 
//                     table[rule_ptr] = new_symbol;
//                 else 
//                     prev->next = new_symbol;    

//                 prev = new_symbol;
//                 tok = strtok(NULL, " ,.-\t\n");
//             }
//         }
//         prev->next = NULL;
//     }

//     printf(" --- Printing first sets ---");

//     /* We have constructed the table, now apply logic of first sets */
//     for (int i=0; i< num_lines; i++) {
//         printf("First set for <%s>: ", map[i].val);
//         first_set(table, map[i].term);
//         printf("\n");
//     }

//     printf(" --- Printing follow sets ---\n");

//     for (int i=0; i< num_lines; i++) {
//         printf("Follow set for <%s>: ", map[i].val);
//         follow_set(table, num_lines, map[i].term);
//         printf("\n");
//     }

//     fclose(fp);
//     if (line)
//         free(line);
//     exit(EXIT_SUCCESS);
// }



#include "parserDef.h"

HashTable hashtable ;

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

// void insertElement (int idx, char * str, typeOfSymbol t, int en) {
// 	hashNode * prev = NULL, * curr = NULL;
	
// 	/* initializing the new Node to be inserted */
// 	hashNode * new = (hashNode *)malloc(sizeof(hashNode));
// 	symbol s;
// 	if(t == T)
// 		s.T = en;
// 	else
// 		s.NT = en;
// 	new -> sym = s;
// 	strcpy(new -> str, str);
// 	new -> tag = t;
// 	new -> next = NULL;

// 	curr = HT[idx].head;
	
// 	if(HT[idx].count == 0) {
// 		HT[idx].head = new;
// 		HT[idx].count++;
// 		return;
// 	}
	
// 	while(curr != NULL) {
// 		prev = curr;
// 		curr = curr -> next;
// 	}
// 	prev -> next = new;
// 	HT[idx].count++;
// }

// hashNode * hashLookup(int idx, char * str) {

// 	hashNode * curr = HT[idx].head;
// 	while(curr != NULL) {
// 		if(strcmp(curr -> str, str) == 0)
// 			break;
// 		curr = curr -> next;
// 	}
// 	return curr;
// }

void populateHashTable() {

	hashtable = getHashTable();
	int i;
	for(i = 0; i < 48; i++) {

		// int idx = hash(nonterminals[i]);
		// insertElement(idx, nonterminals[i], NT, i);

		/* New hash */
		char* key = nonterminals[i];
		stackElement* st = malloc(sizeof(stackElement));
		symbol s;
		s.NT = i;
		st->sym = s;
		st->tag = NT;
		hashtable = insertToTable(hashtable, key, st, stringHash);
	}

	for(i = 0; i < 58; i++) {
		// int idx = hash(terminals[i]);
		// insertElement(idx, terminals[i], T, i);

		/* New hash */
		char* key = terminals[i];
		stackElement* st = malloc(sizeof(stackElement));
		symbol s;
		s.T = i;
		st->sym = s;
		st->tag = T;
		hashtable = insertToTable(hashtable, key, st, stringHash);
	}
}

void add_grammarNode(char* str, List list) {
    // stackElement* newElement = (stackElement*) malloc(sizeof(stackElement));
    // int idx = hash(str);
    // hashNode* lookup = hashLookup(idx, str);
    // if(str[0] <= 'Z') {
    //     (newElement -> sym).T = (lookup -> sym).T;
    // } else {
    //     (newElement -> sym).NT = (lookup -> sym).NT;
    // }
    // newElement->tag = lookup->tag;
    list = insertToList(list, getDataFromTable(hashtable, str, stringHash), BACK);
}

void populateGrammar(char * filename) {

	FILE * fp = fopen(filename, "r");
	char str[201];
	int lhs = 1;
	int grammar_id = 0;
	while(fgets(str, 200, fp) != NULL) {
		char * tok = strtok(str, " \t\n");
		// int idx = hash(tok);
		// hashNode * lookup = hashLookup(idx, tok);
        stackElement* lookup = getDataFromTable(hashtable, tok, stringHash);
		G[grammar_id].left = (lookup -> sym).NT;
		G[grammar_id].list = getList();
		Node* prev = NULL;
		while(tok != NULL) {
			tok = strtok(NULL, " \t\n");
			if(tok == NULL)
				break;
			if(strcmp(tok, "|") == 0) {
				prev = NULL;
				grammar_id++;
				G[grammar_id].left = (lookup -> sym).NT;
                G[grammar_id].list = getList();
			}
			else if(strcmp(tok, ":") ) {
                add_grammarNode(tok, G[grammar_id].list);
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
        Node* node = G[i].list->head;
		while(node != NULL) {
            stackElement* elem = node->data;
			if(elem -> tag == T) {
				first[nonT] = setUnion(first[nonT], ((unsigned long long int)1 << (elem -> sym).T));
				if((first[nonT] % 2) && ((elem -> sym).T != 0)) {
					first[nonT]--;
				}
				break;
			}
			else {
				unsigned long long tmp = firstSet((elem -> sym).NT);
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

unsigned long long int firstFollow(Node * node) {
	
	unsigned long long int tmp = 0;
	Node * tmpNode = node;
	while(tmpNode != NULL) {
        stackElement* elem = tmpNode->data;
		if(elem -> tag == T) {
			tmp = setUnion(tmp, (unsigned long long int) 1 << (elem -> sym).T);
			if((tmp % 2) && ((elem -> sym).T != 0))
				tmp--;
			break;
		}
		else {
			tmp = setUnion(tmp, first[(elem -> sym).NT]);
			if(!findinSet(first[(elem -> sym).NT], 0)) {
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
        Node* node = G[i].list->head;
		while(node != NULL) {
            stackElement* elem = node->data;
			if(elem -> tag == T) {
				node = node -> next;
				continue;
			}
			else {
				if((elem -> sym).NT == nonT) {
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
		F[i].firstset = first[i];
	}
	for(i = 0; i < NUM_NONTERM; i++) {
		followSet(i);
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
		unsigned long long int first_set = firstFollow(G[i].list->head); //F[left].firstset;
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

void syntaxError(int * lookAhead, Stack S) {

	token * tok = tokenStream[*lookAhead];
	stackElement * st = top(S);
	printf("Syntactic Error on line %d:", tok -> line_num);
	if(st -> tag == T) {
		printf("Expecting %s\n", terminals[(st -> sym).T]);
	}
	else {
		printf("%sNoooo\n", nonterminals[(st -> sym).NT]);
		unsigned long long int fs = F[st -> sym.NT].firstset;
		int i;
		printf("Expected ");
		for(i = 1; i < NUM_TERM; i++) {
			if(findinSet(fs, i) == 1) {
				printf("%s ", terminals[i]);
			}
		}
		printf("\n");
	}

	/* moving the lookahead pointer until the next (SEMICOL/DOLLAR) */
	while(*lookAhead < ntokens) {
		tok = tokenStream[*lookAhead];
		*lookAhead = *lookAhead + 1;
		if(tok -> id == SEMICOL || tok -> id == DOLLAR)
			break;
	}

	/* popping the stack until:
	We pop out 1 SEMICOL/DOLLAR */
	while(numElementsInStack(S) > 0) {
		stackElement * tp = top(S);
		S = pop(S);
		if(tp -> tag == T && tp -> sym.T == SEMICOL)
			break;
		else if(tp -> tag == T && tp -> sym.T == DOLLAR)
			break;
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
	while(lookAhead <= ntokens) {
		if(numElementsInStack(S) == 0) {
			printf("Parsing Complete\n");
			break;
		}
		stackElement * Top = top(S);
		token * nextToken = tokenStream[lookAhead];
		terminal t = nextToken -> id;
		// printf("%s\n", terminals[t]);
		if(Top -> tag == T) {
			if(t == (Top -> sym).T) {
				fflush(stdout);
				lookAhead++;
				S = pop(S);
				if(numElementsInStack(S) > 0)
					// printf("%s\n", terminals[((stackElement *)top(S)) -> sym.T]);
					S = pop(S);
			}
			else {
				syntaxError(&lookAhead, S);
			}
		}
		else {
			unsigned long long int first_set = F[(Top -> sym).NT].firstset;
			unsigned long long int follow_set = F[(Top -> sym).NT].followset;
			
			int parseTableVal = parseTable[(Top -> sym).NT][nextToken -> id];
			
			if(parseTableVal >= 0) {
				Node * node = G[parseTableVal].list->end;
				Node* printNode = G[parseTableVal].list->head;
				printf("%s --> ", nonterminals[(Top -> sym).NT]);

				if(((stackElement *)(node -> data))->sym.T > 60 && ((stackElement *)(node -> data))->sym.NT > 60) {
					printf("caught %d %d\n", parseTableVal, lookAhead);
					return;
				}
				// insertChildren(Top -> tn, node);
				// treeNode * ch = Top -> tn -> child;
				


				S = pop(S);
				while(node != NULL) {
                    if(!(((stackElement*)node->data)->tag == T && ((stackElement*)node->data)->sym.T == EMPTY)) {
                        /* Non-Terminal or terminal != EMPTY */
                        S = push(S, node->data); 
                    }
					if(((stackElement*)(printNode->data))->tag == T) {
						printf("%s  ", terminals[((stackElement*)printNode->data)->sym.T]);
					} else {
						printf("%s  ", nonterminals[((stackElement*)printNode->data)->sym.NT]);
					}
					node = node->prev;
					printNode = printNode->next;
				}
                printf("\n");
				// Stack tmp = getStack();
				// while(node != NULL) {
				// 	tmp = push(tmp, node);
				// 	if(node -> tag == T)
				// 		printf("%s\t", terminals[node -> sym.T]);
				// 	else
				// 		printf("%s\t", nonterminals[node -> sym.NT]);
				// 	node = node -> next;
				// }
				// printf("\n");
				// while(node = top(tmp)) {
				// 	stackElement * new = (stackElement *)malloc(sizeof(stackElement));
				// 	new -> sym = node -> sym;
				// 	new -> tag = node -> tag;
				// 	tmp = pop(tmp);
				// 	if((node -> tag == T)&&(node -> sym.T == 0))
				// 		continue;
				// 	S = push(S, new);
				// }

			}
			else {
				syntaxError(&lookAhead, S);
			}
		}
	}
}

void printElement(void* hashEl) {
    hashElement* currEl = (hashElement*) hashEl;
    printf("key: %s", (char*)currEl->key);
    stackElement* el = currEl->data;
    if(el->tag == T) {
        printf(", terminal: %d", el->sym.T);
    } else {
        printf(", nonterminal: %d", el->sym.NT);
    }
}

void parserInit(char * filename) {
	num_rules = 0;
	// int i;
	// for(i = 0; i < 100; i++) {
	// 	first[i] = 0;
	// 	follow[i] = 0;
	// }
	// for(i = 0; i < HASH_TABLE_SIZE; i++) {
	// 	HT[i].head = NULL;
	// 	HT[i].count = 0;
	// }
	populateHashTable();
	populateGrammar(filename);

    // printHashTable(hashtable, printElement);
}

int main() {
    parserInit("grammar.erp");

    // printing grammar rules [array of linked_lists]
    printf("****** Grmmar Rules ******\n");
    int i, j;

    // printHashTable(hashtable, printElement);
    //stackElement* st = hashtable[stringHash("program")];
    // printf("%d %d\n", hash("MINUS"), hash("iterativeStmt"));
    for(i = 0; i < num_rules; i++) {
        printf("%s :", nonterminals[G[i].left]);
        Node* curr = G[i].list->head;
        while(curr != NULL) {
            stackElement* elem = curr->data;
            // printf("{tag: %d, ", curr->tag);
            if(elem->tag == T) {
                printf(" %s", terminals[elem->sym.T]);
            } else {
                printf(" %s", nonterminals[elem->sym.NT]);
            }
            curr = curr->next;
        }
        printf("\n");
    }

    ComputeFirstAndFollowSets();

    printf("\n****** First Sets ******\n");
    // for(i = 0; i < NUM_NONTERM; i++)
    //     firstSet(i);
    for(i = 0; i < NUM_NONTERM; i++) {
        printf("%s:    ", nonterminals[i]);
        for(j = 0; j < 58; j ++)
            if(findinSet(first[i], j))
                printf("%s ", terminals[j]);
        printf("\n");    
    }
    printf("\n****** Follow Sets ******\n");
    // for(i = 0; i < NUM_NONTERM; i++)
    //     followSet(i);
    for(i = 0; i < NUM_NONTERM; i++) {
        printf("%s:    ", nonterminals[i]);
        for(j = 0; j < 58; j ++)
            if(findinSet(follow[i], j))
                printf("%s ", terminals[j]);
        printf("\n"); 
    }

    createParseTable();
    printf("\n ****** Parse Table ******\n");
    for(i = -1; i < NUM_NONTERM; i++) {
        printf("%s,", nonterminals[i]);
        for(j = 1; j < NUM_TERM; j++) {
            if(i == -1) 
                printf("%s,", terminals[j]);
            else
                printf("%d,", parseTable[i][j]);
        }
        printf("\n");
    }

    parseInputSourceCode("prog.eg");
}