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
    int i, j;
    // printf("%d %d\n", hash("MINUS"), hash("iterativeStmt"));
    for(i = 0; i < num_rules; i++) {
        printf("%s :", nonterminals[G[i].left]);
        rhsNode* curr = G[i].head;
        while(curr != NULL) {
            // printf("{tag: %d, ", curr->tag);
            if(curr->tag == T) {
                printf(" %s", terminals[curr->sym.T]);
            } else {
                printf(" %s", nonterminals[curr->sym.NT]);
            }
            curr = curr->next;
        }
        printf("\n");
    }

    printf("\n****** First Sets ******\n");
    for(i = 0; i < NUM_NONTERM; i++)
        firstSet(i);
    for(i = 0; i < NUM_NONTERM; i++) {
        printf("%s:    ", nonterminals[i]);
        for(j = 0; j < 58; j ++)
            if(findinSet(first[i], j))
                printf("%s ", terminals[j]);
        printf("\n");    
    }
    printf("\n****** Follow Sets ******\n");
    for(i = 0; i < NUM_NONTERM; i++)
        followSet(i);
    for(i = 0; i < NUM_NONTERM; i++) {
        printf("%s:    ", nonterminals[i]);
        for(j = 0; j < 58; j ++)
            if(findinSet(follow[i], j))
                printf("%s ", terminals[j]);
        printf("\n"); 
    }

    ComputeFirstAndFollowSets();
    createParseTable();
    printf("\n ****** Parse Table ******\n");
    for(i = -1; i < NUM_NONTERM; i++) {
        printf("%s,", nonterminals[i]);
        for(j = 1; j < NUM_TERM; j++) {
            if(i == -1) 
                printf("%s,", terminals[j]);
            else
                printf("%d,", parseTable[i][j]);
        }
        printf("\n");
    }

    parseInputSourceCode("prog.eg");
}