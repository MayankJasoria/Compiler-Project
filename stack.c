#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack st = NULL;

Stack push(int value) {
    if(st == NULL) {
        /* create a new stack */
        st = (Stack) malloc(sizeof(struct stack));
        st->elemCount = 0;
    }
    st->st = insert(value, BEGIN);
    st->elemCount++;
    return st;
}

Stack pushMany(int* values, int num) {
    int i;
    for(i = 0; i < num; i++) {
        st = push(values[i]);
    }
    return st;
}

Stack pop() {
    if(st == NULL) {
        fprintf(stderr, "The stack is empty\n");
        return st;
    }
    st->elemCount--;
    st->st = deleteByValue(top());

    if(st->elemCount == 0) {
        /* freeing the memory consumed for stack, assuming it won't be needed later */
        free(st);
        st = NULL;
    }
    return st;
}

Stack popMany(int num) {
    if(st->elemCount < num) {
        fprintf(stderr, "More elements requested for deletion than present in stack. Stack has not been modified\n");
        return st;
    }
    while(num > 0) {
        st = pop();
    }
    return st;
}

int top() {
    if(st != NULL) {
        return st->st->value;
    } else {
        fprintf(stderr, "The stack is empty\n");
        return -1;
    }
}

int numElementsInStack() {
    if(st == NULL) {
        return 0;
    } else {
        return st->elemCount;
    }
}