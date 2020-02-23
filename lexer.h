#ifndef _LEXER
#define _LEXER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexerDef.h"
#include "utils/utils.h"

/**
 * Reads a file from the iven file pointer in
 * fixed sized chunks of 255 bytes
 * @param fp    pointer of a file to be read
 * 
 * @return Updated file pointer
 */
FILE * getStream(FILE * fp);

/**
 * Returns the next valid token in the source code
 */ 
token * getNextToken();

/**
 * Computes the hash for a given string
 * @param s The string whose hash value is to be computed
 * 
 * @return The computed hash value
 */
int hash(const char* s);

/**
 * Initializes the lexer for future use
 */
void lexerinit();

/**
 * Removes all comments from the given source code and prints 
 * the resulting code to console, with preserved line numbers
 * @param testcaseFile  The source code file whose comments are to be removed
 */
void removeComments(char *testcaseFile);

#endif