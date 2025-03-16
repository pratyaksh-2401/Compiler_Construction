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

//Contains function prototype declarations of functions in lexer.c
#ifndef LEXER_H
#define LEXER_H
#include "lexerDef.h"

// Lookup Table Functions
lookupTable* createLookupTable();
int lookupHashFunc(char* tkn);
void addNodeToChain(lookupTable* lut, char* pattern, int tkn);
token find_tkn(char* lexeme, lookupTable *lut);

// Functions to be implemented as part of the project
FILE *getStream(FILE *fp);
tokenInfo getNextToken(lookupTable* lut);
void removeComments(char *testcaseFile, char *cleanFile);

// Helper Functions
void retract();
tokenInfo generateErrorToken(char* error_msg);
void addToLexeme(char* lexeme, char c);
int is0to9(char c);
int isatoz(char c);
int isAtoZ(char c);
int is2to7(char c);


#endif