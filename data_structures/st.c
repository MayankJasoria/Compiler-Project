/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astDef.h"
#include "hash_map.h"

#define PRINT_VARIABLE_HEADINGS "%-20s%-20s%-20s%-10s%-10s%-15s%-10s%-15s%-10s%-15s\n"
#define PRINT_VARIABLE_DATA "%-20s%-20s%-3d-%-16d%-10d%-10s%-15s%-10s%-15s%-10d%-15d\n" 
#define PRINT_VAR_ARRAY_DATA "%-20s%-20s%-3d-%-16d%-10d%-10s%-15s[%-3d,%-3d] %-15s%-10d%-15d\n"
#define PRINT_FUNC_HEADINGS "%-15s%-15s%-15s%-15s\n"
#define PRINT_FUNC_DATA "%-15s%-15d%-15d%-15d"

int typeSize[] = {2, 4, 1, -1, 8};

/* Doubts regarding the hash table implementation:
	1. if item not there in table, does getDataFromTable return NULL.
	2. make an array typeSize, after seeing the MASM doc. (done)
	3. The st taken in the I/P of fetchVarData is same as localST
	4. The list Type match.
	5. Check the ast.c alone.
	6. insertinputplist()
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

SymTableVar * fetchVarData(SymTableFunc * func, char* name) {
	SymTableVar* data = NULL;
	while(func != NULL) {
		data = (SymTableVar*) getDataFromTable(func -> dataTable, name, stringHash);
		if(data == NULL) {
			/* scan input_plist */
			data = (SymTableVar*) findInList(func->input_plist, name, string_comp_id);
		}
		if(data != NULL) {
			break;
		}
		func = func -> parent;
	}
	return data;
}

SymTableFunc * fetchFuncData(char* name) {
	SymTableFunc* data = (SymTableFunc*) getDataFromTable(globalST, name, stringHash); //functions can only be declared in globalST unlike variables
	return data;
}

void insertVarRecord(SymTableFunc * func, char* name, int width, int offset, astDataType dataType, SymDataType s) {

	SymTableVar* data = (SymTableVar*) malloc(sizeof(SymTableVar));
	strcpy(data -> name, name);
	data -> width = width;
	data -> offset = offset;
	data -> dataType = dataType;
	data -> type = SYM_VARIABLE;
	data -> sdt = s;
	data -> table = func;

	func -> dataTable = insertToTable(func -> dataTable, name, data, stringHash);
}

void addDataToFunction(SymTableFunc* funcData, char * fname, char* varName, astDataType varDataType, int line_num) {
	
	SymTableFunc * fun = fetchFuncData(fname);

	if(getDataFromTable(funcData -> dataTable, varName, stringHash) == NULL) {
		int offset = fun -> actRecSize;
		int width = typeSize[varDataType];
		SymDataType s;
		insertVarRecord(funcData , varName, width, offset, varDataType, s);
		// st = insertVarRecord(st, varName, varWidth, offset, varDataType);
		fun -> actRecSize += width;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item %s already exists within the scope of this function. No changes have been made. Redeclaration on line %d\n", varName, line_num);
	}
}

void addArrToFunction(SymTableFunc * funcData, char * fname, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {
	
	SymTableFunc * fun = fetchFuncData(fname);
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
			strcpy(a -> highId, lft -> nodeData.leaf -> tn -> lex);

		SymDataType s;
		s.r = a;

		int varWidth;
		if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM && right -> nodeData.leaf -> type == AST_LEAF_IDXNUM)
			varWidth = typeSize[varDataType]*(a -> high - a -> low + 1) + typeSize[AST_TYPE_POINTER];
		else
			varWidth = typeSize[AST_TYPE_POINTER];
		insertVarRecord(funcData, varName, varWidth, offset, AST_TYPE_ARRAY, s);
		fun->actRecSize += varWidth;
	} 
	else {
		fprintf(stderr, 
		"A record for the given data item already exists within the scope of this function. No changes have been made. Redeclaration on line %d\n", lft -> nodeData.leaf -> tn -> line_num);
	}
}

SymTableFunc* insertFuncRecord(char* name) {

	if(fetchFuncData(name) != NULL) {
		// fprintf(stderr, "A record with the given already exists within the symbol table.");
		return NULL;
	}

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
	data -> level = 0;
	strcpy(data -> dependentVar, "");
	strcpy(data -> nextJump, "");
	insertToTable(globalST, name, data, stringHash);
	return data;
}

/* Small error in it , parent */
SymTableFunc * getFuncTable(char * fname, SymTableFunc * par) {

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
	strcpy(data -> name, "");
	strcpy(data -> dependentVar, "");
	strcpy(data -> nextJump, "");
	return data;
}

/**
 * Assumption: The function record (name) is already hashed to the symbol table
 * The size of the activation record is computed dynamically everytime this
 * function is called for a new variable. For other details, 
 * @see symbol_table.h
 */
void addParamToFunction(SymTableFunc* funcData, int paramType, char* varName, astDataType varDataType) {

	/* compute offset */
	int offset = funcData -> actRecSize;

	/* Create a record for the variable */
	SymTableVar* varData = (SymTableVar*) malloc(sizeof(SymTableVar));
	varData -> type = SYM_VARIABLE;
	strcpy(varData -> name, varName);
	varData -> offset = offset;
	varData -> width = typeSize[varDataType];
	varData -> dataType = varDataType;
	SymDataType new;
	varData -> sdt = new;
	varData -> isAssigned = 0;

	/* update activation record size */
	funcData -> actRecSize += varData -> width;
	
	/* populate correct list */
	if(paramType == 0) {
		funcData -> input_plist = insertToList(funcData -> input_plist, varData, BACK);
	} 
	else {
		funcData -> output_plist = insertToList(funcData -> output_plist, varData, BACK);

		insertVarRecord(funcData, varName, varData->width, varData->offset, varData->dataType, new);
	}
}

void addArrParamToFunction(SymTableFunc * funcData, int paramType, char* varName, ASTNode * lft, ASTNode * right, astDataType varDataType) {

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
	if(lft -> nodeData.leaf -> type == AST_LEAF_IDXNUM && right -> nodeData.leaf -> type == AST_LEAF_IDXNUM)
		varWidth = typeSize[varDataType]*(a -> high - a -> low + 1) + typeSize[AST_TYPE_POINTER];
	else
		varWidth = typeSize[AST_TYPE_POINTER];
	SymTableVar * varData = (SymTableVar *)malloc(sizeof(SymTableVar));
	strcpy(varData -> name, varName);
	varData -> type = SYM_VARIABLE;
	varData -> width = varWidth;
	varData -> offset = offset;
	varData -> dataType = AST_TYPE_ARRAY;
	varData -> sdt = s;
	if(paramType == 0) {
		funcData -> input_plist = insertToList(funcData -> input_plist, varData, BACK);
	} else {
		funcData -> output_plist = insertToList(funcData -> output_plist, varData, BACK);
		insertVarRecord(funcData, varName, varWidth, offset, AST_TYPE_ARRAY, s);
	}

	/* update activation record size */
	// funcData -> actRecSize += varData -> width;
	
	funcData->actRecSize += varWidth;
}

/* Utility functions */

/**
 * Comparator for SymTableVar type of data withing linked list
 */
int string_comp_id(void* data, void* list_ele) {
	return strcmp((char *)data, ((SymTableVar *)list_ele)->name) == 0;
}

void printVar(FILE* fp, void* data) {
	
	SymTableVar* varData = (SymTableVar*) ((hashElement*) data)->data;
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
	int offset = tab -> offset;
	int nestLevel = tab -> level;
	/* TODO: left index, right index. Need if else in the print itself */

	fprintf(fp, PRINT_VARIABLE_DATA, varData->name, varData->type, varData->isAssigned, varData->width, varData->offset, typeName[varData->dataType]);
}

void printFunc(FILE* fp, void* data) {
	SymTableFunc* funcData = (SymTableFunc*) data;
	fprintf(fp, PRINT_FUNC_DATA, funcData->name, funcData->type, funcData->isDeclared, funcData->isDefined);
}


/**
 *  For printing the Symbol Table giving following information (ten in number) for each variable identifier at each line using formatted output.[ Use width of variables of type integer as 2, of real as 4 and of boolean as 1 for printing the symbol table] 
Variable name 
Scope - module name
scope - line number pairs of start and end of the scope
width    (if a variable is of array type, then add 1 to total requirement for all elements of an array for holding address of the first element) 
is array
if array, whether static or dynamic    
if array, range variables or number lexemes (e.g. [m, n], [p, q], [10, 20] etc.)
type of element
offset
nesting level (for an input or output parameter, level= 0, local variable in function definition, level = 1, any variable inside a nested scope should get its level incremented appropriately)

a      read_array                   19-27        4       no         ---                   ---                  real        54  3
B      switch_var_demo1       		36- 56      43     yes      static array    	 [10,  30]        			integer    	26  2
*/
void printSymbolTable(SymbolTable st, void (printElement)(FILE*, void*)) {
	FILE * fp = fopen("please.txt", "w");
	if(printElement == printVar) {
		fprintf(fp, PRINT_VARIABLE_HEADINGS, "Variable Name", "Type", "Is Assigned", "Width", "Offset", "AST DataType");
	} else if(printElement == printFunc) {
		fprintf(fp, PRINT_FUNC_HEADINGS, "Function Name", "Type", "Is Declared", "Is Defined");
	}
	printHashTable(fp, st, printElement);
}

void outputChildren(ASTNode * head) {
	ASTNode * ch = head;
	while(ch != NULL) {
		outputSymbolTable(ch);
		ch = ch -> next;
	}
}

void outputSymbolTable(ASTNode * curr) {
	switch(curr -> type) {
		case AST_NODE_PROGRAM: {
			ASTNode* ch = curr -> child;
			outputChildren(ch);
		}
		break;

		case AST_NODE_MODULELIST: {
			ASTNode* ch = curr -> child;
			if(curr -> nodeData.moduleList -> type == AST_MODULE_DRIVER) {
				SymTableFunc * dr = fetchFuncData("driver");
				printSymbolTable(dr -> dataTable, printVar);
			}
			else 
				outputChildren(ch);
		}
		break;

		case AST_NODE_MODULE: {
			ASTNode* ch = curr -> child;
			SymTableFunc* tmp;
			char name[30];
			strcpy(name, ch -> nodeData.leaf -> tn -> lex);
			tmp = fetchFuncData(name);
			printSymbolTable(tmp -> dataTable, printVar);
			outputChildren(ch);
		}
		break;
		
		case AST_NODE_STATEMENT: {
			ASTNode * ch = curr -> child;
			outputChildren(ch);
		}
		break;

		case AST_NODE_CONDSTMT: {
			ASTNode * ch = curr -> child -> next;
			printSymbolTable(ch -> localST -> dataTable, printVar);
			ch = curr -> child;
			outputChildren(ch);
		}
		break;

		case AST_NODE_ITERSTMT: {
			ASTNode * ch = curr -> child -> next;
			if(ch == NULL)
				return;
			printSymbolTable(ch -> localST -> dataTable, printVar);
			ch = curr -> child;
			outputChildren(ch);
		}
		break;

		default: {
			/* do nothing */
		}
		break;
	}
}