#ifndef _LEXERDEF
#define _LEXERDEF

#define NUM_KEYWORDS 29

#define HASH_TABLE_SIZE 1009

int num_keywords;

/* enum for the tokens */
/* TODO: Replace '#define'd tokens with the enum -- uncomment to use enum  */
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
} terminal;

/* type definition of a Token */
typedef struct {
	int id;

	union {
		int val_int;
		double val_float;
	} val;
	/* 1 bit tag 
	   0 indicates integer, 1 indicates float */
	unsigned is_float:1;
	char * lex;
	int line_num;
} token;

typedef struct {
	char * lex;
	int line_num;
} errorInst;

/* hash_table to store the keyworkds */
int hash_table[1009];

/* line_num will store the instantaneous line number position of the lexer */
int line_num;

/* chunk_size is the size of code loaded in the memory bt getStream() */
int chunk_size;

/* 
	size of these arrays hardcoded. Take Care.
*/

/* streamBuffer stores the part of code loaded by getStream() */
char streamBuffer[100];

/* lexeme maintains the current lexeme whilw the dfa traversal */
char lexeme[100];

/* state maintains the current state of the dfa */
int state;

/* buffer_id gives us the index till which the cide chunk has been read by getNextToken() */
int buffer_id;

/* tokenStream is the stream of tokens that will be populated by tokenStream */
token ** tokenStream;

/* capacity of tokenStream allocated to the heap */
int tokenStream_cap;

/* ntokens is the number of tokens recognized by lexer */
int ntokens;

/* data structure to store the list of error, definition above */
errorInst ** lexErrorlist;

int endofLexer;

char * keywordList[NUM_KEYWORDS + 2];

#endif