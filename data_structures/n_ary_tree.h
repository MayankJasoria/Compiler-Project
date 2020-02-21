#ifndef _N_ARY_TREE
#define _N_ARY_TREE

#include "../utils/utils.h"

typedef struct treeElement {
	stackElement* token;
	char lex[25];
	int depth;
	int id;
} TreeElement;

typedef struct treeNode {
	TreeElement data;
	struct treeNode* parent;
	struct treeNode* prev;
	struct treeNode* next;
	struct treeNode* child;
} TreeNode;

typedef TreeNode* Tree;


/**
 * Creates and returns a new tree, having given data at its root
 * @param data 	The data to be populated as the root of the tree
 * 
 * @return new tree
 */
Tree getTree(TreeElement data);

/**
 * Inserts a new child to a given node of the tree
 * @param node	The node whose child is to be added
 * @param data	The data to be added as the child
 * 
 * @return updated tree
 */
Tree insertChild(Tree node, TreeElement data);

// 

/**
 * Inserts a list of children (present in linked list rhsNode)
 * to the specified node (whose children have not yet been added)
 * @param node		The node whise children are to be added
 * @param children	The list of children to be added
 * 
 * @return updated tree
 */
Tree insertChildList(Tree node, List children);

// Tree findElement(Tree root, TreeElement data);

// /**
//  * Prints the list, level-wise, to the console
//  * @param root The root node of the tree to be printed
//  */
// void printTree(Tree root);

#endif