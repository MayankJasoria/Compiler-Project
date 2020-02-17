#ifndef _LEXER
#define _LEXER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexerDef.h"

FILE * getStream(FILE * fp);

token * getNextToken();

void removeComments(char * testcaseFile, char * cheanFile);

// bool isKeyword(token * tok);

#endif