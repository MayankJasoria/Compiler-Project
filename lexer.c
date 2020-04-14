/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * keywordList[] = {
		"<empty>",
		"integer",
		"real",
		"boolean",
		"of",
		"array",
		"start",
		"end",
		"declare",
		"module",
		"driver",
		"program",
		"get_value",
		"print",
		"use",
		"with",
		"parameters",
		"true",
		"false",
		"takes",
		"input",
		"returns",
		"AND",
		"OR",
		"for",
		"in",
		"switch",
		"case",
		"break",
		"default",
		"while",
		"\0"
	};

void insertkey (int idx, char * str, int en) {
	keyNode * prev = NULL, * curr = NULL;
	
	/* initializing the new Node to be inserted */
	keyNode * new = (keyNode *)malloc(sizeof(keyNode));
	strcpy(new -> str, str);
	new -> next = NULL;
	new -> id = en;

	curr = keys[idx].head;
	
	if(keys[idx].count == 0) {
		keys[idx].head = new;
		keys[idx].count++;
		return;
	}
	
	while(curr != NULL) {
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = new;
	keys[idx].count++;
}

keyNode * keyLookup(int idx, char * str) {

	keyNode * curr = keys[idx].head;
	while(curr != NULL) {
		if(strcmp(curr -> str, str) == 0)
			break;
		curr = curr -> next;
	}
	return curr;
}

int hash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

void hashTableinit() {
	int i;
	for(i = 0; i < HASH_TABLE_SIZE; i++) 
		hash_table[i] = -1;
	for(i = 1; i <= num_keywords; i++) {
		int key = hash(keywordList[i]);
		insertkey(key, keywordList[i], i);
	}
}

int checkIdentifier(char * str) {
	if(strlen(str) > 20)
		return -1;
	int key = hash(str);
	keyNode * k = keyLookup(key, str);
	if(keyLookup(key, str) == NULL)
		return 0;
	return k -> id;
}

void lexerinit() {
	printf("Lexical Analysis is being initialized\n");
	state = 1;
	num_keywords = sizeof(keywordList)/sizeof(keywordList[0]) - 1;
	// printf("%d\n", num_keywords);
	hashTableinit();
	endofLexer = 0;
	lexeme[0] = '\0';
	streamBuffer[0] = '\0';
	tokenStream_cap = 4;
	line_num = 1;
	buffer_id = 0;
	ntokens = 0;
	tokenStream = (token **)malloc(tokenStream_cap * (sizeof(token *)));
}

/* allocates memory to a new token */
token * makeNewToken(int id) {
	token * t = (token *)malloc(sizeof(token));
	t -> lex = (char *)malloc(30*sizeof(char));
	t -> line_num = line_num;
	t -> id = id;
	strcpy(t -> lex, lexeme);
	int val = -1;
	if(id == 52) {
		val = atoi(lexeme);
		t -> is_float = 0;
		t -> val.val_int = val;
	}
	else if(id == 53) {
		t -> val.val_float = atof(lexeme);
		t -> is_float = 1;
	}
	// (t -> val).val_float = -1;
	if(id != 57) {
		lexeme[0] = '\0';
		ntokens++;
	}
	state = 1;
	return t;
}

errorInst * makeNewError(int line_num, char * lex) {
	errorInst * e = (errorInst *)malloc(sizeof(errorInst));
	e -> lex = lex;
	e -> line_num = line_num;
	return e;
}

/* push back the desired number of characters back onto the input stream */
void retract(int num) {
	int len = strlen(lexeme);
	buffer_id -= num;
	lexeme[len - num] = '\0';
}

void error() {
	errorInst * e = makeNewError(line_num, lexeme);
	// printf(KRED "\nLexical Error: " KNRM "stray " KCYN "'%s'" KNRM " on line " KMAG "%d\n" KNRM, lexeme, line_num);
	printf("Line number (%d): lexical error -- stray '%s'\n\n", line_num, lexeme);
	lexeme[0] = '\0';
	state = 1;
}


void idlengthError() {
	// printf(KRED "Lexical Error: " KCYN "'%s'" KNRM "(max. length of the identifier exceeded) on line " KMAG "%d\n\n" KNRM, lexeme, line_num);
	printf("Line number (%d): lexical error -- maximum length of identifier exceeded for '%s'\n\n", line_num, lexeme);
	lexeme[0] = '\0';
	state = 1;
}

/* converts a sigle character to a string */
void ctoa(char ch) {
	char tmp[2];
	tmp[0] = ch;
	tmp[1] = '\0';
	strcat(lexeme, tmp);
}

token * getNextToken(FILE * fp) {

	/* Check if the fp is valid. Ideally, this check should be performed in parseInputSourceCode(),
		in parser.c, however due to design of the main program (which sometimes uses this function as the entry 
		point), this check had to be kept here) */
	if (!fp) {
		printf("Error: source file could not be opened, exiting...\n");

		/* Exiting right away, since there is no point returning to the main menu */
		exit(0); 
	}

	char ch, nxt;
	token * newtok;
	int flag = 0;
	while(1) {
		if(flag == 1 && state == 1)
			break;
		if((buffer_id == strlen(streamBuffer)) && flag == 0) {
			fp = getStream(fp);
			if(strlen(lexeme) == strlen(streamBuffer)) {
				char tmp[3];
				tmp[2] = '\0';
				tmp[1] = '#';
				tmp[0] = '#';
				strcat(streamBuffer, tmp);
				flag = 1;
			}
		}
		switch(state) { 
			/* To Do : DRIVERDEF, DRIVERENDDEF */
			case 1: 
				ch = streamBuffer[buffer_id];
				if(ch == '+') {
					state = 2;
					strcat(lexeme, "+");
				}
				else if(ch == '-') {
					state = 3;
					strcat(lexeme, "-");
				}
				else if(ch == '/') {
					state = 4;
					strcat(lexeme, "/");
				}
				else if(ch == ';') {
					state = 5;
					strcat(lexeme, ";");
				}
				else if(ch == ',') {
					state = 6;
					strcat(lexeme, ",");
				}
				else if(ch == '[') {
					state = 7;
					strcat(lexeme, "[");
				}
				else if(ch == ']') {
					state = 8;
					strcat(lexeme, "]");
				}
				else if(ch == '(') {
					state = 9;
					strcat(lexeme, "(");
				}
				else if(ch == ')') {
					state = 10;
					strcat(lexeme, ")");
				}
				else if(ch == '=') {
					state = 11;
					strcat(lexeme, "=");
				}
				else if(ch == '!') {
					state = 13;
					strcat(lexeme, "!");
				}
				else if(ch == ':') {
					state = 15;
					strcat(lexeme, ":");
				}
				else if(ch == '.') {
					state = 28;
					strcat(lexeme, ".");
				}
				else if(ch == '<') {
					state = 18;
					strcat(lexeme, "<");
				}
				else if(ch == '>') {
					state = 22;
					strcat(lexeme, ">");
				}
				else if(ch == '\n')
					state = 26;
				else if(ch == ' ' || ch == '\t')
					state = 27;
				else if(ch >= '0' && ch <= '9') {
					state = 30;
					ctoa(ch);
				}
				else if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')) {
					state = 40;
					ctoa(ch);
				}
				else if(ch == '*') {
					state = 42;
					strcat(lexeme, "*");
				}
				else if(ch == '#') {
					flag = 1;
					break;
				}
				else {	
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 2:
				newtok = makeNewToken(31);
				return newtok;
			case 3:
				newtok = makeNewToken(32);
				return newtok;
			case 4:
				newtok = makeNewToken(34);
				return newtok;
			case 5:
				newtok = makeNewToken(45);
				return newtok;
			case 6:
				newtok = makeNewToken(46);
				return newtok;
			case 7:
				newtok = makeNewToken(48);
				return newtok;
			case 8:
				newtok = makeNewToken(49);
				return newtok;
			case 9:
				newtok = makeNewToken(50);
				return newtok;
			case 10:
				newtok = makeNewToken(51);
				return newtok;
			case 11:
				nxt = streamBuffer[buffer_id];
				if(nxt == '=') {
					state = 12;
					strcat(lexeme, "=");
				}
				else {
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 12:
				newtok = makeNewToken(39);
				return newtok;
			case 13:
				nxt = streamBuffer[buffer_id];
				if(nxt == '=') {
					state = 14;
					strcat(lexeme, "=");
				}
				else {
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 14:
				newtok = makeNewToken(40);
				return newtok;
			case 15:
				nxt = streamBuffer[buffer_id];
				if(nxt == '=') {
					state = 16;
					strcat(lexeme, "=");
				}
				else {
					state = 17;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 16:
				newtok = makeNewToken(47);
				return newtok;
			case 17:
				retract(1);
				newtok = makeNewToken(43);
				return newtok;
			case 18:
				nxt = streamBuffer[buffer_id];
				if(nxt == '<') {
					state = 19;
					strcat(lexeme, "<");
				}
				else if(nxt == '=') {
					state = 20;
					strcat(lexeme, "=");
				}
				else {
					state = 21;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 19:
				nxt = streamBuffer[buffer_id];
				if(nxt == '<') {
					state = 49;
					strcat(lexeme, "<");
				}
				else {
					state = 48;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 20:
				newtok = makeNewToken(36);
				return newtok;
			case 21:
				retract(1);
				newtok = makeNewToken(35);
				return newtok;
			case 22:
				nxt = streamBuffer[buffer_id];
				if(nxt == '>') {
					state = 23;
					strcat(lexeme, ">");
				}
				else if(nxt == '=') {
					state = 24;
					strcat(lexeme, "=");
				}
				else {
					state = 25;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 23:
				nxt = streamBuffer[buffer_id];
				if(nxt == '>') {
					state = 51;
					strcat(lexeme, ">");
				}
				else {
					state = 50;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 24:
				newtok = makeNewToken(37);
				return newtok;
			case 25:
				retract(1);
				newtok = makeNewToken(38);
				return newtok;
			case 26:
				line_num++;
				state = 1;
				break;
			case 27:
				state = 1;
				break;
			case 28:
				nxt = streamBuffer[buffer_id];
				if(nxt == '.') {
					state = 29;
					strcat(lexeme, ".");
				}
				else {
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 29:
				newtok = makeNewToken(44);
				return newtok;
			case 30:
				nxt = streamBuffer[buffer_id];
				if(nxt == '.') {
					state = 31;
					strcat(lexeme, ".");
				}
				else if(nxt >= '0' && nxt <= '9') {
					ctoa(nxt);
				}
				else {
					state = 35;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 31:
				nxt = streamBuffer[buffer_id];
				if(nxt == '.') {
					state = 32;
					strcat(lexeme, ".");
				}
				else if(nxt >= '0' && nxt <= '9') {
					state = 33;
					ctoa(nxt);
				}
				else 
				{
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 32:
				retract(2);
				newtok = makeNewToken(52);
				return newtok;
			case 33:
				nxt = streamBuffer[buffer_id];
				if(nxt >= '0' && nxt <= '9') {
					state = 33;
					ctoa(nxt);
				}
				else if(nxt == 'E' || nxt == 'e') {
					state = 36;
					ctoa(nxt);
				}
				else {
					state = 34;
					strcat(lexeme, "nxt");
				}
				buffer_id++;
				break;
			case 34:
				retract(1);
				newtok = makeNewToken(53);
				return newtok;
			case 35:
				retract(1);
				newtok = makeNewToken(52);
				return newtok;
			case 36:
				nxt = streamBuffer[buffer_id];
				if(nxt >= '0' && nxt <= '9') {
					state = 38;
					ctoa(nxt);
				}
				else if(nxt == '+' || nxt == '-') {
					state = 37;
					ctoa(nxt);
				}
				else {
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 37:
				nxt = streamBuffer[buffer_id];
				if(nxt >= '0' && nxt <= '9') {
					state = 38;
					ctoa(nxt);
				}
				else {
					error();
					buffer_id--;
				}
				buffer_id++;
				break;
			case 38:
				nxt = streamBuffer[buffer_id];
				if(nxt >= '0' && nxt <= '9') {
					ctoa(nxt);
				}
				else {
					state = 39;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 39:
				retract(1);
				newtok = makeNewToken(53);
				return newtok;
			case 40:
				nxt = streamBuffer[buffer_id];
				if((nxt >= 'a' && nxt <= 'z')||(nxt >= 'A' && nxt <= 'Z')||(nxt >= '0' && nxt <= '9')||(nxt == '_')) {
					ctoa(nxt);
				}
				else {
					state = 41;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 41:
				retract(1);
				int keyid = checkIdentifier(lexeme);
				if(keyid == -1) {
					idlengthError();
					break;
				}
				else if(keyid == 0)
					newtok = makeNewToken(54);
				else 
					newtok = makeNewToken(keyid);
				return newtok;
			case 42:
				nxt = streamBuffer[buffer_id];
				if(nxt == '*') {
					state = 44;
					lexeme[0] = '\0';
				}
				else {
					state = 43;
					ctoa(nxt);
				}
				buffer_id++;
				break;
			case 43:
				retract(1);
				newtok = makeNewToken(33);
				return newtok;
			case 44:
				nxt = streamBuffer[buffer_id];
				if(nxt == '*')
					state = 46;
				else if(nxt == '\n')
					state = 45;
				buffer_id++;
				break;
			case 45:
				line_num++;
				nxt = streamBuffer[buffer_id];
				if(nxt == '*') 
					state = 46;
				else if(nxt != '\n')
					state = 44; 
				buffer_id++;
				break;
			case 46:
				nxt = streamBuffer[buffer_id];
				if(nxt == '*')
					state = 47;
				else if(nxt == '\n')
					state = 45;
				else
					state = 44;
				buffer_id++;
				break;
			case 47:
				state = 1;
				lexeme[0] = '\0';
				break;
			case 48:
				retract(1);
				newtok = makeNewToken(41);
				return newtok;
			case 49:
				newtok = makeNewToken(55);
				return newtok;
			case 50:
				retract(1);
				newtok = makeNewToken(42);
				return newtok;
			case 51:
				newtok = makeNewToken(56);
				return newtok;
		}
	}
	token * tok = makeNewToken(57);
	return tok;
}

FILE * getStream(FILE * fp) {

	/* read about fread() from : http://www.cplusplus.com/reference/cstdio/fread/ */
	char tmpBuffer[2*chunk_size];
	size_t bytes_read = fread (tmpBuffer, sizeof(char), chunk_size, fp);
	// printf("Loaded a block from the source code file of size: %zu bytes\n", bytes_read);f
	streamBuffer[0] = '\0';
	strcpy(streamBuffer, lexeme);
	tmpBuffer[bytes_read] = '\0';
	buffer_id = strlen(lexeme);
	if(bytes_read > 0)
		strcat(streamBuffer, tmpBuffer);
	return fp;
}

void removeComments(char *testcaseFile) {
	FILE * test = fopen(testcaseFile, "r");

	/* Check if the fp is valid. Ideally, this check should be performed in parseInputSourceCode(),
		in parser.c, however due to design of the main program (which sometimes uses this function as the entry 
		point), this check had to be kept here) */
	if (!test) {
		printf("Error: source file '%s' could not be opened, exiting...\n", testcaseFile);

		/* Exiting right away, since there is no point returning to the main menu */
		exit(0); 
	}
	

	int lineno = 1;
	char ch;
	int commentOn = 0;
	int end1 = 0;
	int start1 = 0;
	int linePrinted = 0;
	while((ch = fgetc(test)) != EOF) {
		if(!linePrinted) {
			printf("%d  ", lineno);
			linePrinted = true;
		}
		if(commentOn) {
			if(ch == '\n') {
				putchar(ch);
				// putc(ch, clean);
				lineno++;
				linePrinted = False;
			}
			else if(ch == '*' && end1) {
				end1 = 0;
				commentOn = 0;
			} 
			else if(ch != '*' && end1) {
				end1 = 0;
			}
			else if(ch == '*')
				end1 = 1;
		}
		else {
			if(ch == '*' && start1) {
				start1 = 0;
				commentOn = 1;
			}
			else if(ch == '*') {
				start1 = 1;
			}
			else if(ch != '*' && start1) {
				putchar('*');
				putchar(ch);
				start1 = 0;
			}
			else {
				putchar(ch);
				if(ch == '\n') {
					lineno++;
					linePrinted = False;
				}
			}
		}
	}
	fclose(test);
}