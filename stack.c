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

#include "stack.h"


Stack* createStack(){
    Stack* stk = (Stack*) malloc(sizeof(Stack));
    stk->head = NULL;
    return stk;
}


llNode* createNode(ParseTreeNode* pNode){
    llNode* node = (llNode*) malloc(sizeof(llNode));
    node->data = pNode;
    node->next = NULL;
    return node;
}


void push(Stack* stk, ParseTreeNode* pNode){
    llNode* node = createNode(pNode);
    node->next = stk->head;
    stk->head = node;
}


ParseTreeNode* top(Stack* stk ){
    if(stk->head == NULL){
        return NULL;
    }
    return stk->head->data;
}


ParseTreeNode* pop(Stack* stk){
    if(stk->head == NULL){
        return NULL; 
    }
    llNode* temp = stk->head;
    ParseTreeNode* pNode = temp->data;
    stk->head = temp->next;
    free(temp);
    return pNode;
}


int isEmpty(Stack* stk){
    return (stk->head == NULL);
}

