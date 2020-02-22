#ifndef _LEXER
#define _LEXER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexerDef.h"
#include "utils/utils.h"

FILE * getStream(FILE * fp);

token * getNextToken();

int hash(const char* s);

void hashTableinit();

int checkIdentifier(char * str);

void lexerinit();

token * makeNewToken(int id);

errorInst * makeNewError(int line_num, char * lex);

void retract(int num);

void error();

void idlengthError();

void ctoa(char ch);

void removeComments(char *testcaseFile);

#endif