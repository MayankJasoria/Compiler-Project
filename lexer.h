#ifndef _LEXER
#define _LEXER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexerDef.h"

FILE * getStream(FILE * fp);

token * getNextToken();

void removeComments(char * testcaseFile, char * cheanFile);

int hash(const char* s);

void hashTableinit();

int checkIdentifier(char * str);

void lexerinit();

token * makeNewToken(int id);

errorInst * makeNewError(int line_num, char * lex);

void retract(int num);

void error();

void idlengthError();

char * ctoa(char ch);

#endif