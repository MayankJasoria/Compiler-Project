/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_map.h"
#include "../utils/utils.h"

boolean initialized = False;

HashTable getHashTable() {
	/* Creating a Hash Table */
	HashTable table = (HashTable) malloc(sizeof(List)*HASH_TABLE_SIZE);
	for(int i = 0; i < HASH_TABLE_SIZE; i++) {
		/* Initializing all hash cells to NULL */
		table[i] = NULL;
	}
	return table;
}

Node* checkKeyInList(HashTable table, void* key, int idx) {
	/* Iterate through the list, checking for key */
	Node* curr = table[idx]->head;
	while(curr != NULL) {
		if(strcmp((char*) key, (char*)((hashElement*) curr->data)->key) == 0) {
			/* key found */
			break;
		}
		curr = curr->next;
	}
	return curr;
}


HashTable insertToTable(HashTable table, void* key, void* data, int (*hash)(void *)) {
	int idx = hash(key);
	// int idx = computeHash((char*) key);
	if(table[idx] == NULL) {
		/* Create a new List */
		table[idx] = getList();
	}

	/* Create a new entry for hash table */
	hashElement* elem = (hashElement*) malloc(sizeof(hashElement));
	elem->key = key;
	elem->data = data;

	/* Insert the entry to the table */
	table[idx] = insertToList(table[idx], elem, FRONT);
	return table;
}

boolean isPresent(HashTable table, void* key, int (*hash)(void *)) {
	int idx = hash(key);
	// int idx = computeHash((char*) key);
	if(table[idx] == NULL) {
		return False;
	}

	if(checkKeyInList(table, key, idx) != NULL) {
		return True;
	}

	/* key not found */
	return False;
}

void* getDataFromTable(HashTable table, void* key, int (*hash)(void *)) {
	int idx = hash(key);
	// int idx = computeHash((char*) key);
	if(table[idx] == NULL) {
		return False;
	}
	
	/* Find the node containing the {key, data} */
	Node* hashNode = checkKeyInList(table, key, idx);

	if(hashNode != NULL) {
		return hashNode->data;
	}

	/* key not found */
	return NULL;
}

HashTable removeFromTable(HashTable table, void* key, int (*hash)(void *)) {
	if(table == NULL) {
		fprintf(stderr, "The provided hash table is undefined\n");
		return table;
	}
	int idx = hash(key);
	// int idx = computeHash((char*) key);
	if(table[idx] != NULL) {
		/* Some key(s) present in this index, search for required key */
		Node* remNode = checkKeyInList(table, key, idx);
		if(remNode != NULL) {
			/* key found, delete it*/
			table[idx] = deleteByNode(table[idx], remNode);
		}
	}

	return table;
}

/**
 * Credits: djb2 hash function from Dan Bernstein -> http://www.cse.yorku.ca/~oz/hash.html
 */
int stringHash(const char *str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

/**
 * Credits: Answer by Thomal Mueller on https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
 */
int numberHash(long long int x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}