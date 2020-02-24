/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include "n_ary_tree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

treeNode * getTree(stackElement * s) {
	treeNode * root = (treeNode *) malloc(sizeof(treeNode));
	s -> tn = root;
	root -> sym = s -> sym;
	root -> tag = s -> tag;
	root -> parent = NULL;
	root -> child = NULL;
	root -> prev = NULL;
	root -> next = NULL;
	strcpy(root -> lex, "----");
	root -> depth = 0;
	root -> id = 0;
	root -> line_num = -1;
	root -> tok = NULL;
	root -> depth = 0;
	numNodes++;
	root -> isLeaf = True;
	return root;
}

// Tree insertChild(Tree node, TreeElement data) {

// 	if(node == NULL) {
// 		fprintf(stderr, "The given tree is undefined\n");
// 		return node;
// 	}

// 	/* initialize a new child node */
// 	treeNode * childNode = getTree(data);

// 	/* set parent of this node as the given parent node */
// 	childNode->parent = node;

// 	if(node->child == NULL) {
// 		/* parent had no children */
// 		node->child = childNode;
// 		childNode->next = NULL;
// 	} else {
// 		/* parent has children, add to end of list of children */
// 		treeNode* curr = node->child;
// 		while(curr->next != NULL) {
// 			curr = curr->next;
// 		}
// 		curr->next = childNode;
// 		childNode->prev = curr;
// 	}
// 	return node;
// }

Tree insertChildren(Tree node, rhsNode* children) {
	// if(node == NULL) {
	// 	fprintf(stderr, "Given tree is undefined\n");
	// 	return node;
	// }
	// if(node->child != NULL) {
	// 	fprintf(stderr, "This tree already has children defined\n");
	// 	return node;
	// }

	rhsNode * curr = children;

	node -> isLeaf = False;

	treeNode * prev = NULL;
	// treeNode * currChild = NULL;
	
	while(curr != NULL) {
		/* Create the element to add to the tree */
		
		// stackElement newEl;
		// newEl.sym = curr->sym;
		// newEl.tag = curr->tag;

		treeNode * ch = (treeNode *)malloc(sizeof(treeNode));
		ch -> child = NULL;
		ch -> isLeaf = True;
		if(prev == NULL) {
			node -> child = ch;	
		}
		ch -> sym = curr -> sym;
		ch -> tag = curr -> tag;
		ch -> line_num = -1;
		ch -> id = numNodes;
		numNodes++;
		ch -> depth = (node -> depth) + 1;
		strcpy(ch -> lex, "----");
		if(curr -> tag == T && (curr -> sym.T > 54 || curr -> sym.T < 52))
			strcpy(ch -> lex, terminals[curr -> sym.T]);
		// ch -> value = -1;
		ch -> parent = node;
		ch -> next = NULL;
		ch -> prev = prev;
		if(prev != NULL)
			prev -> next = ch;
		prev = ch;
		curr = curr -> next;
		/* insert this element into the tree */
		// if(currChild == NULL) {
		// 	/* First child of the given node */
		// 	currChild = (insertChild(node, newEl))->child;
		// } 
		// else {
		// 	/* Add to list of existing children */
		// 	treeNode * newChild = getTree(newEl);
		// 	newChild->parent = node;
		// 	newChild->prev = currChild;
		// 	currChild->next = newChild;
		// 	currChild = newChild;
		// }
		// curr = curr->next;
	}
	return node;
}