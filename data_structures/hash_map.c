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
int computeHash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

HashTable insertToTable(HashTable table, void* key, void* data) {
	int idx = computeHash((char*) key); /* check */
	if(table[idx] == NULL) {
		table[idx] = getList();
	}
	hash_element* elem = (hash_element*) malloc(sizeof(hash_element));
	elem->key = key;
	elem->data = data;
	table[idx] = insertToList(table[idx], elem, BEGIN);
	return table;
}