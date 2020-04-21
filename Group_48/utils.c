/*  GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P */
	
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void reportError(int line, char * mess) {

	semanticallyCorrect = False;
	errorNode * new = (errorNode *)malloc(sizeof(errorNode));
	new -> line = line;
	strcpy(new -> message, mess);

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
			new -> next = NULL;
		}
		else {
			prev -> next = new;
			new -> next = NULL;
		}
	}
}

void printErrorList() {

	errorNode * tmp = errorList;
	while(tmp != NULL) {
		printf("%s", tmp -> message);
		tmp = tmp -> next;
	}
}

void destroyError() {
	semanticallyCorrect = True;
	errorNode * tmp = errorList;
	while(tmp != NULL) {
		errorNode * tmp2 = tmp;
		tmp = tmp -> next;
		free(tmp2);
	}
	errorList = NULL;
}
