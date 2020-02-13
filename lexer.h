#define _LEXER
#ifndef _LEXER

#include <stdlib.h>
#include "lexerDef.h"

FILE * getStream(FILE * fp);

token * getNextToken();

void removeComments(char * testcaseFile, char * cheanFile);

bool isKeyword(token * tok);

#endif