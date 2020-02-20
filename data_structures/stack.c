#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack getStack() {
    Stack newStack = (Stack) malloc(sizeof(struct stack));
    newStack->elemCount = 0;
    newStack->st = NULL;
    return newStack;
}

Stack push(Stack stack, void* element) {
    if(stack == NULL) {
        printf("The given stack was undefined. Created a new stack\n");
    }
    if(stack->st == NULL) {
        /* create a new stack */
        stack->st = getList();
        stack->elemCount = 0;
    }
    stack->st = insertToList(stack->st, element, FRONT);
    stack->elemCount++;
    return stack;
}

// Stack pushMany(Stack stack, void* elements, int num) {
//     int i;
//     for(i = 0; i < num; i++) {
//         stack = push(stack, elements[i]);
//     }
//     return stack;
// }

Stack pop(Stack stack) {
    if(stack->st == NULL) {
        fprintf(stderr, "The stack is empty\n");
        return stack;
    }
    stack->st = deleteByNode(stack->st, stack->st->head);
    stack->elemCount--;

    if(stack->elemCount == 0) {
        /* freeing the memory consumed for stack, assuming it won't be needed later */
        free(stack->st);
        stack->st = NULL;
        free(stack);
        stack = NULL;
    }
    return stack;
}

Stack popMany(Stack stack, int num) {
    if(stack->elemCount < num) {
        fprintf(
            stderr, 
            "More elements [%d] requested for deletion than [%d] present in stack. Stack has not been modified\n", 
            num, 
            stack->elemCount
        );
        return stack;
    }
    while(num > 0) {
        stack = pop(stack);
        num--;
    }
    return stack;
}

void* top(Stack stack) {
    if(stack != NULL && stack->st != NULL) {
        return stack->st->head->data;
    } else {
        fprintf(stderr, "The stack is empty\n");
        return NULL;
    }
}

int numElementsInStack(Stack stack) {
    if(stack == NULL) {
        return 0;
    } else {
        return stack->elemCount;
    }
}