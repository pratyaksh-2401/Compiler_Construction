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

//Contains all data definitions used in lexer.c 
#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 4096
#define LUT_ARRAY_SIZE 25
#define MAX_PATTERN_SIZE 100
#define MAX_IDENTIFIER_LENGTH 20
#define MAX_FUNCTION_LENGTH 30
#define MAX_LEXEME_LENGTH 100

static int line_no;
typedef struct tokenInfo tokenInfo;
typedef enum token token;
typedef struct lookupTable lookupTable;
typedef struct List List;
typedef struct Node Node;
typedef struct twinBuffer twinBuffer;

enum token{
    TK_ASSIGNOP,
    TK_COMMENT,
    TK_FIELDID,
    TK_ID,
    TK_NUM,
    TK_RNUM,
    TK_FUNID,
    TK_RUID,
    TK_WITH,
    TK_PARAMETERS,
    TK_END,
    TK_WHILE,
    TK_UNION,
    TK_ENDUNION,
    TK_DEFINETYPE,
    TK_AS,
    TK_TYPE,
    TK_MAIN,
    TK_GLOBAL,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_INPUT,
    TK_OUTPUT,
    TK_INT,
    TK_REAL,
    TK_COMMA,
    TK_SEM,
    TK_COLON,
    TK_DOT,
    TK_ENDWHILE,
    TK_OP,
    TK_CL,
    TK_IF,
    TK_THEN,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_RETURN,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_CALL,
    TK_RECORD,
    TK_ENDRECORD,
    TK_ELSE,
    TK_AND,
    TK_OR,
    TK_NOT,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_EOF,
    TK_ERROR,
    TK_EPS
};

struct twinBuffer{
    char* buffer1;
    char* buffer2;
    int currentBuffer;
    int forwardPtr;
    FILE *fp;
};

struct tokenInfo{
    char* pattern;
    token tkn;
    unsigned int line_no; // We are using the additional line number information for error reporting in later stages
    int intVal;
    float floatVal;
};

struct lookupTable{
    List** hashTable;
};

struct List{
    Node* head;
};

struct Node{
    char* pattern;
    token tkn;
    Node* next;
};


#endif