#ifndef _UTILS
#define _UTILS
/**
 * This file is a space to declare any utility or helper data types,
 * type definitions, constants etc, which are for general purpose
 */

/**
 * Simple ENUM to use as boolean
 */
typedef enum {
    False, True
} boolean;

/* enum for the tokens */
typedef enum {
	EMPTY,
	INTEGER,
	REAL,
	BOOLEAN,
	OF,
	ARRAY,
	START,
	END,
	DECLARE,
	MODULE,
	DRIVER,
	PROGRAM,
	GET_VALUE,
	PRINT,
	USE,
	WITH,
	PARAMETERS,
	TRUE,
	FALSE,
	TAKES,
	INPUT,
	RETURNS,
	AND,
	OR,
	FOR,
	IN,
	SWITCH,
	CASE,
	BREAK,
	DEFAULT,
	WHILE,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LT,
	LE,
	GE,
	GT,
	EQ,
	NE,
	DEF,
	ENDDEF,
	COLON,
	RANGEOP,
	SEMICOL,
	COMMA,
	ASSIGNOP,
	SQBO,
	SQBC,
	BO,
	BC,
	NUM,
	RNUM,
	ID,
	DRIVERDEF,
	DRIVERENDDEF,
	DOLLAR
} terminal;

/* enum for nonterminals (turned to lower case to remove the conflict with Keywords) */
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

typedef struct {
	symbol sym;
	typeOfSymbol tag;
} stackElement;

struct rhsNode{
	symbol sym;
	typeOfSymbol tag;
	struct rhsNode * next;
};

typedef struct rhsNode rhsNode;

#endif