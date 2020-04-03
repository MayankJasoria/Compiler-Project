/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_tableDef.h"

/* Doubts regarding the hash table implementation:
	1. if item not there in table, does getDataFromTable return NULL.
	2. make an array typeSize, after seeing the MASM doc.
	3. The st taken in the I/P of fetchVarData is same as localST
	4. The list Type match.
	5. Check the ast.c alone.
*/ 

SymbolTable getSymbolTable() {
	return getHashTable();
}

SymTableVar * fetchVarData(SymbolTable st, char* name) {
	SymTableVar* data = (SymTableVar*) getDataFromTable(st, name, stringHash);
	return data;
}

SymTableFunc * fetchFuncData(char* name) {
	SymTableFunc* data = (SymTableFunc*) getDataFromTable(globalST, name, stringHash);
	return data;
}

SymbolTable insertVarRecord(SymbolTable * st, char* name, int width, int offset, astDataType dataType, SymDataType s) {

	SymTableVar* data = (SymTableVar*) malloc(sizeof(SymTableVar));
	strcpy(data->name, name);
	data->width = width;
	data->offset = offset;
	data->dataType = dataType;
	data->type = SYM_VARIABLE;
	data -> sdt = s;

	return insertToTable(st, name, data, stringHash);
}

void addDataToFunction(SymTableFunc * funcData, char* varName, astDataType varDataType) {
	
	if(fetchVarData(funcData -> dataTable, varName) == NULL) {
		int offset = funcData->actRecSize;
		int width = typeSize[varDataType];
		SymDataType s;
		insertVarRecord(funcData -> dataTable, varName, width, offset, varDataType, s);
		// st = insertVarRecord(st, varName, varWidth, offset, varDataType);
		funcData -> actRecSize += width;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item already exists within the scope of this function.\nNo changes have been made.\n");
	}
}

void addArrToFunction(SymTableFunc * funcData, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {
	
	if(fetchVarData(funcData -> dataTable, varName) == NULL) {
		int offset = funcData -> actRecSize;
		arrayInfo a;
		a.dataType = varDataType;
		if(lft -> type == AST_LEAF_IDXNUM) {
			strcpy(a.lowId, "");
			a.low = ((lft -> tn) -> value).val_int;
		}
		else 
			strcpy(a.lowId, lft -> tn -> lex);
		
		if(right -> type == AST_LEAF_IDXNUM) {
			strcpy(a.highId, "");
			a.high = ((lft -> tn) -> value).val_int;
		}
		else 
			strcpy(a.highId, lft -> tn -> lex);

		SymDataType s;
		s.r = a;

		int varWidth;
		if(lft -> type == AST_LEAF_IDXNUM && right -> type == AST_LEAF_IDXNUM)
			varWidth = typeSize[varDataType]*(a.high - a.low + 1);
		else
			varWidth = typeSize[AST_TYPE_POINTER];
		st = insertVarRecord(funcData -> dataTable, varName, varWidth, offset, AST_TYPE_ARRAY, s);
		funcData->actRecSize += varWidth;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item already exists within the scope of this function.\nNo changes have been made.\n");
	}
}

SymTableFunc * insertFuncRecord(char* name) {

	if(fetchFuncData(globalST, name) != NULL) {
		fprintf(stderr, "A record with the given already exists within the symbol table.");
		return st;
	}

	SymTableFunc* data = (SymTableFunc*) malloc(sizeof(SymTableFunc));
	strcpy(data->name, name);
	data->type = SYM_FUNCTION;
	data->actRecSize = 0;
	data->dataTable = getSymbolTable();
	data -> isDefined = 0;
	data -> isDeclared = 1;
	data -> parent = NULL;
	insertToTable(st, name, data, stringHash);
	return data;
}

SymTableFunc * getFuncTable(char * fname) {

	SymTableFunc * parentFunc = fetchFuncData(fname);
	SymTableFunc * data = (SymTableFunc*) malloc(sizeof(SymTableFunc));
	data -> actRecSize = parentFunc -> actRecSize;
	data -> parent = parentFunc;
	data -> type = SYM_FUNCTION;
	data -> dataTable = getSymbolTable();
	return data;
}