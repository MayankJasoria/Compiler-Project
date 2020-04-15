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

int main(int argc, char* argv[]) {

	char* inputfile = "Testcases_stage2/t2.txt";

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
	// FILE* fp = fopen("SymOut.txt", "w");
	// printSymbolTable(fp, fetchFuncData("var_demo_array") -> dataTable, printVar);
	// fclose(fp);

	outputSymbolTable(NULL, root);
	printf("Hooray!!");
}