/*  GROUP 48:
    PUNEET ANAND    2016B4A70497P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _N_ARY_TREE
#define _N_ARY_TREE

#include "../utils/utils.h"
#include "../parserDef.h"
#include "../lexerDef.h"



/**
 * Creates and returns a new tree, having given data at its root
 * @param data 	The data to be populated as the root of the tree
 * 
 * @return new tree
 */
Tree getTree(stackElement * s);

/**
 * Inserts a new child to a given node of the tree
 * @param node	The node whose child is to be added
 * @param data	The data to be added as the child
 * 
 * @return updated tree
 */
// Tree insertChild(Tree node, rhsNode * ch);

// Tree insertChildList(Tree node, List children)

/**
 * Inserts a list of children (present in linked list rhsNode)
 * to the specified node (whose children have not yet been added)
 * @param node		The node whise children are to be added
 * @param children	The list of children to be added
 * 
 * @return updated tree
 */ 
Tree insertChildren(Tree node, rhsNode* children);

// Tree findElement(Tree root, TreeElement data);

// /**
//  * Prints the list, level-wise, to the console
//  * @param root The root node of the tree to be printed
//  */
// void printTree(Tree root);

int numNodes;

#endif