#ifndef _LEXERDEF
#define _LEXERDEF

/* mapping tokens to unique integers */
#define INTEGER 		1
#define REAL 			2
#define BOOLEAN 		3
#define OF 				4
#define ARRAY 			5
#define START 			6
#define END 			7
#define DECLARE 		8
#define MODULE 			9
#define DRIVER 			10
#define PROGRAM 		11
#define GET_VALUE 		12
#define PRINT 			13
#define USE 			14
#define WITH 			15
#define PARAMETERS 		16
#define TRUE 			17
#define FALSE 			18
#define TAKES 			19
#define INPUT 			20
#define RETURNS 		21
#define AND 			22
#define OR 				23
#define FOR 			24
#define IN 				25
#define SWITCH 			26
#define CASE 			27
#define BREAK 			28
#define DEFAULT 		29
#define WHILE 			30
#define PLUS 			31
#define MINUS 			32
#define MUL 			33
#define DIV 			34
#define LT 				35
#define LE 				36
#define GE 				37
#define GT 				38
#define EQ 				39
#define NE 				40
#define DEF 			41
#define ENDDEF 			42
#define COLON 			43
#define RANGEOP 		44
#define SEMICOL 		45
#define COMMA 			46
#define ASSIGNOP 		47
#define SQBO 			48
#define SQBC 			49
#define BO 				50
#define BC 				51
#define NUM 			52
#define RNUM 			53
#define ID 				54
#define DRIVERDEF		55
#define DRIVERENDDEF	56

/* type definition of a Token */
typedef struct {
	int id;
	double value; // doubt. how to distinguish between float and integer values.
	char * lex;
	int line_num;
} token;

/* hash_table to store the keyworkds */
extern char * hash_table[1000];

/* line_num will store the instantaneous line number position of the lexer */
extern int line_num;

/* chunk_size is the size of code loaded in the memory bt getStream() */
extern int chunk_size;

/* streamBuffer stores the part of code loaded by getStream() */
extern char streamBuffer[chunk_size];

/* buffer_id gives us the index till which the cide chunk has been read by getNextToken() */
extern int buffer_id;

/* tokenStream is the stream of tokens that will be populated by tokenStream */
extern token ** tokenStream;

/* capacity of tokenStream allocated to the heap */
extern int tokenStream_cap;

/* ntokens is the number of tokens recognized by lexer */
extern int ntokens;

/* state maintains the current state of the dfa */
extern int state;

/* lexeme maintains the current lexeme whilw the dfa traversal */
extern char lexeme[chunk_size];

/* enum for the tokens */
/* TODO: Replace '#define'd tokens with the enum -- uncomment to use enum
typedef enum {
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
	GT,
	GE,
	EQ,
	NE,
	DEF,
	ENDDEF,
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
	DRIVERENDDEF
} tokenList; */

#endif