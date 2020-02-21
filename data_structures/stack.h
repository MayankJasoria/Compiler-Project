#ifndef _STACK
#define _STACK

#include "../utils/utils.h"
#include "linked_list.h"

struct stack {
    int elemCount;
    List st;
};

typedef struct stack* Stack;

/**
 * Creates and returns a new stack
 * @return a new Stack
 */
Stack getStack();

/**
 * Adds the given element to top of stack
 * @param element The element to be added to the top of the stack
 * 
 * @return Updated Stack
 */
Stack push(Stack stack, void* element);

// /**
//  * Adds multiple elements, present within an array of size num, sequentially
//  * to the top of the stack, in the same order as they appear in the array
//  * @param elements Array of elements to be added to the stack
//  * @param num Number of elements to be added to the stack
//  * 
//  * @return Updated Stack
//  */
// Stack pushMany(Stack stack, void** elements, int num);

/**
 * Removes the top element from the stack
 * 
 * @return Updated Stack
 */
Stack pop(Stack stack);

/**
 * Removes the specified number of elements from the top of the stack
 * 
 * @param num Number of elements to remove
 * @return Updated Stack
 */
Stack popMany(Stack stack, int num);

/**
 * Returns the element present at the top of the stack
 */
void* top(Stack stack);

/**
 * Returns number of elements in stack
 */
int numElementsInStack(Stack stack);

/**
 * Informs if a given stack is empty
 * 
 * @return True if the stack is empty, false otherwise
 */
boolean isStackEmpty(Stack stack);

/**
 * Prints the contents of stack from top to bottom
 * 
 * @param st    The stack whose values are to be printed
 */
void printStack(Stack st);

#endif