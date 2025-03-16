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

#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <stdlib.h>
#include <stdbool.h>
#include "lexerDef.h"

typedef struct ParseTreeNode ParseTreeNode;

// struct parseTreeNode{
//     int numChildren;
//     int data;
//     parseTreeNode* children;
// };

typedef struct ParseTreeNode {
    int symbol;                
    bool isTerminal;

    tokenInfo tokenData;       
    
    struct ParseTreeNode* parent;
    struct ParseTreeNode* firstChild;
    struct ParseTreeNode* nextSibling;
} ParseTreeNode;

ParseTreeNode* createParseTreeNode(int symbol, bool isTerminal);

#endif