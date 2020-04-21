/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _PASS1_
#define _PASS1_
#include "astDef.h"

/**
 * @param curr		Pointer to the current ASTNode
 * @param fname		Name of the module whose definition contains structure for this node 
 * recursively traverses the children and performs required computations and check for semantic errors.
 */
void traverseAST(ASTNode* curr, char* fname);

/**
 * @param head		Pointer to the current ASTNode
 * @param fname		Name of the module whose definition contains structure for this node 
 * recursively calls pass2AST() for all the siblings of head with the same function name 'fname'.
 * NOTE: it is for the second pass on the AST.
 */
void pass2Children(ASTNode * head, char * fname);

/**
 * @param curr 		Pointer to the current ASTNode
 * @param fname		Name of the module whose definition contains structure for this node 
 * Performs semantic checks specific to a given ASTNode in pass2, majorly type checking
 * and uses pass2Children() to recursively call it on its children.
 */  
void pass2AST(ASTNode* curr, char* fname);

/** 
 * @param curr		Node pointing to the head of the input/output_plist Nodes
 * @param str 		Name of the module
 * The function inserts the linked list to the corresponding global symbol table entry corresponding to 'str'
 */
void insertplist(ASTNode * curr, char * str);

/**
 * @param head		Pointer to the current ASTNode
 * @param fname		Name of the module whose definition contains structure for this node 
 * recursively calls traverseAST() for all the siblings of head with the same function name 'fname'.
 * NOTE: it is for the first pass on the AST.
 */
void traverseChildren(ASTNode * head, char * fname);

/**
 * @param tmp		Pointer to the symbol table entry of the array type variable	
 * @param curr		Pointer to the ASTNode of the index.
 * Performs the static checks on the bounds if possible for the array index access.
 */
void boundChecking(SymTableVar * tmp, ASTNode * curr);

/**
 * @param head		Pointer to the head of the linked list of the input/output parameter list of the called module.
 * @param node		Pointer to the head of the linked list of the idList of actual passed parameters of the called module.		
 * @param localST	Pointer to the symbol table of the local scope of moduleReuseStatement
 * Performs the type checking and matches the types of actual and formal parameter and reports error if present.
 */
int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST);

#endif