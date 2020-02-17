#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


int main() {
	lexerinit();
	FILE * fp = fopen("prog.eg", "r");
	while(endofLexer == 0) {
		fp = getStream(fp);
	}
	int i;
	for(i = 0; i < ntokens; i++)
		printf("%d %s\n", tokenStream[i] -> id, tokenStream[i] -> lex);
	printf("%d\n", ntokens);
}