#include <stdlib.h>
#include <stdio.h>

/**
 * Global File pointer to the file containing generated asm code
 */ 
FILE *fp;

/**
 * Global unique integer for constructs like while, for, switch 
 */ 
int label_num;




/* name:
nextJump;
*/