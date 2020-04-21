/*  
    GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P 
*/
	
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "utils.h"

Stack getStack() {
    Stack newStack = (Stack) malloc(sizeof(struct stack));
    newStack->elemCount = 0;
    newStack->st = NULL;
    return newStack;
}

Stack push(Stack stack, void* element) {
    if(stack == NULL) {
        stack = getStack();
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

Stack pop(Stack stack) {
    if(stack->st == NULL) {
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
        return NULL;
    }
}

int numElementsInStack(Stack stack) {
    if(stack == NULL) {
        return 0;
    }
    return stack->elemCount;
}

boolean isStackEmpty(Stack stack) {
    if(stack == NULL || stack->elemCount == 0) {
        return True;
    }
    return False;
}

void printStack(Stack st, void (*printElement)(void* data)) {
    if(st == NULL) {
        fprintf(stderr, "The given stack is empty\n");
        return;
    }
    printf("Top\n");
    printf(" |\n");
    printf("\\/\n");
    printList(st->st, printElement);
}