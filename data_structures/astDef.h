/**
 *  astDef.h: Contains definitions for constructing abstract syntax tree 
 *  Note: 'declarationNode' in our semantic rules documentation has been changed to
 *         'moduleDeclarationsNode' in this code to avoid confusion.
*/

/**
 * nodeType: Identifies the type of node represented by the 
 *           ASTNode. 
 * Naming convention: Construct name in all uppercase letters
 */

typedef enum {
    AST_NODE_PROGRAM,
    AST_NODE_MODULEDECLARATION,
    AST_NODE_MODULELIST,
    AST_NODE_MODULE,
    AST_NODE_INPUTLIST,
    AST_NODE_OUTPUTLIST,
    AST_NODE_DATATYPE,
    AST_NODE_RANGEARRAYS,
    AST_NODE_STATEMENT,
    AST_NODE_SIMPLESTMT,
    AST_NODE_ASSIGN,
    AST_NODE_WHICHSTMT,
    AST_NODE_MODULEREUSE,
    AST_NODE_IDLIST,
    AST_NODE_EXPR,
    AST_NODE_AOBEXPR,
    AST_NODE_DECLARESTMT,
    AST_NODE_CONDSTMT,
    AST_NODE_CASESTMT,
    AST_NODE_UNARY,
    AST_NODE_LVALARRSTMT,
    AST_NODE_ITERSTMT,
    AST_NODE_FOR,
    AST_NODE_WHILE,
    AST_NODE_LEAF
} astNodeType;

typedef enum {
    AST_TYPE_CAT_PRIM,
    AST_TYPE_CAT_ARRAY,
} astDataTypeCat;

typedef enum {
    AST_TYPE_INT,
    AST_TYPE_REAL,
    AST_TYPE_BOOLEAN,
    AST_TYPE_ARRAY
} astDataType;

typedef enum {
    AST_STMT_IO,
    AST_STMT_SIMPLE,
    AST_STMT_DECLARATION,
    AST_STMT_CONDITIONAL,
    AST_STMT_ITERATIVE,
    AST_STMT_ASSIGNMENT,
    AST_STMT_MODULEREUSE,
    AST_STMT_LVALUEID,
    AST_STMT_LVALUEARR
} stmt_type;

typedef enum {
    AST_WHICH_TYPE_LVALID,
    AST_WHICH_TYPE_LVALARR
} whichType;

typedef enum {
    AST_EXPR_AOB,
    AST_EXPR_UNARY  
} expr_type;

typedef enum {
    AST_VAR_TYPE_BOOLCONSTT,
    AST_VAR_TYPE_ID,
    AST_VAR_TYPE_NUM,
    AST_VAR_TYPE_RNUM
} aob_type;

typedef enum {
    AST_ITER_FOR,
    AST_ITER_WHILE
} iter_type;


typedef struct programNode {

    // struct moduleDeclarationNode* dec_head; /* Linkedlist of moduleDeclarationNode */
    // struct moduleListNode* other_mod1_head; /* Linkedlist of moduleListNode */
    // struct moduleListNode* driver_mod;      /* Linkedlist of moduleListNode */
    // struct moduleListNode* other_mod2_head; /* Linkedlist of moduleListNode */
};

typedef struct moduleDeclarationNode {
    // struct leafNode* id_ptr;
    // struct moduleDeclarationNode* next;

    // struct leafNode* id_ptr; access
    struct ASTNode* next; /* Points to next element of type moduleDeclarations */

}; //This is a linked list (C++ equivalent: a vector of pointers)

/* NOTE: These two structures have been collapsed into moduleListNode defined below */

// struct moduleListNode {
//     struct leafNode* id_ptr;
//     struct inputListNode* input_plist_head;
//     struct outputListNode* output_plist_head;
//     struct statementNode* moduleDef_head;
//     struct ASTNode* next;
// };

// struct moduleNode {
//     struct leafNode* id_ptr;
//     struct inputListNode* input_plist_head;
//     struct outputListNode* output_plist_head;
//     struct statementNode* moduleDef_head;
// };


typedef struct moduleListNode {
    /* check note above */
    struct ASTNode* next; /* Points to next element of type moduleListNode */
};


typedef struct inputListNode {
    // struct leafNode* id_ptr;
    // struct leafNode* type_ptr;
    // struct inputListNode* next; /* Points to next element of type inputListNode */
    struct ASTNode* next; /* Points to next element of type inputListNode */
};

typedef struct outputListNode {
    // struct leafNode* id_ptr;
    // struct leafNode* type_ptr;
    // struct outputListNode* next;

    struct ASTNode* next; /* Points to next element of type outputListNode */

};

typedef struct dataTypeNode {
    // struct rangeArraysNode* range_arrays_ptr;
    // struct leafNode* type_ptr;
    // access via ASTNode
    astDataTypeCat type_cat;
};

typedef struct rangeArraysNode {
    // struct leafNode* index1;
    // struct leafNode* index2;
    // access via ASTNode
};

/* TODO: Need to fix statement node */
typedef struct statementNode {
    // union {
    //     struct simpleStmtNode* simpleStmt;
    //     struct whichStmtNode* whichStmt;
    //     struct declareStmtNode* declareStmt;
    //     struct condStmtNode* condStmt;
    //     struct caseStmtNode* caseStmt;
    //     struct iterStmtNode* iterStmt;
    // } stmtData;
    // access via ASTNode
    stmt_type type;
    struct ASTNode* next; /* Points to next element of type statementNode */
};

/* TODO */
typedef struct simpleStmtNode {

};

typedef struct assignNode {
    // struct LeafNode* lhs_ptr;
    // struct whichStmtNode* whichstmt_ptr;

    /* Access of above will be through ASTNode */
};

typedef struct whichStmtNode {

    /* Either we get an lvalARR statement or 
        lvalIDStmt. In the latter case, synthesize 
        from expression */
    // union {
    //     struct lvalueARRStmtNode* lvalARR;
    //     struct node* exprNode;
    // }; 

    /* Access of above will be through ASTNode, which type 
        we have is infered by type below */


    
    whichType type; /* tag: AST_WHICH_TYPE_LVALID,
                            AST_WHICH_TYPE_LVALARR*/

};

/* -- All nodes below were defined after having a discussion, so they 
        do not have any older definition  -- */ 

typedef struct moduleReuseNode {
    /* TODO: Add data fields later */
    
};

typedef struct idListNode {
    /* TODO: add data fields later */
    struct ASTNode* next;
};

typedef struct exprNode {
    union {
        int val_int;
        float val_float;
        unsigned x:1;
    };
    /* tag:
        AST_EXPR_AOB or AST_EXPR_UNARY */
    expr_type type;
    
};

typedef struct AOBExprNode {
    /*
     * Three children.
     * TODO: Define Data fields later
     */
    
    /* tag */
    aob_type type;
};

typedef struct declareStmtNode {
    /* TODO: add data fields later */
};

typedef struct condStmtNode {
    /* TODO: add data fields later */
};


typedef struct caseStmtNode {
    /* TODO: add data fields later */
    struct ASTNode* next; /* Points to next element of type caseStmtNode */
};

typedef struct unaryNode {
    /* TODO: add data fields later */
};

typedef struct lvalueARRStmtNode {
    /* TODO: add data fields later */
};

typedef struct iterStmtNode {
    /* TODO: add data fields later */
    iter_type type; /* tag for iterative statement */
};

/* Temporary Node */
typedef struct forNode {
    /* TODO: add data fields later */
};

/* Temporary Node */
typedef struct whileNode {
    /* TODO: add data fields later */
};

typedef struct leafNode {
    /* TODO: add data fields later */
};



/**
 * Represents a node in the abstract syntax tree (AST)
 */ 

typedef union {
    struct programNode* program;
    struct moduleDeclarationNode* moduleDeclaration;
    struct moduleListNode* moduleList;
    struct moduleNode* module;
    struct inputListNode* inputList;
    struct outputListNode* outputList;
    struct dataTypeNode* dataType;
    struct rangeArraysNode* rangeArrays;
    struct statementNode* statement;
    struct simpleStmtNode* simpleStmt;
    struct assignNode* assign;
    struct whichStmtNode* whichStmt;
    struct moduleReuseNode* moduleReuse;
    struct idListNode* idList;
    struct exprNode* expr;
    struct AOBExprNode* AOBExpr;
    struct declareStmtNode* declareStmt;
    struct condStmtNode* condStmt;
    struct caseStmtNode* caseStmt;
    struct unaryNode* unary;
    struct lvalueARRStmtNode* lvalueARRStmt;
    struct iterStmtNode* iterStmt;
    struct forNode* for_n;
    struct whileNode* while_n;
} astNodeData;

typedef struct ASTNode {

    /* Attributes specific to the AST node 
       Naming convention: 
        1. Name of node type is the construct name is small case
        2. If the construct name is a keyword in C then append '_n' at the end in (1)
        3. Typedefs not used as they abstract out the record type representing the node and reduce code readability   
    */ 
    union astNodeData nodeData;

    astNodeType type; /* Type of node represented by this AST node */

    /* TODO: Include pointer to symbol table */
    /* TODO: add data fields later */

    /* n-ary tree pointers */
    struct ASTNode* parent;
    struct ASTNode* prev;
    struct ASTNode* next;
    struct ASTNode* child; 
} ASTNode;