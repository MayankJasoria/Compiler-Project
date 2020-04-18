/*  GROUP 48:
PUNEET ANAND    2016B4A70487P
MAYANK JASORIA  2016B1A70703P
SHUBHAM TIWARI  2016B4A70935P
VIBHAV OSWAL    2016B4A70594P */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/utils.h"
#include "data_structures/ast.h"
#include "data_structures/astDef.h"


#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    char* inputfile = "testcases/test3.txt";

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