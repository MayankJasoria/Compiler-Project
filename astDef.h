/* astDef.h: Contains definitions for constructing abstract syntax tree */

/**
 * nodeType: Identifies the type of node represented by the 
 *           ASTNode. 
 * Naming convention: Construct name in all uppercase letters
 */

enum {
    AST_PROGRAM,
    AST_DECLARATION,
    AST_MODULELIST,
    AST_MODULE,
    AST_INPUTLIST,
    AST_OUTPUTLIST,
    AST_DATATYPE,
    AST_RANGEARRAYS,
    AST_STATEMENT,
    AST_SIMPLESTMT,
    AST_ASSIGN,
    AST_WHICHSTMT,
    AST_MODULEREUSE,
    AST_IDLIST,
    AST_EXPR,
    AST_AOBEXPR,
    AST_DECLARESTMT,
    AST_CONDSTMT,
    AST_CASESTMT,
    AST_UNARY,
    AST_LVALARRSTMT,
    AST_ITERSTMT,
    AST_FOR,
    AST_WHILE,
    AST_LEAF
} astNodeType;

struct programNode {

};

struct declarationNode {

};

struct moduleListNode {

};

struct moduleNode {

};

struct inputListNode {

};

struct outputListNode {

};

struct dataTypeNode {

};

struct rangeArraysNode {

};

struct statementNode {

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
        struct programNode program;
        struct declarationNode declaration;
        struct moduleListNode moduleList;
        struct moduleNode module;
        struct inputListNode inputList;
        struct outputListNode outputList;
        struct dataTypeNode dataType;
        struct rangeArraysNode rangeArrays;
        struct statementNode statement;
        struct simpleStmtNode simpleStmt;
        struct assignNode assign;
        struct whichStmtNode whichStmt;
        struct moduleReuseNode moduleReuse;
        struct idListNode idList;
        struct exprNode expr;
        struct AOBExprNode AOBExpr;
        struct declareStmtNode declareStmt;
        struct condStmtNode condStmt;
        struct caseStmtNode caseStmt;
        struct unaryNode unary;
        struct lvalueARRStmtNode lvalueARRStmt;
        struct iterStmtNode iterStmt;
        struct forNode for_n;
        struct whileNode while_n;
    } attr; 

    astNodeType type; /* Type of node represented by this AST node */

    /* TODO: Include pointer to symbol table */

    /* n-ary tree pointers */
    struct ASTNode* parent;
    struct ASTNode* prev;
    struct ASTNode* next;
    struct ASTNode* child; 
}