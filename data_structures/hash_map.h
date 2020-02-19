#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "linked_list.h"
#include "../utils/utils.h"
#define HASH_TABLE_SIZE 1013

typedef struct {
	void* key;
	void* data;
} hash_element;

typedef List* HashTable;

/**
 * Creates and returns a new Hash Table
 * @return a new HashTable
 */
HashTable getHashTable(); 

/**
 * Inserts a new {key, data} pair into the hash table
 * @param key	The key to be used as identifier of the data
 * @param data 	The data to be stored in the table
 * 
 * @return updated Hash Table
 */
HashTable insertToTable(HashTable table, void* key, void* data);

/**
 * Informs whether a given entry (by key) is present in the table or not
 * @param key	The key for identifying the entry
 * 
 * @return TRUE (== 1) if the entry is present, FALSE (== 0) otherwise
 */
boolean isPresent(HashTable table, void* key);

/**
 * Returns the data associated with the given key from the table
 * @param key	The key for identifying the entry
 * 
 * @return The requested data, if it is present. Otherwise NULL
 */
void* getDataFromTable(HashTable table, void* key);

/**
 * Removes an entry (by key) from the table, if it exists
 * @param key	The key for identifying the entry
 * 
 * @return updated Hash Table
 */
HashTable removeFromTable(HashTable table, void* key);

#endif