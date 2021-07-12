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
 * @param table The hash table into which data should be inserted
 * @param key	The key to be used as identifier of the data
 * @param data 	The data to be stored in the table
 * @param hash  The hash function to use
 * 
 * @return updated Hash Table
 */
HashTable insertToTable(HashTable table, void* key, void* data, int (*hash)(void*));

/**
 * Informs whether a given entry (by key) is present in the table or not
 * @param table The hash table into which data should be inserted
 * @param key	The key for identifying the entry
 * @param hash  The hash function to use
 * 
 * @return TRUE (== 1) if the entry is present, FALSE (== 0) otherwise
 */
boolean isPresent(HashTable table, void* key, int (*hash)(void*));

/**
 * Returns the data associated with the given key from the table
 * @param table The hash table into which data should be inserted
 * @param key	The key for identifying the entry
 * @param hash  The hash function to use
 * 
 * @return The requested data, if it is present. Otherwise NULL
 */
void* getDataFromTable(HashTable table, void* key, int (*hash)(void*));

/**
 * Removes an entry (by key) from the table, if it exists
 * @param table The hash table into which data should be inserted
 * @param key	The key for identifying the entry
 * @param hash  The hash function to use
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
int numberHash(void* val);

/**
 * Computes a hash value for a given string
 * @param str	The string whose hash value is to be computed
 * 
 * @return hash value for the given string
 */
int stringHash(void* str);

/**
 * Prints the 'valid entries' of the hash table
 * @param fp			The FILE pointer into which table should be printed
 * @param hashtable     The hash table to be printed
 * @param printelement  The function specifying how each 
 *                      hashed element should be printed
 */
void printHashTable(HashTable hashtable, void (*printElement)(void*));

#endif