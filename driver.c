#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/utils.h"

#include "lexer.h"
#include "parser.h"

/**
 * Performs lexical analysis and parsing of a given file, and 
 * prints the inorder traversal of the generated parse tree
 * to a given output file
 * @param inputfile     The source code file
 * @param outputfile    The file into which the inorder traversal
 *                      of the parse tree is to be written
 */
void lexAndParse(char* inputfile, char* outputfile) {
	parseInputSourceCode(inputfile);
    printf("\n");
    printParseTree(PT, outputfile);
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        fprintf(stderr, KRED "Expected two arguments, found %d. Terminating\n" KNRM, argc-1);
        exit(0);
    }

    /* initializing lexer and parser */
    lexerinit();
    parserInit("grammar_new.erp");
    ComputeFirstAndFollowSets();
    createParseTable();

    printf(KCYN "**************** IMPLEMENTATION STATUS ****************\n" KNRM);
    printf("1: FIRST and FOLLOW set automated\n");
    printf("2: Both lexical and syntax analyzer modules implemented\n");
    printf("3: Code works on all given test cases\n");
    printf(KCYN "*******************************************************\n" KNRM);

    int option = 0;
    boolean executed = False;
    do {
        printf("Enter an option\n1: Remove comments from souce code\n");
        printf("2: Print token list from lexer\n3: Check syntactic correctness of source code\n4: Check time of execution of code\n");
        printf("0: Exit\n\nEnter your choice:\n");
        scanf("%d", &option);
        switch(option) {
            case 0: {
                printf("\nExited\n");
                break;
			}
            case 1: {
				printf(KGRN "\nModified Program:\n" KNRM);
                removeComments(argv[1]);
				printf("\n");
                break;
			}
            case 2: {
                /* Call lexer getNextToken() */
                FILE * fp = fopen(argv[1], "r");
                int i = 1;
                token * tok;
                printf(KGRN "%-25s%-25s%s\n" KNRM, "line_num", "lexeme", "Token_name");
                while((tok = getNextToken(fp))->id != DOLLAR) {
                    printf("%-25d%-25s%d\n", tok->line_num, tok->lex, tok->id);
                    i++;
                }
                break;
			}
            case 3:
				lexAndParse(argv[1], argv[2]);
                break;
            case 4: {
                clock_t start_time, end_time;
                double total_CPU_time, total_CPU_time_in_seconds;
                start_time = clock();
                // invoke lexer and parser here
				lexAndParse(argv[1], argv[2]);
                end_time = clock();
                total_CPU_time  =  (double) (end_time - start_time);
                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
				printf("The total time taken is " KBLU "%f ticks (= %f sec)\n\n" KNRM, total_CPU_time, total_CPU_time_in_seconds);
                break;
			}
            default: printf(KYEL "Option %d is invalid, please try again\n" KNRM, option);
        }
    } while(option != 0);
}