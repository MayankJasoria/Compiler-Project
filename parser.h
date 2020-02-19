#ifndef _PARSER
#define _PARSER

#include "parserDef.h"

void insertElement (int idx, char * str, typeOfSymbol t, int en);

hashNode * hashLookup(int idx, char * str);

void populateHashTable();

rhsNode * make_rhsNode(char * str, rhsNode * prev, int id);

void populateGrammar(char * filename);

unsigned long long int setUnion (unsigned long long int a, unsigned long long int b);

int findinSet(unsigned long long int a, int i);

unsigned long long int firstSet(nonterminal nonT);

unsigned long long int firstFollow(rhsNode * node);

unsigned long long int followSet(nonterminal nonT);

/* To do: include only those which will be used. */





void parserInit(char* filename);

/* Function return types may need to be changed. Check and update as necessary */
void ComputeFirstAndFollowSets();

void createParseTable();

void parseInputSourceCode(char *testcaseFile, table T);

void printParseTree(parseTree PT, char *outfile);

#endif