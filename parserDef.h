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
	index,
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
	range
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

typedef struct {
	char str[25];
	symbol sym;
	typeOfSymbol tag;
} hashTable[1009];

hashTable HT;



#endif