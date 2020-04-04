#ifndef _PASS1_
#define _PASS1_
#include "astDef.h"

void traverseAST(ASTNode* curr, char* fname);

void insertplist(ASTNode * curr, char * str);

void traverseChildren(ASTNode * head, char * fname);

void boundChecking(SymTableVar * tmp, ASTNode * curr);

int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST);

#endif