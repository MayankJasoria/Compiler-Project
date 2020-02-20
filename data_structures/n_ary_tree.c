#include "n_ary_tree.h"
#include "stack.h"
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

	if(node == NULL) {
		fprintf(stderr, "The given tree is undefined\n");
		return node;
	}

	/* initialize a new child node */
	Tree childNode = getTree(data);

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
	return node;
}

Tree insertChildren(Tree node, rhsNode* children) {
	if(node == NULL) {
		fprintf(stderr, "Given tree is undefined\n");
		return node;
	}
	if(node->child != NULL) {
		fprintf(stderr, "This tree already has children defined\n");
		return node;
	}

	rhsNode* curr = children;
	Tree currChild = NULL;
	while(curr != NULL) {
		/* Create the element to add to the tree */
		TreeElement newEl;
		newEl.sym = curr->sym;
		newEl.tag = curr->tag;

		/* insert this element into the tree */
		if(currChild == NULL) {
			/* First child of the given node */
			currChild = (insertChild(node, newEl))->child;
		} else {
			/* Add to list of existing children */
			Tree newChild = getTree(newEl);
			newChild->parent = node;
			newChild->prev = currChild;
			currChild->next = newChild;
			currChild = newChild;
		}
		curr = curr->next;
	}
	return node;
}