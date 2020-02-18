#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


int main() {

	tokenStream_cap = 20;
	ntokens = sizeof(keywordList)/sizeof(keywordList[0]);
	chunk_size = 10;

	lexerinit();
	FILE * fp = fopen("prog.eg", "r");
	while(endofLexer == 0) {
		fp = getStream(fp);
	}
	printf("%d\n", ntokens);
}