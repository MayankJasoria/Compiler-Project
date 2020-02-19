#ifndef _N_ARY_TREE
#define _N_ARY_TREE

#include "../utils/utils.h"

typedef stackElement TreeElement;

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
 * @param node	The node whise child is to be added
 * @param data	The data to be added as the child
 * 
 * @return updated tree
 */
Tree insertChild(Tree node, TreeElement data);

// Tree insertChildList(Tree node, List children)
Tree insertChildren(Tree node, rhsNode* children);

// Tree findElement(Tree root, TreeElement data);

#endif