/**
 * File to check functioning of parser components
 */

#include "parser.h"

char * nonterminals[] = { 
        "program",
        "moduleDeclarations",
        "moduleDeclaration",
        "otherModules",
        "driverModule",
        "module",
        "ret",
        "input_plist",
        "input_plistNew",
        "output_plist",
        "output_plistNew",
        "type",
        "dataType",
        "moduleDef",
        "statements",
        "statement",
        "ioStmt",
        "whichId",
        "index",
        "simpleStmt",
        "assignmentStmt",
        "modulereuseStmt",
        "optional",
        "idList",
        "idListNew",
        "expression",
        "arithOrBoolExpr",
        "arithOrBoolExprNew",
        "relopExpr",
        "relopExprNew",
        "arithmeticExpr",   
        "arithmeticExprNew",
        "term",
        "termNew",
        "factor",
        "var",
        "pm",
        "md",
        "logicalOp",
        "relationalOp",
        "declareStmt",
        "condionalStmt",
        "caseStmts",
        "caseStmtsNew",
        "value",
        "default",
        "iterativeStmt",
        "range"
    };

char * terminals[] = {
        "EMPTY",
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
        "RETURNS",
        "AND",
        "OR",
        "FOR",
        "IN",
        "SWITCH",
        "CASE",
        "BREAK",
        "DEFAULT",
        "WHILE",
        "PLUS",
        "MINUS",
        "MUL",
        "DIV",
        "LT",
        "LE",
        "GE",
        "GT",
        "EQ",
        "NE",
        "DEF",
        "ENDDEF",
        "COLON",
        "RANGEOP",
        "SEMICOL",
        "COMMA",
        "ASSIGNOP",
        "SQBO",
        "SQBC",
        "BO",
        "BC",
        "NUM",
        "RNUM",
        "ID",
        "DRIVERDEF",
        "DRIVERENDDEF",
        "DOLLAR"
    };


void printBinary(unsigned long long int n) {
    unsigned long long int j;
    for(j = 1ull << ((sizeof(unsigned long long int) * 8) - 1); j > 0; j /= 2) {
        ((n&j) > 0) ? printf("1") : printf("0");
    }
}

int main() {
    parserInit("grammar.erp");

    // printing grammar rules [array of linked_lists]
    // printf("****** Grmmar Rules ******\n");
    int i;
    // printf("%d %d\n", hash("MINUS"), hash("iterativeStmt"));
    for(i = 0; i < 100; i++) {
        printf("%s :", nonterminals[G[i].left]);
        rhsNode* curr = G[i].head;
        while(curr != NULL) {
            // printf("{tag: %d, ", curr->tag);
            if(curr->tag == T) {
                printf(" %s", terminals[curr->sym.T]);
            } else {
                printf(" %s", nonterminals[curr->sym.NT]);
            }
            curr = curr->next;
        }
        printf("\n");
    }

    // printf("\n****** First and Follow Sets ******\n");
    // for(i = 0; i < NUM_NONTERM + 2; i++) {
    //     printBinary(first[i]);
    //     printf("  |  ");
    //     printBinary(follow[i]);
    // }
}