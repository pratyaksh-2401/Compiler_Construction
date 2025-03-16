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

//Contains function prototype declarations of functions in parser.c
#include "parserDef.h"
#include "parseTree.h"
#include "stack.h"

lookupTable* create_parser_lut();
int lookup_parser_lut(lookupTable* lut, char* str);
grammar getGrammar(FILE* fp, lookupTable* parser_lut);
FirstAndFollow* ComputeFirstAndFollowSets(grammar G);
void createParseTable(FirstAndFollow* F, table T, grammar G); 
void print_NTorT(int ele);
ParseTreeNode* parseInputSourceCode(char *testcaseFile, table T, grammar G, FirstAndFollow* F);
void printParseTreeInorder(ParseTreeNode* node, FILE* fp);
void printNodeInfo(ParseTreeNode* node, FILE* fp);
void panicModeSynchronize(int A, tokenInfo* lookahead, Stack* stack, lookupTable* lut, FirstAndFollow* F);
void computeFirst(int nt, grammar G, FirstAndFollow* F,int* isFirComputed);
bool inSet(const int* arr, int count, int val);
bool firstHasEpsilon(FirstAndFollow* F, int ntIndex);
void computeAllFollows(grammar G, FirstAndFollow* F);
void printParseTree(ParseTreeNode* root, char* outfile);