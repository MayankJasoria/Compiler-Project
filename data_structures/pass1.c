/* Mayank's Task
Include the files
*/


void* traverseChildren(ASTNode* head) {
    ASTNode* ch = head;
    while(ch != NULL) {
        traverseAST(ch);
        ch = ch -> next;
    }
}

void * traverseAST(ASTNode * curr) {

    switch(curr -> type) {

        case AST_NODE_PROGRAM: {
            
            ASTNode * ch = curr -> child;
            /* Replace loop by traverseChildren(ch) ? */

            while(ch != NULL) {
                traverseAST(ch);
                ch = ch -> next;
            }
        }

        case AST_NODE_MODULEDECLARATION: {

            ASTNode * ch = curr -> child;

            /* Use traverseChildren(ch)? */
            while(ch != NULL) {
                
                traverseAST(ch);
                ch = ch -> next;
            }
        }

        case AST_NODE_MODULELIST: {
            
            ASTNode * ch = curr -> child;

            /* Use traverseChildren(ch)? */
            while(ch != NULL) {
                
                traverseAST(ch);
                ch = ch -> next;
            }
        }

        case AST_NODE_MODULE: {
             
            ASTNode * ch = curr -> child;

            /* Use traverseChildren(ch)? */
            while(ch != NULL) {
                
                traverseAST(ch);
                ch = ch -> next;
            }
        }


        case AST_NODE_INPUTLIST:
        case AST_NODE_OUTPUTLIST:
        case AST_NODE_ARRAY:
        case AST_NODE_RANGEARRAYS:
        case AST_NODE_STATEMENT:
        case AST_NODE_IO:
        case AST_NODE_SIMPLESTMT:
        case AST_NODE_ASSIGN:
        case AST_NODE_WHICHSTMT:
        case AST_NODE_MODULEREUSE:
        case AST_NODE_IDLIST:
        case AST_NODE_EXPR:
        case AST_NODE_AOBEXPR:
        case AST_NODE_DECLARESTMT:
        case AST_NODE_CONDSTMT:
        case AST_NODE_CASESTMT:
        case AST_NODE_UNARY:
        case AST_NODE_LVALARRSTMT:
        case AST_NODE_ITERSTMT:
        case AST_NODE_FOR:
        case AST_NODE_WHILE:
        case AST_NODE_VARIDNUM:
        case AST_NODE_LEAF: {
            /* 
                For ID: (As in ast.c)
                CASE: 3,7, 
            */
        }
    }


}