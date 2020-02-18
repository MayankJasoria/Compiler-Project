/**
 * File to check functioning of parser components
 */

#include "parser.h"

void printBinary(unsigned long long int n) {
    unsigned long long int j;
    for(j = 1ull << ((sizeof(unsigned long long int) * 8) - 1); j > 0; j /= 2) {
        ((n&j) > 0) ? printf("1") : printf("0");
    }
}

int main() {
    parserInit("grammar.erp");

    // printing grammar rules [array of linked_lists]
    printf("****** Grmmar Rules ******\n");
    int i;
    for(i = 0; i < 100; i++) {
        printf("<%d>\t--> ", G[i].left);
        rhsNode* curr = G[i].head;
        while(curr != NULL) {
            printf("{tag: %d, ", curr->tag);
            if(curr->tag == T) {
                printf("Terminal: %d}", curr->sym.T);
            } else {
                printf("Non-Terminal: <%d>}", curr->sym.NT);
            }
            curr = curr->next;
        }
        printf("\n");
    }

    // printf("\n****** First and Follow Sets ******\n");
    // for(i = 0; i < NUM_NONTERM + 2; i++) {
    //     printBinary(first[i]);
    //     printf("  |  ");
    //     printBinary(follow[i]);
    // }
}