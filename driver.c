#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utils/utils.h>

#include "lexer.h"
#include "parser.h"

int main() {
    int option;
    char infile[300];
    char outfile[300];
    boolean executed = False;
    do {
        printf("Enter an option\n1: Remove comments from souce code\n2: Print token list from lexer\n3: Check syntactic correctness of source code\n");
        if(executed) {
            printf("4: Check time of execution of code\n");
        }
        printf("0: Exit\n\nEnter your choice");
        scanf("%d", &option);
        switch(option) {
            case 0:
                printf("\nExited\n");
                break;
            case 1:
                printf("\nEnter the path of input file\n");
                scanf("%s", infile);
                removeComments(infile);
        }
    } while(option != 0);
}