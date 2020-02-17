/* A note about about compiling:
   It seems that the math library is not automatically being linked by gcc version 7.4.0.
   If that is the case, use -lm to link math library explicitly
   Example: gcc hash_table.c -lm
            ./a.out
*/   
#include <stdio.h>
#include <math.h>
#include <string.h>

#define HASH_TABLE_SIZE 1000

/* Hash function. Simply adds the length and ascii value of each character in the string. */

static int hash(const char* s) {
    long hash = 0;
    const int len = strlen(s);
    hash += len;
    for (int i = 0; i < len; i++) {
        hash += (long) s[i];
        hash = hash % HASH_TABLE_SIZE;
    }
    return (int)hash;
}

unsigned char hash_table[HASH_TABLE_SIZE];

void hash_table_test(const char* s) {
    printf("Testing for keyword '%s': ", s);
    if (hash_table[hash(s)] == 1)
        printf("'%s' is a keyword\n", s);
    else 
        printf("'%s' is NOT a keyword\n", s);
}

void main() {

    char* keywords[] = {
        "INTEGER",
        "REAL",
        "BOOLEAN",
        "OF",
        "ARRAY",
        "START",
        "END",
        "DECLARE",
        "MODULE",
        "DRIVER",
        "PROGRAM",
        "GET_VALUE",
        "PRINT",
        "USE",
        "WITH",
        "PARAMETERS",
        "TRUE",
        "FALSE",
        "TAKES",
        "INPUT",
        "AND",
        "OR",
        "FOR",
        "IN",
        "SWITCH",
        "CASE",
        "BREAK",
        "DEFAULT",
        "WHILE"
    };

    int len = sizeof(keywords)/sizeof(keywords[0]);

    for (int i=0; i<HASH_TABLE_SIZE; i++) {
        hash_table[i] = 0;
    }

    for (int i=0; i<len; i++) {
        int hash_val = hash(keywords[i]);
        if (hash_table[hash_val] ==0)
            hash_table[hash_val] = 1;
        else 
            printf("WARNING: collision at %d in hash table for keyword %s\n", hash_val, keywords[i]);    
    }

    printf("Hash table populated with keywords\nTests (assuming keywords are case-sensitive:): \n");

    hash_table_test("SWITCH");
    hash_table_test("switch");
    hash_table_test("HAHALOL");
    hash_table_test("LOLVANDANA");
    hash_table_test("DECLARE");
    hash_table_test("WHYSOSERIOUS");
}