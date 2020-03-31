#ifndef _SYMBOL_TABLE
#define _SYMBOL_TABLE

#include "symbol_TableDef.h"

/**
 * Creates and returns an instance of a new symbol table
 * @return an instance of a new symbol table
 */
SymbolTable getSymbolTable();

/**
 * Inserts a given record into the symbol table
 * @param st	The symbol table into which this record should be added
 * 
 * @return Updated Symbol Table
 */
SymbolTable insertRecord(SymbolTable st /* define arguments here */);

/**
 * Returns a desired record from the symbol table if it exists
 * Otherwise, return NULL
 * @param st	The symbol table from which the record is to be fetched
 * 
 * @return desired record from the symbol table if it exists, otherwise NULL
 */
SymbolTableElement fetchRecord(SymbolTable st /* define arguments here: should ideally be the identifier name*/);

/**
 * Updates a record in the symbol table if it exists. Otherwise, 
 * reports error and returns with the table unchanged
 * @param st	The symbol table in which the record should be updated
 *
 * @return updated symbol table
 */
SymbolTable updateRecord(SymbolTable st /* identifier name, field name, and field value. OR, symbolTableElement */);

#endif