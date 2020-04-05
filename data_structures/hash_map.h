/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "linked_list.h"
#include "../utils/utils.h"
#define HASH_MAP_SIZE 293

typedef struct {
	void* key;
	void* data;
} hashElement;

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
HashTable insertToTable(HashTable table, void* key, void* data, int (*hash)(void*));

/**
 * Informs whether a given entry (by key) is present in the table or not
 * @param key	The key for identifying the entry
 * 
 * @return TRUE (== 1) if the entry is present, FALSE (== 0) otherwise
 */
boolean isPresent(HashTable table, void* key, int (*hash)(void*));

/**
 * Returns the data associated with the given key from the table
 * @param key	The key for identifying the entry
 * 
 * @return The requested data, if it is present. Otherwise NULL
 */
void* getDataFromTable(HashTable table, void* key, int (*hash)(void*));

/**
 * Removes an entry (by key) from the table, if it exists
 * @param key	The key for identifying the entry
 * 
 * @return updated Hash Table
 */
HashTable removeFromTable(HashTable table, void* key, int (*hash)(void*));

/**
 * Computes a hash value for a given number
 * @param val	The number whose hash value is to be computed
 * 
 * @return hash value for the given string
 */
int numberHash(void* y);

/**
 * Computes a hash value for a given string
 * @param str	The string whose hash value is to be computed
 * 
 * @return hash value for the given string
 */
int stringHash(void* y);



#endif