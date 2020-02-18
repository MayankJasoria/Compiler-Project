#include "linked_list.h"

struct stack {
    int elemCount;
    List st;
};

typedef struct stack* Stack;

extern Stack st;

/**
 * Adds the given value to top of stack
 * @param value The value to be added to the top of the stack
 * 
 * @return Updated Stack
 */
Stack push(int value);

/**
 * Adds multiple values, present within an array of size num, sequentially
 * to the top of the stack, in the same order as they appear in the array
 * @param values Array of values to be added to the stack
 * @param num Number of elements to be added to the stack
 * 
 * @return Updated Stack
 */
Stack pushMany(int* values, int num);

/**
 * Removes the top element from the stack
 * 
 * @return Updated Stack
 */
Stack pop();

/**
 * Removes the specified number of elements from the top of the stack
 * 
 * @param num Number of elements to remove
 * @return Updated Stack
 */
Stack popMany(int num);

/**
 * Returns the value present at the top of the stack
 */
int top();