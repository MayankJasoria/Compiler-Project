#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int main() {
	lexerinit();
	FILE * fp = fopen("progerr.eg", "r");
	if(fp == NULL) {
		printf("Error opening file\n");
		return 0;
	}
	while(endofLexer == 0) {
		fp = getStream(fp);
	}
	int i;
	for(i = 0; i < ntokens; i++)
		printf("Token Sequence: %d Token id:%d Token Lexeme: %s\n", i + 1, tokenStream[i] -> id, tokenStream[i] -> lex);
	printf("Total number of token generated: %d\n", ntokens);
	removeComments("prog.eg", "clean.eg");
}