/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astDef.h"
#include "hash_map.h"
#include "symbolTable.h"
#include "utils.h"

#define PRINT_FUNC_HEADINGS "%-25s%-25s\n"
#define PRINT_FUNC_DATA "%-25s%-25d\n"

#define PRINT_VARIABLE_HEADINGS "%-25s%-25s%-20s%-10s%-10s%-15s%-25s%-20s%-10s%-15s\n"
#define PRINT_VARIABLE_DATA "%-25s%-25s%-*d - %-*d%-10d%-10s%-15s%-25s%-20s%-10d%-15d\n" 
#define PRINT_VAR_STAT_ARRAY_DATA "%-25s%-25s%-*d - %-*d%-10d%-10s%-15s[%d, %d]%-*s%-20s%-10d%-15d\n"
#define PRINT_VAR_LDYN_ARRAY_DATA "%-25s%-25s%-*d - %-*d%-10d%-10s%-15s[%s, %d]%-*s%-20s%-10d%-15d\n"
#define PRINT_VAR_RDYN_ARRAY_DATA "%-25s%-25s%-*d - %-*d%-10d%-10s%-15s[%d, %s]%-*s%-20s%-10d%-15d\n"
#define PRINT_VAR_LRDYN_ARRAY_DATA "%-25s%-25s%-*d - %-*d%-10d%-10s%-15s[%s, %s]%-*s%-20s%-10d%-15d\n"

#define PRINT_ARR_HEADINGS "%-22s%-20s%-22s%-16s%-25s%-20s\n"
#define PRINT_STAT_ARR_DATA "%-22s%-*d - %-*d%-22s%-16s[%d, %d]%-*s%-20s\n"
#define PRINT_LDYN_ARR_DATA "%-22s%-*d - %-*d%-22s%-16s[%s, %d]%-*s%-20s\n"
#define PRINT_RDYN_ARR_DATA "%-22s%-*d - %-*d%-22s%-16s[%d, %s]%-*s%-20s\n"
#define PRINT_LRDYN_ARR_DATA "%-22s%-*d - %-*d%-22s%-16s[%s, %s]%-*s%-20s\n"
	
/* 
 * specifies the width(in bytes) corresponding to the dataType.
 * Index: corresponding to the astDataType enum.
 */
int typeSize[] = {2, 4, 1, 8, 8};

/** 
 * specifies the width(in bytes) corresponding to the dataType.
 */
int string_comp_id(void* data, void* list_ele);

SymbolTable getSymbolTable() {
	return getHashTable();
}

int lookupDependentVar(SymTableFunc * func, char* name) {
	SymTableVar* data = NULL;
	while(func != NULL) {
		if((strcmp(name, func -> dependentVar) == 0) && func -> scope == SCOPE_FOR)
			return 1;
		func = func -> parent;
	}
	return 0;
}

/* Fetches record for a given local variable */
SymTableVar * fetchVarData(SymTableFunc * func, char* name, int line_num) {
	SymTableVar* data = NULL;
	while(func != NULL) {
		data = (SymTableVar*) getDataFromTable(func -> dataTable, name, stringHash);
		if(data == NULL) {
			/* scan input_plist */
			data = (SymTableVar*) findInList(func->input_plist, name, string_comp_id);
		}
		if(data != NULL && data -> declarationLine <= line_num) {
			break;
		}
		data = NULL;
		if(func -> parent == NULL) {
			data = (SymTableVar*) findInList(func->input_plist, name, string_comp_id);
			return data;
		}
		func = func -> parent;
	}
	return data;
}

SymTableFunc * fetchFuncData(char* name) {
	/* functions can only be declared in globalST unlike variables */
	SymTableFunc* data = (SymTableFunc*) getDataFromTable(globalST, name, stringHash); //functions can only be declared in globalST unlike variables
	return data;
}

SymTableFunc * getParentFunc(SymTableFunc * local) {
	/* traversing back in outer scopes */
	while(local -> parent != NULL)
		local = local -> parent;
	return local;
}

void insertVarRecord(SymTableFunc * func, char* name, int width, int offset, astDataType dataType, SymDataType s, int line_num) {
	
	/* allocating and assigning fields of a variable record */
	SymTableVar* data = (SymTableVar*) malloc(sizeof(SymTableVar));
	strcpy(data -> name, name);
	data -> width = width;
	data -> offset = offset;
	data -> dataType = dataType;
	data -> type = SYM_VARIABLE;
	data -> sdt = s;
	data -> table = func;
	data -> declarationLine = line_num;

	/* inserting the created record to the symbol table */
	func -> dataTable = insertToTable(func -> dataTable, name, data, stringHash);
}

void addDataToFunction(SymTableFunc* funcData, char * fname, char* varName, astDataType varDataType, int line_num) {

	/* getting the record for the function entry in the global symbol table */
	SymTableFunc * fun = fetchFuncData(fname);

	/** 
	 * If a record with given name already exists, report an error,
	 * otherwise, insert it into the local Symbol Table
	 */
	if(getDataFromTable(funcData -> dataTable, varName, stringHash) == NULL) {
		int offset = fun -> actRecSize;
		int width = typeSize[varDataType];
		SymDataType s;
		insertVarRecord(funcData , varName, width, offset, varDataType, s, line_num);
		fun -> actRecSize += width;
	} 
	else {
		/* reporting error */
		char message[200];
		sprintf(message, 
		"Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the scope of this function).\n", line_num, varName);
		reportError(line_num, message);
	}
}

void addArrToFunction(SymTableFunc * funcData, char * fname, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {
	
	/* fetching Pointer to the symbol table of the function */
	SymTableFunc * fun = fetchFuncData(fname);
	
	/** 
	 * if a record exists with the same name, report a redeclaration error, 
	 * otherwise insert it to the symbol table
	 */
	if(getDataFromTable(funcData -> dataTable, varName, stringHash) == NULL) {
		int offset = fun -> actRecSize;
		arrayInfo* a = (arrayInfo*) malloc(sizeof(arrayInfo));
		a -> dataType = varDataType;
		if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
			strcpy(a -> lowId, "");
			a -> low = ((lft -> nodeData.leaf -> tn) -> value).val_int;
		}
		else 
			strcpy(a -> lowId, lft -> nodeData.leaf -> tn -> lex);
		
		if(right -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
			strcpy(a -> highId, "");
			a -> high = (right -> nodeData.leaf -> tn -> value.val_int);
		}
		else 
			strcpy(a -> highId, right -> nodeData.leaf -> tn -> lex);

		SymDataType s;
		s.r = a;

		int varWidth;
		if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM && right -> nodeData.leaf -> type == AST_LEAF_IDXNUM)
			varWidth = typeSize[varDataType]*(a -> high - a -> low + 1) + typeSize[AST_TYPE_POINTER];
		else
			varWidth = typeSize[AST_TYPE_POINTER];
		insertVarRecord(funcData, varName, varWidth, offset, AST_TYPE_ARRAY, s, lft -> nodeData.leaf -> tn -> line_num);
		fun->actRecSize += varWidth;
	} 
	else {
		char message[200];
		sprintf(message, 
		"Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the scope of this function).\n", lft -> nodeData.leaf -> tn -> line_num, varName);
		reportError(lft -> nodeData.leaf -> tn -> line_num, message);
	}
}

SymTableFunc* insertFuncRecord(char* name) {

	if(fetchFuncData(name) != NULL) {
		return NULL;
	}

	/** 
	 * Checks if a function with the same name already exists in the global symbol table
	 * Otherwise create a record with the given name into the global symbol table
	 */
	SymTableFunc* data = (SymTableFunc*) malloc(sizeof(SymTableFunc));
	strcpy(data->name, name);
	data->type = SYM_FUNCTION;
	data->actRecSize = 0;
	data->dataTable = getSymbolTable();
	data -> isDefined = 0;
	data -> isDeclared = 1;
	data -> parent = NULL;
	data -> input_plist = getList();
	data -> output_plist = getList();
	data -> scope = SCOPE_DEFAULT;
	data -> level = 1;
	data -> dynamicRecSize = 0;
	data -> inputSize = 0;
	data -> outputSize = 0;
	strcpy(data -> dependentVar, "");
	strcpy(data -> nextJump, "");
	insertToTable(globalST, name, data, stringHash);
	return data;
}

SymTableFunc * getFuncTable(char * fname, SymTableFunc * par) {

	/* Creates a pointer type record of a Function type, and insert it to global symbol table */
	SymTableFunc * parentFunc = fetchFuncData(fname);
	SymTableFunc * data = (SymTableFunc*) malloc(sizeof(SymTableFunc));
	data -> actRecSize = parentFunc -> actRecSize;
	data -> parent = par;
	data -> type = SYM_FUNCTION;
	data -> dataTable = getSymbolTable();
	data -> input_plist = getList();
	data -> output_plist = getList();
	data -> scope = SCOPE_DEFAULT;
	data -> level = par -> level + 1;
	data -> dynamicRecSize = 0;
	data -> inputSize = 0;
	data -> outputSize = 0;
	strcpy(data -> name, "");
	strcpy(data -> dependentVar, "");
	strcpy(data -> nextJump, "");
	return data;
}

int paramlistComparator(void * myElement, void * listElement) {

	char * my = (char *)myElement;
	SymTableVar * listEl = (SymTableVar *)listElement;

	return strcmp(my, listEl -> name) == 0;
}


/**
 * Assumption: The function record (name) is already hashed to the symbol table
 * The size of the activation record is computed dynamically everytime this
 * function is called for a new variable. For other details, 
 * @see symbol_table.h
 */
void addParamToFunction(SymTableFunc* funcData, int paramType, char* varName, astDataType varDataType, int line_num) {

	/* compute offset */
	int offset = funcData -> actRecSize;

	if(paramType == 0 && findInList(funcData -> input_plist, varName, paramlistComparator) != NULL) {
		char message[200];
		sprintf(message, "Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the input parameter list of this function).\n", 
			line_num, varName);
		reportError(line_num, message);
		return;
	}
	else if(paramType == 1 && fetchVarData(funcData, varName, funcData -> end_line_num) != NULL) {
		char message[200];
		sprintf(message, "Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the parameter list of this function).\n", 
			line_num, varName);
		reportError(line_num, message);
		return;
	}

	/* Create a record for the variable */
	SymTableVar* varData = (SymTableVar*) malloc(sizeof(SymTableVar));
	varData -> type = SYM_VARIABLE;
	strcpy(varData -> name, varName);
	varData -> offset = offset;
	varData -> width = typeSize[varDataType];
	varData -> dataType = varDataType;
	SymDataType new;
	varData -> table = funcData;
	varData -> sdt = new;
	varData -> isAssigned = 0;
	varData -> declarationLine = funcData -> start_line_num;

	/* update activation record size */
	funcData -> actRecSize += varData -> width;

	/* populate correct list */
	if(paramType == 0) {
		funcData -> inputSize += varData -> width;
		funcData -> input_plist = insertToList(funcData -> input_plist, varData, BACK);
	} 
	else {
		funcData -> outputSize += varData -> width;
		funcData -> output_plist = insertToList(funcData -> output_plist, varData, BACK);
		insertVarRecord(funcData, varName, varData->width, varData->offset, varData->dataType, new, line_num);
	}
}

/** 
 * Analogous to addParamToFunction, only difference is the datatype of the variable, 
 * For an array type parameter, we need to allocate space for storing the pointer to the 
 * base address, lower and upper bound.
 */ 
void addArrParamToFunction(SymTableFunc * funcData, int paramType, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {

	if(paramType == 0 && findInList(funcData -> output_plist, varName, paramlistComparator) != NULL) {
		char message[200];
		sprintf(message, "Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the input parameter list of this function).\n", 
			lft -> nodeData.leaf -> tn -> line_num, varName);
		reportError(line_num, message);
		return;
	}
	else if(paramType == 1 && fetchVarData(funcData, varName, funcData -> end_line_num) != NULL) {
		char message[200];
		sprintf(message, "Line number (%d): semantic error -- Redeclaration of '%s' (it already exists within the parameter list of this function).\n", 
			lft -> nodeData.leaf -> tn -> line_num, varName);
		reportError(line_num, message);
		return;
	}

	int offset = funcData -> actRecSize;
	arrayInfo* a = (arrayInfo*) malloc(sizeof(arrayInfo));
	a -> dataType = varDataType;
	if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		strcpy(a -> lowId, "");
		a -> low = ((lft -> nodeData.leaf -> tn) -> value).val_int;
	}
	else 
		strcpy(a -> lowId, lft -> nodeData.leaf -> tn -> lex);
		
	if(right -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		strcpy(a -> highId, "");
		a -> high = (right -> nodeData.leaf -> tn -> value.val_int);
	}
	else 
		strcpy(a -> highId, right -> nodeData.leaf -> tn -> lex);

	SymDataType s;
	s.r = a;

	int varWidth;
	if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM && right -> nodeData.leaf -> type == AST_LEAF_IDXNUM) {
		// varWidth = typeSize[varDataType]*(a -> high - a -> low + 1) + typeSize[AST_TYPE_POINTER];
		varWidth = typeSize[AST_TYPE_POINTER];
	}
	else
		varWidth = typeSize[AST_TYPE_POINTER];
	varWidth += 2*typeSize[AST_TYPE_INT];

	SymTableVar * varData = (SymTableVar *)malloc(sizeof(SymTableVar));
	strcpy(varData -> name, varName);
	varData -> type = SYM_VARIABLE;
	varData -> width = varWidth;
	varData -> offset = offset;
	varData -> dataType = AST_TYPE_ARRAY;
	varData -> sdt = s;
	varData -> table = funcData;
	varData -> declarationLine = funcData -> start_line_num;
	if(paramType == 0) {
		funcData -> inputSize += varWidth;
		funcData -> input_plist = insertToList(funcData -> input_plist, varData, BACK);
	} else {
		funcData -> output_plist = insertToList(funcData -> output_plist, varData, BACK);
		insertVarRecord(funcData, varName, varWidth, offset, AST_TYPE_ARRAY, s, lft -> nodeData.leaf -> tn -> line_num);
	}

	/* update activation record size */
	funcData->actRecSize += varWidth;
}

/* Utility functions */

/* Comparator for SymTableVar type of data within linked list */
int string_comp_id(void* data, void* list_ele) {
	return strcmp((char *)data, ((SymTableVar *)list_ele)->name) == 0;
}

/**
 * Utility function for computing length of an integer
 * @param num	The number whose length is to be computed
 * @return the no. of digits in the given integer
 */
int intlen(int num) {
	int count =0;
	if(num < 0) {
		num = -num;
	}
	while(num != 0) {
		count++;
		num /= 10;
	}
	return count;
}

/* Print the details of the local variable */
void printVar(void* data) {
	SymTableVar* varData = (SymTableVar*) ((hashElement*) data)->data;
	SymTableFunc* tab = varData -> table;
	SymTableFunc* tmp = tab;
	while(tmp -> parent != NULL)
		tmp = tmp -> parent;
	char modName[30];
	strcpy(modName, tmp -> name);
	
	int offset = varData -> offset;

	if(offset < tmp -> inputSize + tmp -> outputSize)
		return;
	else
		offset -= tmp -> inputSize + tmp -> outputSize;

	int startline = tab -> start_line_num;
	int endline = tab -> end_line_num;
	int varWidth = varData -> width;
	int isArray = varData -> dataType == AST_TYPE_ARRAY;
	int isDynamic = -1;
	if(isArray) {
		if(strcmp(varData -> sdt.r -> lowId, "") == 0 && strcmp(varData -> sdt.r -> highId, "") == 0)
			isDynamic = 0;
		else
			isDynamic = 1;
	}
	char type[30];
	strcpy(type, typeName[varData -> dataType]);
	if(isArray)
		strcpy(type, typeName[varData -> sdt.r -> dataType]);
	
	int nestLevel = tab -> level;
	/* Check if the variable is not an array type variable */
	if(!isArray) {
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		printf(PRINT_VARIABLE_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline, 
			varWidth, "No", "---", "---", type, offset, nestLevel);
	} 
	/* Check if the array is static */
	else if(!isDynamic) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + intlen(varData->sdt.r->high));
		printf(PRINT_VAR_STAT_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline, 
			varWidth, "Yes", "Static", varData->sdt.r->low, varData->sdt.r->high, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the lower bound is dynamic and the upper bound is static */
	else if((strcmp(varData->sdt.r->lowId, "") != 0) && (strcmp(varData->sdt.r->highId, "") == 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + intlen(varData->sdt.r->high));
		printf(PRINT_VAR_LDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->lowId, varData->sdt.r->high, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the lower bound is static and the upper bound is dynamic */
	else if((strcmp(varData->sdt.r->lowId, "") == 0) && (strcmp(varData->sdt.r->highId, "") != 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + strlen(varData->sdt.r->highId));
		printf(PRINT_VAR_RDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->low, varData->sdt.r->highId, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the array is dynamic */
	else {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + strlen(varData->sdt.r->highId));
		printf(PRINT_VAR_LRDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->lowId, varData->sdt.r->highId, spaceWidth, " ", type, offset, nestLevel);
	}
}

/* Prints details of all the variables of input plist and output plist */
void printListVar(void* data) {
	SymTableVar* varData = (SymTableVar*) data;
	SymTableFunc* tab = varData -> table;
	SymTableFunc* tmp = tab;
	while(tmp -> parent != NULL)
		tmp = tmp -> parent;
	char modName[30];
	strcpy(modName, tmp -> name);
	int startline = tab -> start_line_num;
	int endline = tab -> end_line_num;
	int varWidth = varData -> width;
	int isArray = varData -> dataType == AST_TYPE_ARRAY;
	int isDynamic = -1;

	/* Check if the variable is an array type variable */
	if(isArray) {
		if(strcmp(varData -> sdt.r -> lowId, "") == 0 && strcmp(varData -> sdt.r -> highId, "") == 0)
			isDynamic = 0;
		else
			isDynamic = 1;
	}
	char type[30];
	strcpy(type, typeName[varData -> dataType]);

	/* Check if the variable is an array type variable */
	if(isArray)
		strcpy(type, typeName[varData -> sdt.r -> dataType]);
	int offset = varData -> offset;
	int nestLevel = 0;

	/* Check if the variable is not an array type variable */
	if(!isArray) {
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		printf(PRINT_VARIABLE_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline, 
			varWidth, "No", "---", "---", type, offset, nestLevel);
	} 
	/* Check if the array is static */
	else if(!isDynamic) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + intlen(varData->sdt.r->high));
		printf(PRINT_VAR_STAT_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline, 
			varWidth, "Yes", "Static", varData->sdt.r->low, varData->sdt.r->high, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the lower bound is dynamic and the upper bound is static */
	else if((strcmp(varData->sdt.r->lowId, "") != 0) && (strcmp(varData->sdt.r->highId, "") == 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + intlen(varData->sdt.r->high));
		printf(PRINT_VAR_LDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->lowId, varData->sdt.r->high, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the lower bound is static and the upper bound is dynamic */
	else if((strcmp(varData->sdt.r->lowId, "") == 0) && (strcmp(varData->sdt.r->highId, "") != 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + strlen(varData->sdt.r->highId));
		printf(PRINT_VAR_RDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->low, varData->sdt.r->highId, spaceWidth, " ", type, offset, nestLevel);
	} 
	/* Check if the array is dynamic */
	else {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + strlen(varData->sdt.r->highId));
		printf(PRINT_VAR_LRDYN_ARRAY_DATA, varData->name, modName, leftWidth, startline, rightWidth, endline,
			varWidth, "Yes", "Dynamic", varData->sdt.r->lowId, varData->sdt.r->highId, spaceWidth, " ", type, offset, nestLevel);
	}
}

/* Prints the activation record of the function */
void printFunc(void* data) {
	SymTableFunc* funcData = (SymTableFunc*) ((hashElement*) data)->data;
	printf(PRINT_FUNC_DATA, funcData->name, funcData->actRecSize - funcData -> inputSize - funcData -> outputSize);
}

/* Prints the array in the input plist */
void printListArr(void* data) {
	SymTableVar* varData = (SymTableVar*) data;
	int isArray = varData -> dataType == AST_TYPE_ARRAY;
	if(isArray == 0)
		return;
	SymTableFunc* tab = varData -> table;
	SymTableFunc* tmp = tab;
	while(tmp -> parent != NULL)
		tmp = tmp -> parent;
	char modName[30];
	strcpy(modName, tmp -> name);
	int startline = tab -> start_line_num;
	int endline = tab -> end_line_num;
	int isDynamic = -1;
	if(strcmp(varData -> sdt.r -> lowId, "") == 0 && strcmp(varData -> sdt.r -> highId, "") == 0)
		isDynamic = 0;
	else
		isDynamic = 1;
	char type[30];
	strcpy(type, typeName[varData -> sdt.r -> dataType]);
	
	/* Check if the array is static */
	if(!isDynamic) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + intlen(varData->sdt.r->high));
		printf(PRINT_STAT_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Static Array", varData->sdt.r->low, varData->sdt.r->high, spaceWidth, " ", type);
	} 
	/* Check if the lower bound is dynamic and the upper bound is static */
	else if((strcmp(varData->sdt.r->lowId, "") != 0) && (strcmp(varData->sdt.r->highId, "") == 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + intlen(varData->sdt.r->high));
		printf(PRINT_LDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->lowId, varData->sdt.r->high, spaceWidth, " ", type);
	} 
	/* Check if the lower bound is static and the upper bound is dynamic */
	else if((strcmp(varData->sdt.r->lowId, "") == 0) && (strcmp(varData->sdt.r->highId, "") != 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + strlen(varData->sdt.r->highId));
		printf(PRINT_RDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->low, varData->sdt.r->highId, spaceWidth, " ", type);
	} 
	/* Check if the array is dynamic */
	else {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + strlen(varData->sdt.r->highId));
		printf(PRINT_LRDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->lowId, varData->sdt.r->highId, spaceWidth, " ", type);
	}
}

/* Prints an array type variable in the local scope of a module */
void printArr(void* data) {
	SymTableVar* varData = (SymTableVar*) ((hashElement*) data)->data;
	int isArray = varData -> dataType == AST_TYPE_ARRAY;
	if(isArray == 0)
		return;
	SymTableFunc* tab = varData -> table;
	SymTableFunc* tmp = tab;
	while(tmp -> parent != NULL)
		tmp = tmp -> parent;
	char modName[30];
	strcpy(modName, tmp -> name);
	int startline = tab -> start_line_num;
	int endline = tab -> end_line_num;

	int isDynamic = -1;
	if(strcmp(varData -> sdt.r -> lowId, "") == 0 && strcmp(varData -> sdt.r -> highId, "") == 0)
		isDynamic = 0;
	else
		isDynamic = 1;
	char type[30];
	strcpy(type, typeName[varData -> sdt.r -> dataType]);

	/* Check if the array is static */
	if(!isDynamic) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + intlen(varData->sdt.r->high));
		printf(PRINT_STAT_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Static Array", varData->sdt.r->low, varData->sdt.r->high, spaceWidth, " ", type);
	} 
	/* Check if the lower bound is dynamic and the upper bound is static */
	else if((strcmp(varData->sdt.r->lowId, "") != 0) && (strcmp(varData->sdt.r->highId, "") == 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + intlen(varData->sdt.r->high));
		printf(PRINT_LDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->lowId, varData->sdt.r->high, spaceWidth, " ", type);
	} 
	/* Check if the lower bound is static and the upper bound is dynamic */
	else if((strcmp(varData->sdt.r->lowId, "") == 0) && (strcmp(varData->sdt.r->highId, "") != 0)) {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (intlen(varData->sdt.r->low) + strlen(varData->sdt.r->highId));
		printf(PRINT_RDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->low, varData->sdt.r->highId, spaceWidth, " ", type);
	} 
	/* Check if the array is dynamic */
	else {
		int spaceWidth = 21;
		int leftWidth = intlen(startline);
		int rightWidth = 17 - leftWidth;
		spaceWidth -= (strlen(varData->sdt.r->lowId) + strlen(varData->sdt.r->highId));
		printf(PRINT_LRDYN_ARR_DATA, modName, leftWidth, startline, rightWidth, endline, varData->name,
			"Dynamic Array", varData->sdt.r->lowId, varData->sdt.r->highId, spaceWidth, " ", type);
	}
}

/* Prints the entire symbol table */
void printSymbolTable(SymbolTable st, void (printElement)(void*)) {
	if(printElement == printFunc) {
		printf(PRINT_FUNC_HEADINGS, "Function Name", "Activation Record Size");
	}
	printHashTable(st, printElement);
}

/* recursively calls outputSymbolTable for all the children of head */
void outputChildren(ASTNode * head, int operation) {
	ASTNode * ch = head;
	/* iterating over the children. */
	while(ch != NULL) {
		outputSymbolTable(ch, operation);
		ch = ch -> next;
	}
}

void outputSymbolTable(ASTNode * curr, int operation) {
	/* switch on type of ASTNode */
	switch(curr -> type) {
		case AST_NODE_PROGRAM: {
			ASTNode* ch = curr -> child;
			
			if(operation == 0) {
				printf(PRINT_VARIABLE_HEADINGS, "Variable Name", "Module Name", "Scope Line No.","Width",
					"Is Array", "Static/Dynamic", "Range", "Type of element", "Offset", "Nesting Level");
			} else {
				printf(PRINT_ARR_HEADINGS, "Module Name", "Scope Line No.", "Variable Name",
					"Static/Dynamic", "Range", "Type of Element");
			}
			outputChildren(ch, operation);
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.moduleList -> type == AST_MODULE_DRIVER) {
				SymTableFunc * dr = fetchFuncData("driver");
				if(operation == 0)
					printSymbolTable(dr -> dataTable, printVar);
				else
					printSymbolTable(dr -> dataTable, printArr);
			}
			else 
				outputChildren(ch, operation);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			SymTableFunc* tmp;
			char name[30];
			strcpy(name, ch -> nodeData.leaf -> tn -> lex);
			tmp = fetchFuncData(name);
			if(operation == 0) {
				printList(tmp->input_plist, printListVar);
				printList(tmp->output_plist, printListVar);
				printSymbolTable(tmp -> dataTable, printVar);
			}
			else {
				printList(tmp->input_plist, printListArr);
				printList(tmp->output_plist, printListArr);
				printSymbolTable(tmp -> dataTable, printArr);
			}
			outputChildren(ch, operation);
		}
		break;
		
		case AST_NODE_STATEMENT: {
			ASTNode * ch = curr -> child;
			outputChildren(ch, operation);
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode * ch = curr -> child -> next;
			if(ch -> localST == NULL)
				return;
			if(operation == 0)
				printSymbolTable(ch -> localST -> dataTable, printVar);
			else
				printSymbolTable(ch -> localST -> dataTable, printArr);
			ch = curr -> child;
			outputChildren(ch, operation);
		}
		break;

		case AST_NODE_CASESTMT: {
			ASTNode * ch = curr -> child;
			outputChildren(ch, operation);
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode * ch = curr -> child -> next;
			if(ch == NULL)
				return;
			if(operation == 0)	
				printSymbolTable(ch -> localST -> dataTable, printVar);
			else
				printSymbolTable(ch -> localST -> dataTable, printArr);
			ch = curr -> child;
			outputChildren(ch, operation);
		}
		break;

		default: {
			/* do nothing */
		}
		break;
	}
}