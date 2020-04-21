/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/
	
#ifndef _PARSERDEF
#define _PARSERDEF

#include <stdlib.h>
#include <string.h>
#include "lexerDef.h"
#include "lexer.h"
#include "stack.h"
#include "utils.h"
#include "n_ary_tree.h"

#define NUM_TERM 58
#define NUM_NONTERM 57
#define NUM_RULES 200

#define PRINT_FORMAT_HEADER "\n%-15s%-15s%-25s%-25s%-25s%-25s%-30s%-20s"
#define PRINT_FORMAT_BODY1  "\n%-15s%-15d%-25s%-25s%-25s%-25c%-30s%-20d"
#define PRINT_FORMAT_BODY2	"\n%-15s%-15d%-25s%-25d%-25s%-25c%-30s%-20d"
#define PRINT_FORMAT_BODY3	"\n%-15s%-15d%-25s%-25f%-25s%-25c%-30s%-20d"

#define PRINT_FORMAT_BODY1_LINE_STR	"\n%-15s%-15s%-25s%-25s%-25s%-25c%-30s%-20d"
#define PRINT_FORMAT_BODY2_LINE_STR	"\n%-15s%-15s%-25s%-25d%-25s%-25c%-30s%-20d"
#define PRINT_FORMAT_BODY3_LINE_STR	"\n%-15s%-15s%-25s%-25f%-25s%-25c%-30s%-20d"

/* structure for maintaining the first and follow sets of the Non Terminals */

unsigned long long int first[NUM_NONTERM + 2];
unsigned long long int follow[NUM_NONTERM + 2];

typedef struct sets {
	unsigned long long int firstset;
	unsigned long long int followset;
} FirstAndFollow[NUM_NONTERM];

int parseTable[NUM_NONTERM][NUM_TERM];

FirstAndFollow F;

typedef struct {
	nonterminal left;
	rhsNode * head;
} grammar[NUM_RULES];

grammar G;

/* changed the declaration of hashNode and hashTable */

struct hashNode {
	char str[25];
	symbol sym;
	typeOfSymbol tag;
	struct hashNode * next;
};

typedef struct hashNode hashNode;

typedef struct {
	hashNode * head;
	int count;
} hashTable[HASH_TABLE_SIZE];

hashTable HT;

int num_rules;

char * terminals[NUM_TERM];
char * nonterminals[NUM_NONTERM];

Tree PT;

boolean syntacticallyCorrect;

#endif