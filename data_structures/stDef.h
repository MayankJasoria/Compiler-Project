/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */

#ifndef _SYMBOL_TABLE_DEF
#define _SYMBOL_TABLE_DEF

#include "hash_map.h"
#include "linked_list.h"
#include "astDef.h"

/* Forward declarations */
enum astDataType;

/* defining a symbol table */
typedef HashTable SymbolTable;

SymbolTable globalST;

typedef enum {
	SYM_VARIABLE,
	SYM_FUNCTION,
	SYM_OTHER   /* Ex: If Else Construct */
} SymTableType;

typedef struct arrayInfo {
	astDataType dataType; /* can only be int, real, boolean? */
	int low; /*low..high */
	int high;
	char* lowId; /*lowID..highId*/
	char* highId;
} arrayInfo;

typedef union {
	arrayInfo* r;	
	int intVal;
	float floatVal;
	int boolVal:1;
} SymDataType;

typedef struct SymTableFunc {
	SymTableType type;  /*to cross check if it is a function (type==SYM_FUNCTION) */
	int isDefined;			/*to check if the function is defined*/
	int isDeclared;			/*to check if the function is declared*/
	struct SymTableFunc * parent; /* pointer to the static parent of the scope. */
	int baseAdd; /* base address of the fuction activation record. */
	char * name; /* name of the function */
	List input_plist; /* List of input parameter variables */
	List output_plist; /* List of output parameter variables */
	SymbolTable dataTable; /* symbol table associated with the local elements of this function , it contains entries of type SymTableVar */
	int actRecSize; /* field for storing activation record size */
} SymTableFunc;


typedef struct symTableVar {	
	SymTableType type;
	char* name;
	int isAssigned;
	int width; /* total memory space to be allocated */
	int offset;
	/*
	* datatype of variable -> INT, RNUM, BOOL, ARRAY
	*/
	astDataType dataType;
	SymDataType sdt;
} SymTableVar;

#endif