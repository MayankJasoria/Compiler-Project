
#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char * keywordList[] = {
		"<empty>",
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


int hash(const char* s) {
	long hash = 0;
	const int len = strlen(s);
	hash += len;
	int i;
	for (i = 0; i < len; i++) {
		hash += (long) s[i];
		hash = hash % HASH_TABLE_SIZE;
	}
	return (int)hash;
}

void hashTableinit() {
	int i;
	for(i = 0; i < HASH_TABLE_SIZE; i++)
		hash_table[i] = -1;
	for(i = 1; i <= num_keywords; i++) {
		int key = hash(keywordList[i]);
		hash_table[key] = i;
	}
}

int checkIdentifier(char * str) {
	if(strlen(str) > 20)
		return -1;
	int key = hash(str);
	if(hash_table[key] == -1)
		return 0;
	if(strcmp(keywordList[key], str))
		return 0;
	return hash_table[key];
}

void lexerinit() {
	state = 1;
	num_keywords = 29;
	hashTableinit();
	endofLexer = 0;
	lexeme[0] = '\0';
	streamBuffer[0] = '\0';
	chunk_size = 30;
	/* 
		To DO:
		chunk_size;
		extern's;
	*/
}

/* allocates memory to a new token */
token * makeNewToken(int id) {
	token * t = (token *)malloc(sizeof(token));
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
		val = atof(lexeme);
		t -> is_float = 1;
		t -> val.val_float = val;
	}
	t -> val.val_float = -1;
	lexeme[0] = '\0';
	return t;
}

errorInst * makeNewError(int line_num, char * lex) {
	errorInst * e = (errorInst *)malloc(sizeof(errorInst));
	e -> lex = lex;
	e -> line_num = line_num;
	return e;
}

// /* check if it is a valid id/ keyword */
// int checkIdentifier() {
// 	if(strlen(lexeme) > 20)
// 		return -1;
// 	return isKeyword(lexeme);
// }

/* push back the desired number of characters back onto the input stream */
void retract(int num) {
	int len = strlen(lexeme);
	buffer_id -= num;
	lexeme[len - num] = '\0';
}

void error() {
	errorInst * e = makeNewError(line_num, lexeme);
	/* To do: should we store errors or just print? */
	printf("Lexical Error || %s on line %d\n", lexeme, line_num);
	lexeme[0] = '\0';
	state = 1;
}


void idlengthError() {
	printf("Lexical Error || %s (length of the identifier exceeded) on line %d\n", lexeme, line_num);
	lexeme[0] = '\0';
	state = 1;
}

/* converts a sigle character to a string */
char * ctoa(char ch) {
	char * tmp = (char *)malloc(2*sizeof(char));
	tmp[0] = ch;
	tmp[1] = '\0';
	return tmp;
}

token * getNextToken() {
	char ch, nxt;
	token * newtok;
	while(1) {
		if(buffer_id == strlen(streamBuffer) || streamBuffer[buffer_id] == 4)
			break;
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
					strcat(lexeme, ctoa(ch));
				}
				else if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')) {
					state = 40;
					strcat(lexeme, ctoa(ch));
				}
				else if(ch == '*') {
					state = 42;
					strcat(lexeme, "*");
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
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
				}
				buffer_id++;
				break;
			case 19:
				newtok = makeNewToken(41);
				return newtok;
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
					strcat(lexeme, ctoa(nxt));
				}
				buffer_id++;
				break;
			case 23:
				newtok = makeNewToken(42);
				return newtok;
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
					strcat(lexeme, ctoa(nxt));
				}
				else {
					state = 35;
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
				}
				else if(nxt == 'E' || nxt == 'e') {
					state = 36;
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
				}
				else if(nxt == '+' || nxt == '-') {
					state = 37;
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
				}
				else {
					state = 39;
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
				}
				else {
					state = 41;
					strcat(lexeme, ctoa(nxt));
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
					strcat(lexeme, ctoa(nxt));
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
				if(nxt != '\n')
					state = 44; 
				// To DO: what if we reach end of chunk here.
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
		}
	}
	token * tok = makeNewToken(-1);
	return tok;
}

FILE * getStream(FILE * fp) {

	/* read about fread() from : http://www.cplusplus.com/reference/cstdio/fread/ */
	char tmpBuffer[50];
	size_t bytes_read = fread (tmpBuffer, sizeof(char), chunk_size, fp);
	strcpy(streamBuffer, lexeme);
	buffer_id = strlen(lexeme);
	if(bytes_read > 0)
		strcat(streamBuffer, tmpBuffer);
	else if(bytes_read == 0)
		strcat(streamBuffer, ctoa(4));
	/* Since EOF is not a character, concatinating a char(4), so that any transitions which have 'others' do their transition */
	if(strlen(streamBuffer) <= 1) {
		endofLexer = 1;
		return fp;
	}

	while(1) {
		state = 1;
		lexeme[0] = '\0';
		token * tok = getNextToken();
		if(tok -> id == -1)
			break;
		else {
			if(ntokens >= tokenStream_cap) {
				realloc(tokenStream, 2*tokenStream_cap);
				tokenStream_cap *= 2;
			}
			tokenStream[ntokens] = tok;
			ntokens++;
		}
	}
	return fp;
}