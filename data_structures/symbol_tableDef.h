/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */

#ifndef _SYMBOL_TABLE_DEF
#define _SYMBOL_TABLE_DEF

#include "hash_map.h"
#include "astDef.h"

// defining a symbol table
typedef HashTable SymbolTable;

typedef enum {
	SYM_VARIABLE,
	SYM_FUNCTION
} SymTableType;

typedef struct symTableFunction {
	SymTableType type;

	char* name;

	// symbol table associated with the elements of this function
	SymbolTable dataTable;
	
	// field for storing activation record size
	int actRecSize;
} SymTableFunc;

typedef struct symTableVar {
	SymTableType type;
	char* name;
	// total memory space to be allocated
	int width;
	// datatype of variable -> INT, RNUM, BOOL (optionally define a new enum)
	astDataType dataType;
} SymTableVar;

#endif