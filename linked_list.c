#include<stdlib.h>
#include"linked_list.h"

Node* end;

List insert(int value, position dir) {
    if(head == NULL) {
        /* First element of list */
        head = (List) malloc(sizeof(Node));
        head->value = value;
        head->next = NULL;
        head->prev = NULL;
        end = head;
        return head;
    }
    /* Defining new node to be inserted */
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    if(dir == BEGIN) {
        /* Insert at beginning of list */
        newNode->next = head;
        newNode->prev = NULL;
        head->prev = newNode;
        head = newNode;
    } else if(dir == END) {
        /* Inserting at end of list */
        newNode->next = NULL;
        end->next = newNode;
        newNode->prev = end;
        end = newNode;
    } else {
        /* Some unknown type of position has been entered */
        perror("Error: Unknown Direction\n");
    }
    return head;
}

List deleteByValue(int value) {
    if(head == NULL) {
        perror("List is empty\n");
        return head;
    }
    Node* curr = head;
    Node* prev = NULL;
    while(curr != NULL) {
        if(curr->value == value) {
            /* this is the node to be deleted */
            if(prev == NULL) {
                /* First element */
                head = curr->next;
                if(head == NULL) {
                    /* only element of the list; update end pointer */
                    end = NULL;
                } else {
                    head->prev = NULL;
                }
            } else {
                /* internal element */
                prev->next = curr->next;
                if(prev->next == NULL) {
                    /* delete from end of list; update end pointer */
                    end = prev;
                } else {
                    prev->next->prev = curr->prev;
                }
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

List deleteByNode(Node* element) {
    if(element == NULL) {
        perror("Element does not exist\n");
        return head;
    }
    if(head == NULL) {
        perror("List is empty\n");
        return head;
    }
    if(element->prev != NULL) {
        /* first element */
        head = element->next;
        if(head == NULL) {
            /* List had only one element */
            end = NULL;
        } else {
            head->prev = NULL;
        }
    } else {
        element->prev->next = element->next;
        if(element->next == NULL) {
            /* Deleting last element */
            end = element->prev;
        } else {
            element->next->prev = element->prev;
        }
    }
    free(element);
    return head;
}

Node* find(int value) {
    Node* curr = head;
    while(curr != NULL) {
        if(curr->value == value) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}