#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "data_structures/stack.h"
#include "data_structures/hash_map.h"

void printList(List ll) {
	Node* curr = ll->head;
	while(curr != NULL) {
		printf("[ %d ] --> ", *((int*)(curr->data)));
		curr = curr->next;
	}
	printf("NULL\n");
}

void printListReverse(List ll) {
	Node* curr = ll->end;
	printf("NULL");
	while(curr != NULL) {
		printf(" <-- [%d]", *((int*)curr->data));
		curr = curr->prev;
	}
	printf("\n");
}

void hash_table_test(HashTable hashtable, char* key) {
	if (isPresent(hashtable, key, stringHash)) {
		printf("%s is a keyword\n", (char *)key);
	} else {
		printf("%s is not a keyword\n", (char *)key);
	}
}

int main() {
	lexerinit();
	FILE * fp = fopen("prog.eg", "r");
	if(fp == NULL) {
		printf("Error opening file\n");
		return 0;
	}
	while(endofLexer == 0) {
		fp = getStream(fp);
	}
	//printf("%d\n", hash("driver"));
	//printf("%d\n", hash_table[hash("driver")]);
	int i;
	for(i = 0; i < ntokens; i++)
		printf("Token Sequence: %d Token id:%d Token Lexeme: %s\n", i + 1, tokenStream[i] -> id, tokenStream[i] -> lex);
	printf("Total number of token generated: %d\n", ntokens);
	removeComments("prog.eg", "clean.eg");

	// Testing Linked List
	// List ll = getList();
	// srand(time(0));
	// for(int i = 0, j = 0; i < 10; i++, j = j^1) {
	// 	int *ins = malloc(sizeof(int));
	// 	*ins = rand();
	// 	printf("Inserted %d\n", *ins);
	// 	ll = insertToList(ll, ins, j);
	// }

	// printListReverse(ll);

	// // delete third element
	// ll = deleteByNode(ll, ll->head->next->next);

	// while (ll->head) {
	// 	ll = deleteByNode(ll, ll->head);
	// 	printListReverse(ll);
	// }

	// printListReverse(ll);

	// // delete head
	// ll = deleteByNode(ll, ll->head);

	// printListReverse(ll);

	// // delete tail
	// ll = deleteByNode(ll, ll->end);

	// printListReverse(ll);

	// testing stack
	// Stack st = getStack();
	// srand(time(0));
	// for(int i = 0; i < 10; i++) {
	// 	int* val = (int*) malloc(sizeof(int));
	// 	*val = rand();
	// 	printf("pushed %d\n", *val);
	// 	push(st, val);
	// }

	// // popping 3 elements
	// for(int i = 0; i < 3; i++) {
	// 	printf("popped :%d\n", *((int*)top(st)));
	// 	st = pop(st);
	// }

	// printf("Top: %d\n", *((int*)top(st)));

	// popMany(st, 4);

	// printf("new Top: %d\n", *((int*)top(st)));

	// popMany(st, 39);

	HashTable hashtable = getHashTable();

	// srand(time(0));

	// for (int i=0; i < 34567; i++) {
	// 	int *key = malloc(sizeof(int));
	// 	*key = rand();
	// 	hashtable = insertToTable(hashtable, key, key, numberHash);
	// 	//free(key);
	// }

	srand(time(0));

	for (int i=0; i < 32; i++) {
		char* key = malloc(strlen(keywordList[i]));
		strcpy(key, keywordList[i]);
		int *data = malloc(sizeof(int));
		*data = rand();
		hashtable = insertToTable(hashtable, key, data, stringHash);
	}

	// for (int i=0; i<32; i++) {
	// 	printf("")
	// }

	hash_table_test(hashtable, "hey");
	hash_table_test(hashtable, "delete");
	hash_table_test(hashtable, "module");
	hash_table_test(hashtable, "print");
	hash_table_test(hashtable, "use");
	hash_table_test(hashtable, "why");

}