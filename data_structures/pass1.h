/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _PASS1_
#define _PASS1_
#include "astDef.h"

void traverseAST(ASTNode* curr, char* fname);

void pass2Children(ASTNode * head, char * fname);

void pass2AST(ASTNode* curr, char* fname);

void insertplist(ASTNode * curr, char * str);

void traverseChildren(ASTNode * head, char * fname);

void boundChecking(SymTableVar * tmp, ASTNode * curr);

int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST);

#endif