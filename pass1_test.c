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

	char* inputfile = "CodeGeneration_testcases/c10.txt";

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
	FILE* fp = fopen("actRecSize.txt", "w");
	printSymbolTable(fp, globalST, printFunc);
	fclose(fp);

	outputSymbolTable(NULL, root);
	
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