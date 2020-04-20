
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void reportError(int line, char * mess) {

	errorNode * new = (errorNode *)malloc(sizeof(errorNode));
	new -> line = line;
	strcpy(new -> mess, mess);

	errorNode * tmp = errorList;
	errorNode * prev = NULL;
	while(tmp != NULL) {
		if(tmp -> line > line) {
			if(prev == NULL) {
				errorList = new;
				new -> next = tmp;
			}
			else {
				prev -> next = new;
				new -> next = tmp;
			}
			break;
		}
		prev = tmp;
		tmp = tmp -> next;
	}
	if(tmp == NULL) {
		if(prev == NULL) {
			errorList = new;
		}
		else {
			prev -> next = new;
		}
	}
}

void printList() {

	errorNode * tmp = errorList;
	while(tmp != NULL) {
		printf("%s", tmp -> mess);
		tmp = tmp -> next;
	}
}

void destroyError() {

	errorNode * tmp = errorList;
	while(tmp != NULL) {
		errorNode * tmp2 = tmp;
		tmp = tmp -> next;
		free(tmp2);
	}
}
