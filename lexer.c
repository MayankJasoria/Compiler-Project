
#include "lexer.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* allocates memory to a new token */
token * makeNewToken(int id) {
	token * t = (token *)malloc(sizeof(token));
	token -> line_num = line_num;
	token -> id = id;
	strcpy(token -> lex, lexeme);
	token -> value = -1; 
	return t;
}

/* push back the desired number of characters back onto the input stream */
void retract(int num) {
	int len = strlen(lexeme);
	buffer_id -= num;
	lexeme[len - num] = '\0';
}

token * getNextToken() {
	int state = 1;
	char * lexeme = (char*)malloc(chunk_size*sizeof(char));
	while(1) {
		case 1: 
			char ch = streamBuffer[buffer_id];
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
				char tmp[2];
				tmp[0] = ch;
				tmp[1] = '\0';
				strcat(lexeme, tmp);
			}
			else if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')) {
				state = 40;
				char tmp[2];
				tmp[0] = ch;
				tmp[1] = '\0';
				strcat(lexeme, tmp);
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
			token * newtok = makeNewToken(31);
			return newtok;
		case 3:
			token * newtok = makeNewToken(32);
			return newtok;
		case 4:
			token * newtok = makeNewToken(34);
			return newtok;
		case 5:
			token * newtok = makeNewToken(45);
			return newtok;
		case 6:
			token * newtok = makeNewToken(46);
			return newtok;
		case 7:
			token * newtok = makeNewToken(48);
			return newtok;
		case 8:
			token * newtok = makeNewToken(49);
			return newtok;
		case 9:
			token * newtok = makeNewToken(50);
			return newtok;
		case 10:
			token * newtok = makeNewToken(51);
			return newtok;
		case 11:
			char nxt = streamBuffer[buffer_id];
			if(nxt == '=') {
				state = 12;
				strcat(lexeme, '=');
			}
			else {
				error();
				buffer_id--;
			}
			buffer_id++;
			break;
		case 12:
			token * newtok = makeNewToken(39);
			return newtok;
		case 13:
			char nxt = streamBuffer[buffer_id];
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
			token * newtok = makeNewToken(40);
			return newtok;
		case 15:
			char nxt = streamBuffer[buffer_id];
			if(nxt == '=') {
				state = 16;
				strcat(lexeme, "=");
			}
			else {
				state = 17;
				char tmp[2];
				tmp[0] = nxt;
				tmp[1] = '\0';
				strcat(lexeme, tmp);
			}
			buffer_id++;
			break;
		case 16:
			token * newtok = makeNewToken(47);
			return newtok;
		case 17:
			retract(1);
			token * newtok = makeNewToken(43);
			return newtok;
		case 18:
			char nxt = streamBuffer[buffer_id];
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
				char tmp[2];
				tmp[0] = nxt;
				tmp[1] = '\0';
				strcat(lexeme, tmp);
			}
			buffer_id++;
			break;
		case 19:
			token * newtok = makeNewToken(41);
			return newtok;
		case 20:
			token * newtok = makeNewToken(36);
			return newtok;
		case 21:
			retract(1);
			token * newtok = makeNewToken(35);
			return newtok;
		case 22:
			char nxt = streamBuffer[buffer_id];
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
				char tmp[2];
				tmp[0] = nxt;
				tmp[1] = '\0';
				strcat(lexeme, tmp);
			}
			buffer_id++;
			break;
		case 23:
			token * newtok = makeNewToken(42);
			return newtok;
		case 24:
			token * newtok = makeNewToken(37);
			return newtok;
		case 25:
			retract(1);
			token * newtok = makeNewToken(38);
			return newtok;
		case 26:
			line_num++;
			state = 1;
			break;
		case 27:
			state = 1;
			break;
		case 28:
			char nxt = streamBuffer[buffer_id];
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
			token * newtok = makeNewToken(44);
			return newtok;
	}
}

FILE * getStream(FILE * fp) {

	/* read about fread() from : http://www.cplusplus.com/reference/cstdio/fread/ */
	size_t bytes_read = fread (streamBuffer, sizeof(char), 30, f);
	
	while(1) {
		token * tok = getNextToken();
		if(tok -> id == -1)
			break;
		else {
			if(ntoken >= tokenStream_cap) {
				realloc(tokenStream, 2*tokenStream_cap);
				tokenStream_cap *= 2;
			}
			tokenStream[ntokens] = tok;
			ntokens++;
		}
	}

	return f;
}