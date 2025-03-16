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

#include "parseTree.h"


ParseTreeNode* createParseTreeNode(int symbol, bool isTerminal) {
    ParseTreeNode* node = (ParseTreeNode*) malloc(sizeof(ParseTreeNode));
    node->symbol = symbol; 
    node->isTerminal = isTerminal;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    node->tokenData.tkn = -1;
    node->tokenData.line_no = -1;
    node->tokenData.pattern = '\0';
    return node;
}
