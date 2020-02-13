#define _LEXERDEF
#ifndef _LEXERDEF

/* mapping tokens to unique integers */
#define INTEGER 	1
#define REAL 		2
#define BOOLEAN 	3
#define OF 			4
#define ARRAY 		5
#define START 		6
#define END 		7
#define DECLARE 	8
#define MODULE 		9
#define DRIVER 		10
#define PROGRAM 	11
#define GET_VALUE 	12
#define PRINT 		13
#define USE 		14
#define WITH 		15
#define PARAMETERS 	16
#define TRUE 		17
#define FALSE 		18
#define TAKES 		19
#define INPUT 		20
#define RETURNS 	21
#define AND 		22
#define OR 			23
#define FOR 		24
#define IN 			25
#define SWITCH 		26
#define CASE 		27
#define BREAK 		28
#define DEFAULT 	29
#define WHILE 		30
#define PLUS 		31
#define MINUS 		32
#define MUL 		33
#define DIV 		34
#define LT 			35
#define LE 			36
#define GE 			37
#define GT 			38
#define EQ 			39
#define NE 			40
#define DEF 		41
#define ENDDEF 		42
#define COLON 		43
#define RANGEOP 	44
#define SEMICOL 	45
#define COMMA 		46
#define ASSIGNOP 	47
#define SQBO 		48
#define SQBC 		49
#define BO 			50
#define BC 			51
#define NUM 		52
#define RNUM 		53
#define ID 			54

typedef struct {
	int id;
	char * value;
	char * lex;
	int line_num;
} token;

extern char * hash_table[1000];

#endif