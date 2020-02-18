#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum nts {
    PROGRAM,			
    MODULEDECLARATIONS,
    MODULEDECLARATION,	
    OTHERMODULES,			
    DRIVERMODULE,			
    MODULE,			
    RET,				
    INPUT_PLIST,			
    INPUT_PLISTNEW,	
    OUTPUT_PLIST,			
    OUTPUT_PLISTNEW,	
    TYPE,					
    DATATYPE,				
    MODULEDEF,				
    STATEMENTS,			
    STATEMENT,				
    IOSTMT,				
    WHICHID,				
    INDEX,					
    SIMPLESTMT,		
    ASSIGNMENTSTMT,	
    MODULEREUSESTMT,		
    OPTIONAL,				
    IDLIST,				
    IDLISTNEW,				
    EXPRESSION,			
    ARITHORBOOLEXPR,
    ARITHORBOOLEXPRNEW,
    RELOPEXPR,
    RELOPEXPRNEW,
    ARITHMETICEXPR,	
    ARITHMETICEXPRNEW,		
    TERM,					
    TERMNEW,				
    FACTOR,			
    VARNEW,				
    VAR,				
    PM,				
    MD,				
    LOGICALOP,				
    RELATIONALOP,			
    DECLARESTMT,			
    CONDIONALSTMT,			
    CASESTMTS,				
    CASESTMTSNEW,			
    VALUE,					
    DEFAULT,			
    ITERATIVESTMT,			
    RANGE				
} nts;

struct entry {
    nts term;
    char *val;
};

struct entry map[] = {
    PROGRAM,            "program",		
    MODULEDECLARATIONS, "moduleDeclarations",
    MODULEDECLARATION,	"moduleDeclaration",
    OTHERMODULES,       "otherModules",		
    DRIVERMODULE,       "driverModule",		
    MODULE,             "module",	
    RET,                "ret",				
    INPUT_PLIST,        "input_plist",			
    INPUT_PLISTNEW,     "input_plistNew",
    OUTPUT_PLIST,		"output_plist",	
    OUTPUT_PLISTNEW,	"output_plistNew",
    TYPE,	            "type",				
    DATATYPE,			"dataType",	
    MODULEDEF,			"moduleDef",	
    STATEMENTS,			"statements",
    STATEMENT,			"statement",	
    IOSTMT,				"ioStmt",
    WHICHID,			"whichId",	
    INDEX,				"index",	
    SIMPLESTMT,		    "simpleStmt",
    ASSIGNMENTSTMT,	    "assignmentStmt",
    MODULEREUSESTMT,	"moduleReuseStmt",	
    OPTIONAL,			"optional",	
    IDLIST,				"idList",
    IDLISTNEW,			"idListNew",	
    EXPRESSION,			"expression",
    ARITHORBOOLEXPR,    "arithOrBoolExpr",
    ARITHORBOOLEXPRNEW, "arithOrBoolExprNew",
    RELOPEXPR,          "RelopExpr",
    RELOPEXPRNEW,       "RelopExprNew",
    ARITHMETICEXPR,	    "arithmeticExpr",
    ARITHMETICEXPRNEW,	"arithmeticExprNew",	
    TERM,				"term",	
    TERMNEW,			"termNew",	
    FACTOR,			    "factor",
    VARNEW,				"varNew",
    VAR,				"var",
    PM,				    "pm",
    MD,				    "md",
    LOGICALOP,			"logicalOp",	
    RELATIONALOP,		"relationalOp",	
    DECLARESTMT,		"declareStmt",	
    CONDIONALSTMT,		"condionalStmt",	
    CASESTMTS,			"caseStmts",	
    CASESTMTSNEW,		"caseStmtsNew",	
    VALUE,				"value",	
    DEFAULT,			"default",
    ITERATIVESTMT,		"iterativeStmt",	
    RANGE,				"range"
};

struct symbol {
    union {
        char* token;
        nts non_term;
    };
    /* when set, indicates non-terminal, else a token */
    unsigned tag:1;
    struct symbol* next;
};

/* assumes input string of form "<([a-z]|[A-Z]|[0-9])*>" */
nts lookup_nt(const char* key) {
    
    int i = 0;
    char *name = map[i].val;
    while (name) {
        if (strlen(name) != (strlen(key)-2)) {
            name = map[++i].val;
            continue;
        }
        if (strncmp(name, key+1, strlen(key)-2) == 0)
            return map[i].term;
        name = map[++i].val;
    }
    return 0;
} 

void mov_next(struct symbol** curr) {
    while (*curr && !(((*curr)->tag == 0) && (strcmp((*curr)->token, "|")==0))) {
        *curr = (*curr)->next;
    } 
}

int first_set(struct symbol** table, int index) {
    char *name = map[index].val;
    int term = map[index].term;

    //printf("First set for %s: {", name);
    /* Compute first set for this term */

    struct symbol* next = table[term];

    int glob_e = 0;
    while (next) {

        if (next->tag==0) {
            /* we have a token */
            printf(",%s",next->token);
            if (strcmp(next->token, "E")==0) {
                glob_e = 1;
            }
        } else {
            /* we have a term, recurse into it and find out whether it can be empty */
            int pos_e = 1;
            while (pos_e && next && !((next->tag==0)&&(strcmp(next->token, "|")==0))) {
                if (next->tag==0) {
                    printf(",%s",next->token);
                    pos_e = 0;
                    break;
                } 

                if (next->non_term == term) {
                    pos_e = 0;
                    break;
                }
                pos_e = first_set(table, next->non_term);
                next = next->next;
            }
            if (pos_e) 
                glob_e = 1;
        }

        mov_next(&next);
        if (next)
            next = next->next;
        else break;    
    }

    return glob_e;

}

void follow_set(struct symbol** table, int table_size, int index) {
    char *name = map[index].val;
    int term = map[index].term;

    /* look for wherever this NT is appearing */
    for (int i=0; i<table_size; i++) {
        if (i == term) continue;

        struct symbol* next = table[i];

        while (next) {
            int mov= 0;
            if (next->tag && (next->non_term == term)) {
                /* then follow it ? */
                if (next->next) {
                    next = next->next;
                    if (next->tag) {
                        first_set(table, next->non_term);
                    } else {
                        /* it maybe a | */
                        if (strcmp(next->token, "|")==0) {
                            mov = 1;
                            break;
                        }
                        printf(", %s", next->token);
                    }
                } else {
                    /* nothing follows this, so just follow whatever derives it */
                    first_set(table, i);
                }
            }
            if (mov) {
                mov_next(&next);
            }
            else {
                next = next->next;
            }
        }
    }
}

int main(void) {


    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int num_lines = 0;

    fp = fopen("erplag", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        /* line of length read */
        num_lines++;
    }    

    fseek(fp, 0, SEEK_SET);
    struct symbol **table = malloc(num_lines*(sizeof(struct symbol *)));

    while ((read = getline(&line, &len, fp)) != -1) {
        /* line of length read */

        /* tokenize each line str -> line*/
        char *tok;
        printf ("Splitting string \"%s\" into tokens:\n",line);
        tok = strtok (line," ,.-\t\n");
        int first = 1;
        struct symbol* prev = NULL;
        int rule_ptr = 0;
        while (tok != NULL)
        {
            printf ("%s\n",tok);
            if (first) {
                first = 0;
                rule_ptr = lookup_nt(tok);
                tok = strtok(NULL, " ,.-\t\n");
                tok = strtok(NULL, " ,.-\t\n");
                continue;
            } else {
        
                struct symbol* new_symbol = malloc(sizeof(struct symbol));

                if (tok[0] == '<') {
                    /* it is a NT */
                    new_symbol->tag = 1;
                    new_symbol->non_term = lookup_nt(tok);
                } else {
                    /* it is a term */
                    new_symbol->tag = 0;
                    new_symbol->token = malloc(strlen(tok));
                    strcpy(new_symbol->token, tok);
                }
                
                if (prev == NULL) 
                    table[rule_ptr] = new_symbol;
                else 
                    prev->next = new_symbol;    

                prev = new_symbol;
                tok = strtok(NULL, " ,.-\t\n");
            }
        }
        prev->next = NULL;
    }

    printf(" --- Printing first sets ---");

    /* We have constructed the table, now apply logic of first sets */
    for (int i=0; i< num_lines; i++) {
        printf("First set for <%s>: ", map[i].val);
        first_set(table, map[i].term);
        printf("\n");
    }

    printf(" --- Printing follow sets ---\n");

    for (int i=0; i< num_lines; i++) {
        printf("Follow set for <%s>: ", map[i].val);
        follow_set(table, num_lines, map[i].term);
        printf("\n");
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}