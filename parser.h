/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _PARSER
#define _PARSER

#include "parserDef.h"

#define PRINT_FORMAT  "%-15s:%-15s:%-25s:%-25s:%-25s:%-25s:%-20s"

/* NOTE: Function return types may need to be changed. Check and update as necessary */

/**
 * Initializes the parser for use in future
 * @param filename  The file which contains the grammar rules
 *                  that the parser should use for parsing
 */
void parserInit(char* filename);

/**
 * Computes the first and follow sets for all non terminals
 * the grammar rules 
 */
void ComputeFirstAndFollowSets();

/**
 * Creates the parse table using the grammar rules, and first and follow sets
 */
void createParseTable();

/**
 * Parses the input source code and generates the parse tree.
 * Also, reports any syntactical errors which are identified
 * during the process
 * @param testcaseFile  The source code file
 */
void parseInputSourceCode(char *testcaseFile);

/**
 * Writes the inorder traversal of the parse tree to a given file
 * @param outfile   The file into which the inorder traversal is to be written
 */
void printParseTree(Tree PT, char *outfile);

#endif