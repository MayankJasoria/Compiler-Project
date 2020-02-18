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

typedef enum {
	PROGRAM,
	MODULEDECLARATIONS,
	MODULEDECLARATION,
	OTHERMODULES,
	DRIVERMODULE,
	MODULE,
	RET,
	INPUT_PLIST,
	INPUT_PLISTNEW,
	OUTPUT_PLIST,
	OUTPUT_PLISTNEW,
	TYPE,
	DATATYPE,
	MODULEDEF,
	STATEMENTS,
	STATEMENT,
	IOSTMT,
	WHICHID,
	INDEX,
	SIMPLESTMT,
	ASSIGNMENTSTMT,
	MODULEREUSESTMT,
	OPTIONAL,
	IDLIST,
	IDLISTNEW,
	EXPRESSION,
	ARITHORBOOLEXPR,
	ARITHORBOOLEXPRNEW,
	RELOPEXPR,
	RELOPEXPRNEW,
	ARITHMETICEXPR,	
	ARITHMETICEXPRNEW,
	TERM,
	TERMNEW,
	FACTOR,
	VAR,
	PM,
	MD,
	LOGICALOP,
	RELATIONALOP,
	DECLARESTMT,
	CONDIONALSTMT,
	CASESTMTS,
	CASESTMTSNEW,
	VALUE,
	DEFAULT,
	ITERATIVESTMT,
	RANGE
} nonterminal;

typedef enum {T, NT} typeOfSymbol;

/* Enumerated interger value of the corresponding T/NT */
typedef union {
	terminal T;
	nonterminal NT;
} symbol;

struct rhsnode{
	symbol sym;
	typeOfSymbol tag;
	struct rhsnode * next;
};

typedef struct rhsnode rhsnode;

typedef struct {
	nonterminal sym;
	rhsnode * head;
} grammar[100];

grammar G;

typedef struct {
	char str[25];
	symbol sym;
	typeOfSymbol tag;
} hashTable[1009];

hashTable HT;

#endif