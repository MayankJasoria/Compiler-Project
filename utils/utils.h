/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _UTILS
#define _UTILS

#include "../lexerDef.h"

/**
 * This file is a space to declare any utility or helper data types,
 * type definitions, constants etc, which are for general purpose
 */

/**
 * Defining constants for print highlighting
 */
#define KNRM "\e[0m" /* NORMAL */
#define KRED "\e[1;91m" /* RED*/
#define KGRN "\e[1;92m" /* GREEN */
#define KYEL "\e[1;93m" /* YELLOW */
#define KBLU "\e[1;94m" /* BLUE */
#define KMAG "\e[1;95m" /* MAGENTA */
#define KCYN "\e[1;96m" /* CYAN */

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
	range_arrays,
	boolconstt,
	var_id_num,
	whichstmt,
	lvalueidstmt,
	lvaluearrstmt,
	u,
	unary_op,
	new_nt
} nonterminal;

typedef enum {T, NT} typeOfSymbol;

/* Enumerated interger value of the corresponding T/NT */
typedef union {
	terminal T;
	nonterminal NT;
} symbol;

typedef struct treeNode {
	symbol sym;
	typeOfSymbol tag;
	int rule_num;
	int line_num;
	union {
		int val_int;
		float val_float;
	} value;
	char lex[25];
	int depth;
	int id;
	struct treeNode * parent;
	struct treeNode * prev;
	struct treeNode * next;
	struct treeNode * child;
	token * tok;
	boolean isLeaf;
} treeNode;

typedef treeNode * Tree;

typedef struct {
	symbol sym;
	typeOfSymbol tag;
	treeNode * tn;
} stackElement;

typedef stackElement treeElement;

struct rhsNode{
	symbol sym;
	typeOfSymbol tag;
	struct rhsNode * next;
};

typedef struct rhsNode rhsNode;

struct errorNode {
	int line;
	char message[200];
	struct errorNode * next;
};

typedef struct errorNode errorNode;

boolean semanticallyCorrect;

errorNode * errorList;

/**
 * Registers an error
 * @param line	The line number at which the error was encountered
 * @param mess	The error reported 
 */
void reportError(int line, char * mess);

/*
 * Prints the list of semantic errors to be reported
 */
void printErrorList();

/**
 * Destroys any old error list
 */
void destroyError();

#endif