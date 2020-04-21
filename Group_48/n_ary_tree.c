/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/
	
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
	root -> rule_num = -1;
	root -> tok = NULL;
	root -> depth = 0;
	numNodes++;
	root -> isLeaf = True;
	return root;
}

Tree insertChildren(Tree node, rhsNode* children) {
	rhsNode * curr = children;

	node -> isLeaf = False;

	treeNode * prev = NULL;
	
	while(curr != NULL) {
		/* Create the element to add to the tree */
		treeNode * ch = (treeNode *)malloc(sizeof(treeNode));
		ch -> child = NULL;
		ch -> isLeaf = True;
		if(prev == NULL) {
			node -> child = ch;	
		}
		ch -> sym = curr -> sym;
		ch -> tag = curr -> tag;
		ch -> line_num = -1;
		ch -> rule_num = -1;
		ch -> id = numNodes;
		numNodes++;
		ch -> depth = (node -> depth) + 1;
		strcpy(ch -> lex, "----");
		if(curr -> tag == T && (curr -> sym.T > 54 || curr -> sym.T < 52))
			strcpy(ch -> lex, terminals[curr -> sym.T]);
		ch -> parent = node;
		ch -> next = NULL;
		ch -> prev = prev;
		if(prev != NULL)
			prev -> next = ch;
		prev = ch;
		curr = curr -> next;
	}
	return node;
}