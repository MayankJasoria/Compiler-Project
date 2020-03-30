#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/utils.h"
#include "data_structures/ast.h"
#include "data_structures/astDef.h"

#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    char* inputfile = "t4.txt";

    /* initializing lexer and parser */
    lexerinit();
    parserInit("grammar_new.erp");
    ComputeFirstAndFollowSets();
    createParseTable();

    parseInputSourceCode(inputfile);
    printf("\n");
    /* printParseTree(PT, outputfile); */
    /* Use PT to construct AST */

    ASTNode* root = constructAST(NULL, NULL, PT);  
    printf("Hooray!!");
}