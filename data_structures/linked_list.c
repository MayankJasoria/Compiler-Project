/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

List getList() {
	List newList = (List) malloc(sizeof(Head));
	newList->head = NULL;
	newList->end = NULL;
	return newList;
}

List insertToList(List list, void* data, position dir) {
	if(list == NULL) {
		// printf("The given list was undefined. Created a new list\n");
		list = getList();
	}
	/* Defining new node to be inserted */
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = data;
	if(list->head == NULL) {
		/* First element of list */
		list->head = newNode;
		list->end = newNode;
		newNode -> next = NULL;
		newNode -> prev = NULL;
		return list;
	}
	if(dir == FRONT) {
		/* Insert at beginning of list */
		newNode->next = list->head;
		newNode->prev = NULL;
		list->head->prev = newNode;
		list->head = newNode;
	} else if(dir == BACK) {
		/* Inserting at end of list */
		newNode->next = NULL;
		list->end->next = newNode;
		newNode->prev = list->end;
		list->end = newNode;
	} else {
		/* Some unknown type of position has been entered */
		// fprintf(stderr,"Error: Unknown Direction\n");
	}
	return list;
}

// List deleteByData(List list, void* data) {
// 	if(list->head == NULL) {
// 		fprintf(stderr,"List is empty\n");
// 		return list;
// 	}
// 	Node* curr = list->head;
// 	Node* prev = NULL;
// 	short deleted = 0;
// 	while(curr != NULL) {
// 		if(curr->data == data) {
// 			/* this is the node to be deleted */
// 			if(prev == NULL) {
// 				/* First element */
// 				list->head = curr->next;
// 				if(list->head == NULL) {
// 					/* only element of the list; update end pointer */
// 					list->end = NULL;
// 				} else {
// 					list->head->prev = NULL;
// 				}
// 			} else {
// 				/* internal element */
// 				prev->next = curr->next;
// 				if(prev->next == NULL) {
// 					/* delete from end of list; update end pointer */
// 					list->end = prev;
// 				} else {
// 					prev->next->prev = curr->prev;
// 				}
// 			}
// 			free(curr);
// 			deleted = 1;
// 			break;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	if(deleted == 0) {
// 		fprintf(stderr,"Element to be deleted not found\n");
// 	}
// 	return list;
// }

List deleteByNode(List list, Node* element) {
	if(element == NULL) {
		// fprintf(stderr,"Element does not exist\n");
		return list;
	}
	if(list->head == NULL) {
		// fprintf(stderr,"List is empty\n");
		return list;
	}
	if(element->prev == NULL) {
		/* first element */
		list->head = element->next;
		if(list->head == NULL) {
			/* List had only one element */
			list->end = NULL;
		} else {
			list->head->prev = NULL;
		}
	} else {
		element->prev->next = element->next;
		if(element->next == NULL) {
			/* Deleting last element */
			list->end = element->prev;
		} else {
			element->next->prev = element->prev;
		}
	}
	free(element->data);
	free(element);
	return list;
}

// Node* findInList(List list, void* data) {
// 	Node* curr = list->head;
// 	while(curr != NULL) {
// 		if(curr->data == data) {
// 			break;
// 		}
// 		curr = curr->next;
// 	}
// 	return curr;
// }

void destroyList(List list) {
	/* traverse from end of list */
	while(list->end != NULL) {
		Node* del = list->end;
		list->end = list->end->prev;
		free(del);
		list->end->next = NULL;
	}
	/* list is empty */
	list->head = NULL;

	/* finally, delete the list */
	free(list);
	list = NULL;
}

void printList(List list, void (*printElement)(void* data)) {
	if(list == NULL) {
		fprintf(stderr, "The given list is undefined\n");
		return;
	}

	Node* curr = list->head;
	while(curr != NULL) {
		printf("{");
		printElement(curr->data);
		printf("} --> ");
		curr = curr->next;
	}
	printf("NULL\n");
}