/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */

#ifndef _SYMBOL_TABLE
#define _SYMBOL_TABLE

#include "symbol_TableDef.h"

/**
 * Creates and returns an instance of a new symbol table
 * @return an instance of a new symbol table
 */
SymbolTable getSymbolTable();

// /**
//  * Inserts a given record into the symbol table
//  * @param st	The symbol table into which this record should be added
//  * 
//  * @return Updated Symbol Table
//  */
// SymbolTable insertRecord(SymbolTable st /* define arguments here */);

// /**
//  * Returns a desired record from the symbol table if it exists
//  * Otherwise, return NULL
//  * @param st	The symbol table from which the record is to be fetched
//  * 
//  * @return desired record from the symbol table if it exists, otherwise NULL
//  */
// SymbolTableElement fetchRecord(SymbolTable st /* define arguments here: should ideally be the identifier name*/);

// /**
//  * Updates a record in the symbol table if it exists. Otherwise, 
//  * reports error and returns with the table unchanged
//  * @param st	The symbol table in which the record should be updated
//  *
//  * @return updated symbol table
//  */
// SymbolTable updateRecord(SymbolTable st /* identifier name, field name, and field value. OR, symbolTableElement */);

/**
 * Inserts a record for a variable into the symbol table
 * @param st		The symbol table into which the variable record should be added
 * @param name		Name of the variable
 * @param width		The total memory size required for storing the variable data
 * @param dataType	The dataType of the variable
 * 
 * @return updated symbol table
 */
SymbolTable insertVarRecord(SymbolTable st, char* name, int width, astDataType dataType);

/**
 * Inserts a record for a function into the symbol table
 * @param st	The symbol table in which the function record should be added
 * @param name	The name of the function
 * 
 * @return updated symbol table
 */
SymbolTable insertFuncRecord(SymbolTable st, char* name);

/**
 * Returns the record for a variable from the symbol table,
 * if it exists. Otherwise returns NULL
 * @param st	The symbol table from which the variable is to be fetched
 * @param name	The name of the variable
 * 
 * @return pointer to the record if it is found, otherwise NULL
 */
SymTableVar* fetchVarData(SymbolTable st, char* name);

/**
 * Returns the record for a function from the symbol table,
 * if it exists. Otherwise returns NULL
 * @param st	The symbol table from which the function is to be fetched
 * @param name	The name of the function
 * 
 * @return pointer to the record if it is found, otherwise NULL
 */
SymTableFunc* fetchFuncData(SymbolTable st, char* name);

/**
 * Adds a new variable into the symbol table of variables associated with a function
 * @param st		The symbol table from which the function is to be fetched
 * @param funcName		The name of the function
 * @param varName		Name of the variable
 * @param varWidth		The total memory size required for storing the variable data
 * @param varDataType	The dataType of the variable
 * 
 * @return updated Symbol Table
 */
SymbolTable addDataToFunction(SymbolTable st, char* funcName, char* varName, int varWidth, astDataType varDataType);

#endif