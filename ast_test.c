#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/utils.h"

#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    char* inputfile = "";

    /* initializing lexer and parser */
    lexerinit();
    parserInit("grammar_new.erp");
    ComputeFirstAndFollowSets();
    createParseTable();

    parseInputSourceCode(inputfile);
    printf("\n");
    /* printParseTree(PT, outputfile); */
    /* Use PT to construct AST */

    
}