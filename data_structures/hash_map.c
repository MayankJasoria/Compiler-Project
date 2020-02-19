#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

boolean initialized = FALSE;

/**
 * Initializes the hash table for first time use
 * (May overwrite a hash table with memory leaks
 * if used on an existing hash table)
 * @return A newly initialized hash table
 */


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

HashTable insertToTable(void* key, void* data) {
	int idx = computeHash((char*) key);
}