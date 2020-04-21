/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */

#ifndef _AST
#define _AST

#include "astDef.h"
#include "queue.h"

/**
 * Creates and returns a blank Abstract Syntax Tree root
 * @param type	The type for a given AST node
 * 
 * @return a new AST node of specified type
 */
ASTNode* getASTNode(astNodeType type);

/**
 * Returns datatype of expression
 * @param expr	AST Node representing the root of expression subtree
 */
int getExprType(ASTNode * expr);

/**
 * Adds a child to a given node as the first child
 * @param parent	The parent node, to which a child should be added
 * @param child		The child node to be added	
 * 
 * @return updated parent node
 */
ASTNode* addChild(ASTNode* parent, ASTNode* child);

/**
 * Constructs an AST downward from a given root (parent node)
 * @param parent		The parent node, for which the AST is being constructed
 * @param prev_sibling	The previous sibling of the current node
 */
ASTNode* constructAST(ASTNode* parent, ASTNode* prev_sibling, treeNode* pt);

/**
 * Prints the complete AST, in a breadth first manner
 * @param root  The root of the current subtree of AST
 */ 
void printAST(ASTNode* root);

/**
* Prints all the details of an AST Node, in DFS order
* @param curr The current AST Node
*/ 
void printNode(ASTNode* curr);

/**
 * Returns the size of the current AST
 */
static inline int getASTSize() {
    return ASTSize;
}

/**
 * Returns the number of nodes in the current AST
 */
static inline int getASTnumNodes() {
    return numASTnodes;
}

#endif