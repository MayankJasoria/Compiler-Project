/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/
	
#include "codeGenDef.h"

/**
 * Initializes the Code Generator for use
 * @param fname	The name of the file into which
 * 				the assembly code should be written
 */
void emitCodeInit(const char* fname);

/**
 * Traverses the AST, and emits NASM assembly on the fly.
 * @param curr	
 * @param fname	Name of the current function. Supply NULL as input
 * 				in the caller function
 */
void emitCodeAST(ASTNode* curr, char* fname);

/**
 * Finalizes Code generation operation and terminates it
 */
void emitCodeFinalize();
