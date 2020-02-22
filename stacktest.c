#include "data_structures/stack.h"
#include <stdlib.h>
#include <string.h>

void main() {
    Stack s = getStack();

    for (int i=0; i <5; i++) {

        s = push(s, malloc(1));
    }

    for (int i=0; i<5; i++)
        s = pop(s);
    
}