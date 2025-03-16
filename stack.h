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

#ifndef STACK_H
#define STACK_H 

#include <stdio.h>
#include <stdlib.h>
#include "parseTree.h"  

typedef struct llNode {
    ParseTreeNode* data;     
    struct llNode* next;
} llNode;

typedef struct stack {
    llNode* head;            
} Stack;

Stack* createStack();

llNode* createNode(ParseTreeNode* pNode);

void push(Stack* stk, ParseTreeNode* pNode);

ParseTreeNode* pop(Stack* stk);

ParseTreeNode* top(Stack* stk);

int isEmpty(Stack* stk);

#endif
