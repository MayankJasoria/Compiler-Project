/*  
	GROUP 48:
	PUNEET ANAND    2016B4A70487P
	MAYANK JASORIA  2016B1A70703P
	SHUBHAM TIWARI  2016B4A70935P
	VIBHAV OSWAL    2016B4A70594P 
*/

/**
 *  astDef.h: Contains definitions for constructing abstract syntax tree 
 *  Note: 'declarationNode' in our semantic rules documentation has been changed to
 *         'moduleDeclarationsNode' in this code to avoid confusion.
 */


#ifndef _AST_DEF
#define _AST_DEF

#include "hash_map.h"

/**
 * BOUND_RUNTIME: The bound checking of the array index is left for runtime.
 * BOUND_CORRECT: The given index access satisfies the bounds of the array. (if statically checked)
 * BOUND_ERROR: The given index access satisfies the bounds of the array. (if statically checked)
 */
typedef enum {
	BOUND_RUNTIME,
	BOUND_ERROR,
	BOUND_CORRECT
} boundCheck;

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

/**
 * astDataType: Identifies the datatype of node represented by the 
 * ASTNode (if it represents some identifier or a subexpression). 
 */
typedef enum astDataType {
	AST_TYPE_INT,
	AST_TYPE_REAL,
	AST_TYPE_BOOLEAN,
	AST_TYPE_ARRAY,
	AST_TYPE_POINTER
} astDataType;

/** 
 * stmt_type: specifies the type of statement if it is a statement type of node
 * naming convention: Construct name in all uppercase letters
 */
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

/**
 * io_type: specifies the type of IO statement for AST_NODE_IO.
 * AST_IO_GETVAL: used for get_value() construct
 * AST_IO_PRINT: used for print construct
 */
typedef enum {
	AST_IO_GETVAL,
	AST_IO_PRINT
} io_type;

/** 
 * iter_type: specifies the type of IO statement for AST_NODE_ITER.
 * AST_ITER_FOR: used for for loop construct
 * AST_ITER_WHILE: used for while loop construct
 */
typedef enum {
	AST_ITER_FOR,
	AST_ITER_WHILE
} iter_type;

/** 
 * module_type: distinguishes driver modules from other modules. 
 * AST_MODULE_DRIVER: for driver module
 * AST_MODULE_Other: for other modules
 */
typedef enum {
	AST_MODULE_DRIVER,
	AST_MODULE_OTHER
} module_type;


/**
 *	leaf_type: specifies the type of leaf node.
 * 	naming convention: type of symbol represented in all uppercase.
 */
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
 *	optype: specifies the type of operation to be performed between subexpressions
 *	AST_LOP: Logical Operator	
 *	AST_RELOP: Relational Operator
 *	AST_AOP: Arithmetic Operator
 */
typedef enum {
	AST_LOP,
	AST_RELOP,
	AST_AOP
} optype;

/* typeSize: array specifying the width of each dataType in bytes */
int typeSize[5];

/* typeName: specifies the string representation corresponding to the enum 'astDataType' */
char typeName[5][20];

typedef struct pn {
	/* no particular field needed for Program Node */
} programNode;

/* This is a linked list type of structure */
typedef struct {
	/* no particular field needed for moduleDeclarationNode node. */
} moduleDeclarationNode; 

typedef struct moduleNode {
	/* points to the line number of corresponding START Keyword */
	int start_line_num;	

	/* points to the line number of corresponding END Keyword */
	int end_line_num;	
} moduleNode;

typedef struct {
	/* tag AST_MODULE_DRIVER, AST_MODULE_OTHER */
	module_type type;

	/* points to the line number of corresponding START Keyword */
	int start_line_num;

	/* points to the line number of corresponding END Keyword */
	int end_line_num;	
} moduleListNode;

typedef struct {
	/* no particular field needed for moduleDeclarationNode node. */
} inputListNode;

typedef struct {
	/* indicates whether the output parameter is being assigned or not */
	int isAssigned;	
} outputListNode;

typedef struct {
	/* Whether Array is static: 0 - Not static, 1 - static */ 
	unsigned is_static:1;

	/* indicates the datatype represented by the node */
	astDataType dataType;	
} dataTypeNode;

typedef struct {
	/* Whether Array is static: 0 - Not static, 1 - static */
	unsigned is_static:1; 
} rangeArraysNode;

typedef struct {
	/* defined above */
	stmt_type type;

	/* Points to next element of type statementNode */
	struct ASTNode* next;	
} statementNode;

typedef struct {
	/* defined above */
	stmt_type type; 
} simpleStmtNode;

typedef struct {
	/* defined above */	
	boundCheck b;	
} assignNode;

typedef struct {
	//delete
	int a;

	/* indicates the type check of the actual and formal parameters */
	int listCheck;
} moduleReuseNode;

typedef struct {
	/* Points to the next identifier in the id list. */
	struct ASTNode* next;
} idListNode;

typedef struct {
	/* Stores the temporary offset during sub-expression evaluation */
	int temporaryOffset;  

	/* Enum value which stores the data type of sub-expression*/
	astDataType dataType;
} AOBExprNode;

typedef struct {
	/* No particular field needed */
	//delete
	int a;
} declareStmtNode;

typedef struct {
	/* Indicates whether the conditional statement has a default case */
	int def;
	
	/* Starting line number of conditional statement scope*/
	int start_line_num;
	
	/* Ending line number of conditional statement scope*/
	int end_line_num;

	/*  Starting line number of default statement */
	int def_line_num;
} condStmtNode;

typedef struct {

	//delete
	struct ASTNode* next; /* Points to next element of type caseStmtNode */
	
	/* Label number of the break statement to jump to */
	int breakLabel;

	/* Label number of the current case statement */
	int label;

	/* Helper variable */
	int lastLabel;

	/* Name of the switch variable of the corresponding conditional statement construct */
	char switchVar[30];

	/* Data type of switch variable */
	astDataType dataType; 
} caseStmtNode;

typedef struct {
	//delete
	int a;

	/* Stores the temporary offset during sub-expression evaluation */
	int temporaryOffset;

	/* Enum value which stores the data type of sub-expression */
	astDataType dataType;
} unaryNode;

typedef struct {
	//delete
	int a;

	/* Enum value which stores the data type of sub-expression */
	astDataType dataType;
} lvalueARRStmtNode;

typedef struct {
	/* tag for iterative statement */
	iter_type type; 

	/* Start line number of the scope of for loop */
	int start_line_num;

	/* End line number of the scope of for loop */
	int end_line_num;
} iterStmtNode;

//delete
typedef struct {
	int a;
	
} forNode;

//delete
typedef struct {
	
} whileNode;

typedef struct {
	/* Indicates the bound check in case of array type variable */
	boundCheck b;

	/* Tag for the type of IO Node: print or get_value */
	io_type type;
} ioNode;

typedef struct {
	/* Indicates the bound check in case of array type variable */
	boundCheck b;

	/* Stores the temporary offset during sub-expression evaluation */
	int temporaryOffset;

	/* Enum value which stores the data type of sub-expression */
	astDataType dataType;

	//delete
	int a;
} varidnumNode;

typedef struct {
	/** 
	 * Corresponding Parse Tree Node of the given leaf 
	 * These parse tree nodes are preserved and not freed
	 */
	struct treeNode* tn; 

	/* Offset in case it represents an ID, NUM, RNUM */
	int temporaryOffset;

	/* Enum value which stores the data type in case it represents an ID, NUM, RNUM */
	astDataType dataType;

	/* Tag if it is a operator */
	optype op;

	/* Tag for the data type of leaf */
	leaf_type type; 
} leafNode;


/* Represents a node in the AST */ 
typedef union {
	programNode* program;
	moduleDeclarationNode* moduleDeclaration;
	moduleListNode* moduleList;
	moduleNode* module;
	inputListNode* inputList;
	outputListNode* outputList;
	dataTypeNode* dataType;
	rangeArraysNode* rangeArrays;
	statementNode* statement;
	ioNode* io;
	simpleStmtNode* simpleStmt;
	assignNode* assign;
	moduleReuseNode* moduleReuse;
	idListNode* idList;
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

struct SymTableFunc;


/**
 * Attributes specific to the AST node 
 * Naming convention: 
 * 1. Name of node type is the construct name is small case
 * 2. If the construct name is a keyword in C then append '_n' at the end in (1)
 * 3. Typedefs not used as they abstract out the record type representing the node and reduce code readability   
 */

typedef struct ASTNode {

	 /* Union structure to hold the specific type of node */
	astNodeData nodeData;

	/* Type of node represented by this AST node */
	astNodeType type; 

	/**
	 * Include pointer to Symbol Table Entry of nested constructs [if, while etc.].
	 * This contains pointer to variable symbol table
	 */
	struct SymTableFunc* localST;
	
	/* Grammar rule corresponding to the given Node while extracting the corresponding tree structure */
	int associatedRule;	
	
	/* Pointers to maintain the logical n-ary tree structure */
	struct ASTNode* parent;
	struct ASTNode* prev;
	struct ASTNode* next;
	struct ASTNode* child; 
} ASTNode;

/** 
 * -------------------------------------------------------------------------------- 
 * 	START OF stDef.h Code here copied from stDef.h to avoid circulardependenncies
 * --------------------------------------------------------------------------------
 */

/* defining a symbol table */
typedef HashTable SymbolTable;

SymbolTable globalST;

typedef enum {
	/* Symbol Table for a given local scope */
	SYM_VARIABLE,

	/* Specifies the symbol table entry is for a function which holds the pointer to its local symbol table */
	SYM_FUNCTION,

	//delete
	SYM_OTHER   /* Ex: If Else Construct */
} SymTableType;

typedef struct arrayInfo {
	/* can only be int, real, boolean */
	astDataType dataType; 
	
	/* lower bound if statically declared */
	int low; 
	
	/* upper bound if statically declared */
	int high; 

	/* identifier of the lower bound of the array variable if array is dynamic */
	char lowId[30]; 
	
	/* identifier of the upper bound of the array variable if array is dynamic */
	char highId[30]; 
} arrayInfo;

/* dataType of the elements in the local symbol tables, contains relevent information */
typedef union {
	/* 
	 * If the local variable is of array datatype, it contains pointer 
	 * to its corresponding arrayInfo structure defined above
	 */
	arrayInfo* r;	
	
	/* Contains the integral value for an integer type local variable */
	int intVal;

	/* Containg the real value for a floating point local variable */
	float floatVal;

	/* Containg the boolean value for a floating point local variable */
	int boolVal:1;
} SymDataType;

/* 
 * scopeType: stores the type of local scope
 * SCOPE_FOR: if it is local scope corresponding to a For statement construct.
 * SCOPE_COND: if it is local scope corresponding to a conditional statement construct.
 * SCOPE_WHILE: if it is local scope corresponding to a While statement construct construct.
 * SCOPE_DEFAULT: if it is local scope corresponding to a module construct.
 */
typedef enum {
	SCOPE_FOR,
	SCOPE_COND,
	SCOPE_WHILE,
	SCOPE_DEFAULT
} scopeType;

typedef struct SymTableFunc {
	/* To cross check if it is a function (type==SYM_FUNCTION) */
	SymTableType type;  

	/* To check if the function is defined*/
	int isDefined;		

	/* To check if the function is declared*/	
	int isDeclared;			

	/* Pointer to the static parent of the scope. */
	struct SymTableFunc * parent; 

	/* Base address of the fuction activation record. */
	int baseAdd; 

	/* Name of the function */
	char name[30]; 
	
	/* List of input parameter variables */
	List input_plist; 
	
	/* List of output parameter variables */
	List output_plist; 
	
	/* Symbol table associated with the local elements of this function, it contains entries of type SymTableVar */
	SymbolTable dataTable; 
	
	/* Field for storing activation record size */
	int actRecSize; 

	/* The sum of the width of the dynamically allocated temporaries in the given scope */
	int dynamicRecSize;
	
	/** 
	 * If loop, then stores the variable involved in the loop statement
	 * If switch-case, then stores the variable involved in the switch statement
	 */
	char dependentVar[30];
	
	/* Tag for the given type of scope */
	scopeType scope;
	
	/* Nested level of the scope */
	int level;

	/* Starting line number of the local scope */
	int start_line_num;
	
	/* Ending line number of the local scope */
	int end_line_num;
	
	/* The sum of the width of the input parameters */
	int inputSize;

	/* The sum of the width of the output parameters */
	int outputSize;

	//delete
	char nextJump[30];
} SymTableFunc;

typedef struct symTableVar {	
	/* To cross check if it is a function (type==SYM_FUNCTION) */
	SymTableType type;

	/* Name of the local variable */
	char name[30];
	
	/* Tag to check if the variable is assigned */
	int isAssigned;

	/* Total memory space to be allocated in bytes */
	int width; 

	/* Offset of the local variable with respect to the parent module in bytes */
	int offset;

	/* Additional paremeter used */
	int whileNest;

	//delete
	int declarationLine;

	
	/* Datatype of variable -> INT, RNUM, BOOL, ARRAY */
	astDataType dataType;

	/* SymTableType record of the corresponding local variable */
	SymDataType sdt;
	
	/* Pointer to the local symbol table */
	SymTableFunc * table;
} SymTableVar;

/* Additional Parameter used */
int varPresent;

/* Additional Parameter used */
int globalNest;

/* Number of Nodes in the AST */
int numASTnodes;

/* Total memory used for the AST */
int ASTSize;

#endif