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
*/ 

SymbolTable getSymbolTable() {
	return getHashTable();
}

SymTableVar* fetchVarData(SymbolTable st, char* name) {
	SymTableVar* data = (SymTableVar*) getDataFromTable(st, name, stringHash);
	return data;
}

SymTableFunc* fetchFuncData(SymbolTable st, char* name) {
	SymTableFunc* data = (SymTableFunc*) getDataFromTable(st, name, stringHash);
	return data;
}

SymbolTable insertVarRecord(SymbolTable st, char* name, int width, int offset, astDataType dataType) {

	if(fetchFuncData(st, name) != NULL || fetchVarData(st, name) != NULL) {
		fprintf(stderr, "A record with the given already exists within the symbol table.");
		return st;
	}

	SymTableVar* data = (SymTableVar*) malloc(sizeof(SymTableVar));
	strcpy(data->name, name);
	data->width = width;
	data->offset = offset;
	data->dataType = dataType;
	data->type = SYM_VARIABLE;

	return insertToTable(st, name, data, stringHash);
}

SymbolTable addDataToFunction(SymTableFunc funcData, char* varName, int varWidth, astDataType varDataType) {
	
	if(fetchVarData(funcData->dataTable, varName) == NULL) {
		int offset = funcData->actRecSize;
		st = insertVarRecord(st, varName, varWidth, offset, varDataType);
		funcData->actRecSize += varWidth;
		return st;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item already exists within the scope of this function.\nNo changes have been made.\n");
		return st;
	}
}

SymbolTable addArrToFunction(SymTableFunc funcData, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {
	
	if(fetchVarData(funcData -> dataTable, varName) == NULL) {
		int offset = funcData -> actRecSize;
		st = insertVarRecord(st, varName, varWidth, offset, varDataType);
		funcData->actRecSize += varWidth;
		return st;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item already exists within the scope of this function.\nNo changes have been made.\n");
		return st;
	}
}

SymbolTable insertFuncRecord(SymbolTable st, char* name) {

	if(fetchFuncData(st, name) != NULL || fetchVarData(st, name) != NULL) {
		fprintf(stderr, "A record with the given already exists within the symbol table.");
		return st;
	}

	SymTableFunc* data = (SymTableFunc*) malloc(sizeof(SymTableFunc));
	strcpy(data->name, name);
	data->type = SYM_FUNCTION;
	data->actRecSize = 0;
	data->dataTable = getSymbolTable();
	return insertToTable(st, name, data, stringHash);
}

SymbolTable addDataToFunction(SymbolTable st, char* funcName, char* varName, int varWidth, astDataType varDataType) {
	SymTableFunc* funcData = fetchFuncData(st, funcName);

	if(funcData == NULL) {
		fprintf(stderr, "The data for the required function could not be fetched.\n");
		return st;
	}

	if(fetchVarData(funcData->dataTable, varName) == NULL) {
		int offset = funcData->actRecSize;
		st = insertVarRecord(st, varName, varWidth, offset, varDataType);
		funcData->actRecSize += varWidth;

		return st;
	} else {
		fprintf(stderr, 
			"A record for the given data item already exists within the scope of this function.\nNo changes have been made.\n");
		return st;
	}
}

SymbolTable updateOffsetOfFunc(SymbolTable st, char* funcName, int varWidth) {
	SymTableFunc* funcData = fetchFuncData(st, funcName);

	if(funcData == NULL) {
		fprintf(stderr, "The data for the required function could not be fetched.\n");
		return st;
	}

	funcData->actRecSize += varWidth;

	return st;
}