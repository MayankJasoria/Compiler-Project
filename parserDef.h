#ifndef _PARSERDEF
#define _PARSERDEF

#include <stdlib.h>
#include <string.h>
#include "lexerDef.h"
#include "lexer.h"

#define NUM_TERM 50
#define NUM_NONTERM 50

/* structure for maintaining the first and follow sets of the Non Terminals */

unsigned long long int first[NUM_NONTERM + 2];
unsigned long long int follow[NUM_NONTERM + 2];

typedef struct sets {
	unsigned long long int first[NUM_NONTERM + 2];
	unsigned long long int follow[NUM_NONTERM + 2];
} FirstAndFollow;

/* turned to lower case to remove the conflict with Keywords */
typedef enum {
	program,
	moduledeclarations,
	moduledeclaration,
	othermodules,
	drivermodule,
	module,
	ret,
	input_plist,
	input_plistnew,
	output_plist,
	output_plistnew,
	type,
	datatype,
	moduledef,
	statements,
	statement,
	iostmt,
	whichid,
	_index, /* For removing conflict with index */
	simplestmt,
	assignmentstmt,
	modulereusestmt,
	optional,
	idlist,
	idlistnew,
	expression,
	arithorboolexpr,
	arithorboolexprnew,
	relopexpr,
	relopexprnew,
	arithmeticexpr,	
	arithmeticexprnew,
	term,
	termnew,
	factor,
	var,
	pm,
	md,
	logicalop,
	relationalop,
	declarestmt,
	condionalstmt,
	casestmts,
	casestmtsnew,
	value,
	_default, /* for removing the conflict */
	iterativestmt,
	range,

} nonterminal;

typedef enum {T, NT} typeOfSymbol;

/* Enumerated interger value of the corresponding T/NT */
typedef union {
	terminal T;
	nonterminal NT;
} symbol;

struct rhsNode{
	symbol sym;
	typeOfSymbol tag;
	struct rhsNode * next;
};

typedef struct rhsNode rhsNode;

typedef struct {
	nonterminal left;
	rhsNode * head;
} grammar[100];

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

/* POSSIBLE PLACEHOLDERS - AVOIDING COMPILE ERRORS */
/* Update definitions below when relevant */
typedef struct tb {
	int adf;
} table;

typedef struct pt {
	int asd;
} parseTree;

#endif