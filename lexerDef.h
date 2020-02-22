#ifndef _LEXERDEF
#define _LEXERDEF

// #include "utils/utils.h"

#define NUM_KEYWORDS 30

#define HASH_TABLE_SIZE 200

int num_keywords;

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

struct keyNode {
	char str[25];
	int id;
	struct keyNode * next;
};

typedef struct keyNode keyNode;

typedef struct {
	keyNode * head;
	int count;
} keyTable[HASH_TABLE_SIZE];

keyTable keys;

/* hash_table to store the keyworkds */
int hash_table[HASH_TABLE_SIZE];

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