/*
Group Number:18
-------------Group Member Names and ID-------------
1]Swapnil Yadav     2021B3A72770P
2]Manav Pahwa       2021B5A72796P
3]Ishan Wani        2021B3A72772P
4]Pratyaksh Kansal  2021B4A72783P
5]Atharv Joshi      2021B4A72749P
---------------------------------------------------
*/

//Contains all definitions for data types such as grammar, table, parseTree etc. used in parser.c

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include "lexerDef.h"

#define MAX_TERMINALS 60
#define NUM_NON_TERMINALS 54
#define MAX_TandNT_LENGTH 100
#define NON_TERMINAL_OFFSET 100
#define EPS_TOKEN_VALUE 59

typedef enum NonTerminal NonTerminal;
typedef struct NT_rule NT_rule;
typedef struct set first;
typedef struct set follow;
typedef struct FirstAndFollow FirstAndFollow;
typedef NT_rule* grammar;
typedef struct table_item** table;

struct NT_rule{
    int numRules;
    int** prod_rule;
};

// struct set{
//     int* terminals; 
// };

struct FirstAndFollow{
    int nt;
    int *firstSet;
    int firstCount;
    int *followSet;
    int followCount;
};

struct table_item{
    int nt;
    int prod_number; // -1 for error, -2 for syn, else prod rule
};

enum NonTerminal{
    program = NON_TERMINAL_OFFSET,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDataType,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    actualOrRedefined,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    fieldType,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    option_single_constructed,
    constructedVariable,
    oneExpansion,
    moreExpansions,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    expPrime,
    term,
    termPrime,
    factor,
    highPrecedenceOperators,
    lowPrecedenceOperators,
    booleanExpression,
    var,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A
};

static char* tk_and_nt_array[] = {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", 
    "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", 
    "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", 
    "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "TK_ERROR", "TK_EOF", "eps",
    "program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDataType", "constructedDatatype", "remaining_list", "stmts", 
    "typeDefinitions", "actualOrRedefined", "typeDefinition", "fieldDefinitions", "fieldDefinition", "fieldType", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", 
    "stmt", "assignmentStmt", "singleOrRecId", "option_single_constructed", "constructedVariable", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", 
    "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "term", "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", 
    "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"
};
static int count;

#endif