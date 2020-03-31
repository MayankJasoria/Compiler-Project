#ifndef _SYMBOL_TABLE_DEF
#define _SYMBOL_TABLE_DEF

#include "hash_map.h"

// defining a symbol table
typedef HashTable SymbolTable;

typedef struct symbolTableElement {
	// add relevant parameters here
	// given below are placeholders
	char* name;
	int type;
} SymbolTableElement;

#endif