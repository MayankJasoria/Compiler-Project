typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} Node;

typedef Node* List; /* Doubly-linked list */

typedef enum {
    BEGIN,
    END
} position;

extern List head;

/**
 * Inserts 'value' to the start or end of the list,
 * depending on position
 * @param value The value to be inserted
 * @param dir   Either BEGIN or END, defining the place at which
 *              the element should be inserted into the list
 * 
 * @return updated List
 */
List insert(int value, position dir);

/**
 * deletes a value from the list
 * @param value The value to be deleted
 * 
 * @return updated List
 */
List deleteByValue(int value);

/**
 * deletes the given node from the list
 * @param element The element (Node address) to be deleted
 * 
 * @return updated list
 */
List deleteByNode(Node* element);

/**
 * Returns the address of an element in list
 * @param value The value to be found in the list
 * 
 * @return Node address of the value; NULL if not found
 */
Node* find(int value);