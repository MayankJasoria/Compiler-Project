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
    AST_NODE_ARRAY,
    AST_NODE_RANGEARRAYS,
    AST_NODE_STATEMENT,
    AST_NODE_IO,
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
    AST_NODE_VARIDNUM,
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
    AST_STMT_LVALUEARR,
    AST_STMT_SIMPLE_MODULEREUSE,
    AST_STMT_SIMPLE_ASSIGN
} stmt_type;

typedef enum {
    AST_IO_GETVAL,
    AST_IO_PRINT
} io_type;

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

typedef enum {
    AST_MODULE_DRIVER,
    AST_MODULE_OTHER
} module_type;

typedef enum {
    AST_LEAF_INT,
    AST_LEAF_RNUM,
    AST_LEAF_NUM,
    AST_LEAF_BOOL,
    AST_LEAF_ID,
    AST_LEAF_IDXNUM,
    AST_LEAF_IDXID,
    AST_LEAF_PLUS,
    AST_LEAF_MINUS,
    AST_LEAF_MUL,
    AST_LEAF_DIV,
    AST_LEAF_OR,
    AST_LEAF_AND,
    AST_LEAF_LT,
    AST_LEAF_LE,
    AST_LEAF_GT,
    AST_LEAF_GE,
    AST_LEAF_EQ,
    AST_LEAF_NE,
    AST_LEAF_TRUE,
    AST_LEAF_FALSE,
    AST_LEAF_VALNUM,
    AST_LEAF_VALTRUE,
    AST_LEAF_VALFALSE,
    AST_LEAF_VARIDNUM_NUM,
    AST_LEAF_VARIDNUM_ID,
    AST_LEAF_VARIDNUM_RNUM,
    AST_LEAF_BOOLTRUE,
    AST_LEAF_BOOLFALSE,
    AST_LEAF_UOPPLUS,
    AST_LEAF_UOPMINUS
} leaf_type;

/**
 * NOTE: All occurrences of 'int a' are only placeholders
 */

typedef struct pn {
    int a;
    // struct moduleDeclarationNode* dec_head; /* Linkedlist of moduleDeclarationNode */
    // struct moduleListNode* other_mod1_head; /* Linkedlist of moduleListNode */
    // struct moduleListNode* driver_mod;      /* Linkedlist of moduleListNode */
    // struct moduleListNode* other_mod2_head; /* Linkedlist of moduleListNode */
} programNode;

typedef struct {
    int a;
    // struct leafNode* id_ptr;
    // struct moduleDeclarationNode* next;

    // struct leafNode* id_ptr; access
    struct ASTNode* next; /* Points to next element of type moduleDeclarations */

} moduleDeclarationNode; //This is a linked list (C++ equivalent: a vector of pointers)

/* NOTE: These two structures have been collapsed into moduleListNode defined below */

// struct moduleListNode {
//     struct moduleNode* data;
//     struct ASTNode* next;
// };

// struct moduleNode {
//     struct leafNode* id_ptr;
//     struct inputListNode* input_plist_head;
//     struct outputListNode* output_plist_head;
//     struct statementNode* moduleDef_head;
// };


typedef struct {
    module_type type; /* tag AST_MODULE_DRIVER, AST_MODULE_OTHER */
    /* check note above */
    struct ASTNode* next; /* Points to next element of type moduleListNode */
} moduleListNode;


typedef struct {
    // struct leafNode* id_ptr;
    // struct leafNode* type_ptr;
    // struct inputListNode* next; /* Points to next element of type inputListNode */
    struct ASTNode* next; /* Points to next element of type inputListNode */
} inputListNode;

typedef struct {
    // struct leafNode* id_ptr;
    // struct leafNode* type_ptr;
    // struclt outputListNode* next;

    struct ASTNode* next; /* Points to next element of type outputListNode */

} outputListNode;

typedef struct {
    // struct rangeArraysNode* range_arrays_ptr;
    // struct leafNode* type_ptr;
    // access via ASTNode
    astDataTypeCat type_cat;
} dataTypeNode;

typedef struct {
    int a;
    // struct leafNode* index1;
    // struct leafNode* index2;
    // access via ASTNode
} rangeArraysNode;

/* TODO: Need to fix statement node */
typedef struct {
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
} statementNode;

/* TODO */
typedef struct {
    stmt_type type;

} simpleStmtNode;

typedef struct {
    int a;
    // struct LeafNode* lhs_ptr;
    // struct whichStmtNode* whichstmt_ptr;

    /* Access of above will be through ASTNode */
} assignNode;

typedef struct {

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

} whichStmtNode;

/* -- All nodes below were defined after having a discussion, so they 
        do not have any older definition  -- */ 

typedef struct {
    int a;
    /* TODO: Add data fields later */
    
} moduleReuseNode;

typedef struct {
    /* TODO: add data fields later */
    struct ASTNode* next;
} idListNode;

typedef struct {
    union {
        int val_int;
        float val_float;
        unsigned x:1;
    };
    /* tag:
        AST_EXPR_AOB or AST_EXPR_UNARY */
    expr_type type;
    
} exprNode;

typedef struct {
    /*
     * Three children.
     * TODO: Define Data fields later
     */
    
    /* tag */
    aob_type type;
} AOBExprNode;

typedef struct {
    int a;
    /* TODO: add data fields later */
} declareStmtNode;

typedef struct {
    int a;
    /* TODO: add data fields later */
} condStmtNode;

typedef enum {
    AST_CASE_STD,
    AST_CASE_DEFAULT
} case_stmt_type;

typedef struct {
    /* TODO: add data fields later */
    struct ASTNode* next; /* Points to next element of type caseStmtNode */
    case_stmt_type type;
} caseStmtNode;

typedef struct {
    int a;
    /* TODO: add data fields later */
} unaryNode;

typedef struct {
    int a;
    /* TODO: add data fields later */
} lvalueARRStmtNode;

typedef struct {
    /* TODO: add data fields later */
    iter_type type; /* tag for iterative statement */
} iterStmtNode;

/* Temporary Node */
typedef struct {
    int a;
    /* TODO: add data fields later */
} forNode;

/* Temporary Node */
typedef struct {
    int a;
    /* TODO: add data fields later */
} whileNode;

typedef struct {
    /* TODO: add data fields later */
    io_type type;
} ioNode;

typedef struct {

    int a;
} varidnumNode;
    
/* remember: leaf nodes not to be freed */
// typedef union {
//     // typeNode type;
//     // indexNode idx;
// } leafData;

typedef struct {
    /* TODO: add data fields later */
    // leafData ld;

    /* Tags:
    AST_LEAF_INT,
    AST_LEAF_RNUM,
    AST_LEAF_NUM,
    AST_LEAF_BOOL */
    struct treeNode* tn; /* from leaf of parse tree */
    leaf_type type; 
} leafNode;


/**
 * Represents a node in the abstract syntax tree (AST)
 */ 

typedef union {
    programNode* program;
    moduleDeclarationNode* moduleDeclaration;
    moduleListNode* moduleList;
    // struct moduleNode* module;
    inputListNode* inputList;
    outputListNode* outputList;
    dataTypeNode* dataType;
    rangeArraysNode* rangeArrays;
    statementNode* statement;
    ioNode* io;
    simpleStmtNode* simpleStmt;
    assignNode* assign;
    whichStmtNode* whichStmt;
    moduleReuseNode* moduleReuse;
    idListNode* idList;
    exprNode* expr;
    AOBExprNode* AOBExpr;
    declareStmtNode* declareStmt;
    condStmtNode* condStmt;
    caseStmtNode* caseStmt;
    unaryNode* unary;
    lvalueARRStmtNode* lvalueARRStmt;
    iterStmtNode* iterStmt;
    forNode* for_n;
    whileNode* while_n;
    varidnumNode* var;
    leafNode* leaf;
} astNodeData;

typedef struct ASTNode {

    /* Attributes specific to the AST node 
       Naming convention: 
        1. Name of node type is the construct name is small case
        2. If the construct name is a keyword in C then append '_n' at the end in (1)
        3. Typedefs not used as they abstract out the record type representing the node and reduce code readability   
    */ 
    astNodeData nodeData;

    astNodeType type; /* Type of node represented by this AST node */

    /* TODO: Include pointer to symbol table */
    /* TODO: add data fields later */

    /* n-ary tree pointers */
    struct ASTNode* parent;
    struct ASTNode* prev;
    struct ASTNode* next;
    struct ASTNode* child; 
} ASTNode;

