#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

boolean initialized = FALSE;

HashTable getHashTable() {
	/* Creating a Hash Table */
	HashTable table = (HashTable) malloc(sizeof(List)*HASH_TABLE_SIZE);
	for(int i = 0; i < HASH_TABLE_SIZE; i++) {
		/* Initializing all hash cells to NULL */
		table[i] = NULL;
	}
	return table;
}


/**
 * Computes a hash value for a given input
 * @param str	The string whose hash value is to be computed
 * 
 * @return hash value for the given string
 */
int computeHash(const char *str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

HashTable insertToTable(HashTable table, void* key, void* data) {
	int idx = computeHash((char*) key); /* check */
	if(table[idx] == NULL) {
		/* Create a new List */
		table[idx] = getList();
	}

	/* Create a new entry for hash table */
	hashElement* elem = (hashElement*) malloc(sizeof(hashElement));
	elem->key = key;
	elem->data = data;

	/* Insert the entry to the table */
	table[idx] = insertToList(table[idx], elem, BEGIN);
	return table;
}

boolean isPresent(HashTable table, void* key) {
	int idx = computeHash((char*) key);
	if(table[idx] == NULL) {
		return FALSE;
	}

	if(checkKeyInList(table, key, idx) != NULL) {
		return TRUE;
	}

	/* key not found */
	return FALSE;
}

void* getDataFromTable(HashTable table, void* key) {
	int idx = computeHash((char*) key);
	if(table[idx] == NULL) {
		return FALSE;
	}
	
	/* Find the node containing the {key, data} */
	Node* hashNode = checkKeyInList(table, key, idx);

	if(hashNode != NULL) {
		return hashNode->data;
	}

	/* key not found */
	return NULL;
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

HashTable removeFromTable(HashTable table, void* key) {
	if(table == NULL) {
		fprintf(stderr, "The provided hash table is undefined\n");
		return table;
	} 
	int idx = computeHash((char*) key);
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