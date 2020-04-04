#include "astDef.h"

void insertplist(ASTNode * curr, char * str);

void traverseChildren(ASTNode * head, char * fname);

void boundChecking(SymTableVar * tmp, ASTNode * curr);

int listTypeMatch(Node* head, ASTNode* node, SymTableFunc* localST);

void traverseAST(ASTNode* curr, char* fname);