#ifndef _PARSERDEF
#define _PARSERDEF

#include <stdlib.h>
#include <string.h>
#include "lexerDef.h"
#include "lexer.h"
#include "data_structures/stack.h"
#include "utils/utils.h"
#include "data_structures/n_ary_tree.h"

#define NUM_TERM 58
#define NUM_NONTERM 57
#define NUM_RULES 200

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

// typedef struct {
// 	char str[25];
// 	symbol sym;
// 	typeOfSymbol tag;
// } hashTable[HASH_TABLE_SIZE];

// hashTable HT;

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

/* POSSIBLE PLACEHOLDERS - AVOIDING COMPILE ERRORS */
/* Update definitions below when relevant */
typedef struct tb {
	int adf;
} table;

typedef struct pt {
	int asd;
} parseTree;

#endif