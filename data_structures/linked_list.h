/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _LINKED_LIST
#define _LINKED_LIST
#include "../utils/utils.h"

typedef struct node {
    void* data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct {
    Node* head;
    Node* end;
} Head;

typedef Head* List; /* Doubly-linked list */

typedef enum {
    FRONT,
    BACK
} position;

/**
 * Creates and returns a doubly-linked list
 * @return a new Doubly-linked list
 */
List getList();

/**
 * Inserts 'data' to the start or end of the list,
 * depending on position
 * @param list  The list into which the data is to be inserted
 * @param data  The data to be inserted
 * @param dir   Either BEGIN or END, defining the place at which
 *              the element should be inserted into the list
 * 
 * @return updated List
 */
List insertToList(List list, void* data, position dir);

// /**
//  * Deletes a data from the list
//  * @param list  The list from which the data is to be deleted
//  * @param data  The data to be deleted
//  * 
//  * @return updated List
//  */
// List deleteByData(List list, void* data);

/**
 * Deletes the given node from the list
 * @param list      The list from which the node is to be deleted
 * @param element   The element (Node address) to be deleted
 * 
 * @return updated list
 */
List deleteByNode(List list, Node* element);

// /**
//  * Returns the address of an element in list
//  * @param list  The list to be searched
//  * @param data  The data to be found in the list
//  * 
//  * @return Node address of the data; NULL if not found
//  */
// Node* findInList(List list, void* data);

/**
 * Completely destroys a list, freeing all associated memory
 * @param list  The list on which this operation is to be performed
 */
void destroyList(List list);

/**
 * Prints a given linked list, from head to tail
 * 
 * @param list  		The list to be printed
 * @param printElement 	Function to print an element of the given list
 */
void printList(List list, void (*printElement)(void* data));

#endif