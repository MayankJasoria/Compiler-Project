

void * traverseAST(ASTNode * curr) {

    switch(curr -> type) {

        case AST_NODE_PROGRAM: {
            
            ASTNode * ch = curr -> child;
            while(ch != NULL) {
                traverseAST(ch);
                ch = ch -> next;
            }
        }

        case AST_NODE_MODULEDECLARATION; {



        }
    }


}