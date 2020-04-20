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

#include "data_structures/st.h"
#include "lexer.h"
#include "parser.h"
#include "data_structures/pass1.h"
#include "codeGen.h"

int main(int argc, char* argv[]) {

	char* inputfile = "mytest.txt";

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

	globalST = getSymbolTable();

	traverseAST(root, "");
	pass2AST(root, "");
	
	/* Printing function activation record sizes */
	// FILE* fp = fopen("actRecSize.txt", "w");
	// printSymbolTable(globalST, printFunc);
	// fclose(fp);

	// outputSymbolTable(root);
	
	// int parseTreeSize = getParseTreeSize();
	// int astSize = getASTSize();
	// int numParseTreeNodes = getParseTreeNumNodes();
	// int astNodesCount = getASTnumNodes();

	// printf("\nParse Tree size: %d\n", parseTreeSize);
	// printf("AST size: %d\n", astSize);
	// printf("Number of parse tree nodes: %d\n", numParseTreeNodes);
	// printf("Number of AST nodes: %d\n", astNodesCount);

	/**
	 * CODE GENERATION!
	 */
	emitCodeInit("code.asm");
	emitCodeAST(root, NULL);
	emitCodeFinalize();
	printf("Hooray!!\n");
}