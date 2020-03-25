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

enum {
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

enum {
    AST_TYPE_CAT_PRIM;
    AST_TYPE_CAT_ARRAY;
} astDataTypeCat;

enum {
    AST_TYPE_INT,
    AST_TYPE_REAL,
    AST_TYPE_BOOLEAN,
    AST_TYPE_ARRAY
} astDataType;

enum {
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

struct programNode {

    struct moduleDeclarationNode* dec_head; 
    struct moduleListNode* other_mod1_head;
    struct moduleListNode* driver_mod;
    struct moduleListNode* other_mod2_head;
};

struct moduleDeclarationNode {
    struct leafNode* id_ptr;
    struct moduleDeclarationNode* next;
};

struct moduleListNode {
    struct moduleNode* module_ptr;
    struct moduleListNode* next;
};

struct moduleNode {
    struct leafNode* id_ptr;
    struct inputListNode* input_plist_head;
    struct outputListNode* output_plist_head;
    struct statementNode* moduleDef_head;
};

struct inputListNode {
    struct leafNode* id_ptr;
    struct leafNode* type_ptr;
    struct inputListNode* next;
};

struct outputListNode {
    struct leafNode* id_ptr;
    struct leafNode* type_ptr;
    struct inputListNode* next;
};

struct dataTypeNode {
    struct rangeArraysNode* range_arrays_ptr;
    struct leafNode* type_ptr;
    astDataTypeCat type_cat;
};

struct rangeArraysNode {
    struct leafNode* index1;
    struct leafNode* index2;
};

/* TODO: Need to fix statement node */
struct statementNode {
    union {
        struct simpleStmtNode* simpleStmt;
        struct whichStmtNode* whichStmt;
        struct declareStmtNode* declareStmt;
        struct condStmtNode* condStmt;
        struct caseStmtNode* caseStmt;
        struct iterStmtNode* iterStmt;
    } 

    stmt_type type;
    struct statementNode* next;
    
};

struct simpleStmtNode {

};

struct assignNode {

};

struct whichStmtNode {

};

struct moduleReuseNode {

};

struct idListNode {

};

struct exprNode {

};

struct AOBExprNode {

};

struct declareStmtNode {

};

struct condStmtNode {

};


struct caseStmtNode {

};

struct unaryNode {

};

struct lvalueARRStmtNode {

};

struct iterStmtNode {

};

/* Temporary Node */
struct forNode {

};

/* Temporary Node */
struct whileNode {

};

struct leafNode {

};



/**
 * Represents a node in the abstract syntax tree (AST)
 */ 

struct ASTNode {

    /* Attributes specific to the AST node 
       Naming convention: 
        1. Name of node type is the construct name is small case
        2. If the construct name is a keyword in C then append '_n' at the end in (1)
        3. Typedefs not used as they abstract out the record type representing the node and reduce code readability   
    */ 
    union {
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
    }; 

    astNodeType type; /* Type of node represented by this AST node */

    /* TODO: Include pointer to symbol table */

    /* n-ary tree pointers */
    struct ASTNode* parent;
    struct ASTNode* prev;
    struct ASTNode* next;
    struct ASTNode* child; 
}