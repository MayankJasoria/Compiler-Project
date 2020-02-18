#include<stdlib.h>
#include"linked_list.h"

Node* end;

List insert(int value, position dir) {
    if(head == NULL) {
        head = (List) malloc(sizeof(Node));
        head->value = value;
        head->next = NULL;
        end = head;
        return head;
    }
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    if(dir == BEGIN) {
        newNode->next = head->next;
        head->next = newNode;
    } else if(dir == END) {
        newNode->next = NULL;
        end->next = newNode;
        end = newNode;
    } else {
        perror("Error: Unknown Direction\n");
    }
    return head;
}

List delete(int value) {
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
                }
            } else {
                /* internal element */
                prev->next = curr->next;
            }
            if(prev->next == NULL) {
                /* delete from end of list; update end pointer */
                end = prev;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
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