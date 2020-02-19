#include "n_ary_tree.h"
#include <stdio.h>

Tree getTree(TreeElement data) {
	Tree root = (Tree) malloc(sizeof(TreeNode));
	root->data = data;
	root->parent = NULL;
	root->prev = NULL;
	root->next = NULL;
	root->child = NULL;
	return root;
}

Tree insertChild(Tree node, TreeElement data) {
	/* initialize a new child node */
	Tree childNode = (Tree) malloc(sizeof(TreeNode));
	childNode->data = data;
	childNode->prev = NULL;
	childNode->child = NULL;

	/* set parent of this node as the given parent node */
	childNode->parent = node;

	if(node->child == NULL) {
		/* parent had no children */
		node->child = childNode;
		childNode->next = NULL;
	} else {
		/* parent has children, add to end of list of children */
		TreeNode* curr = node->child;
		while(curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = childNode;
		childNode->prev = curr;
	}
}