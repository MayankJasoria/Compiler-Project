#ifndef _PARSER
#define _PARSER

#include "parserDef.h"

void parserInit(char* filename);

/* Function return types may need to be changed. Check and update as necessary */
void ComputeFirstAndFollowSets (grammar G, FirstAndFollow F);

void createParseTable(FirstAndFollow F, table T);

void parseInputSourceCode(char *testcaseFile, table T);

void printParseTree(parseTree PT, char *outfile);

#endif