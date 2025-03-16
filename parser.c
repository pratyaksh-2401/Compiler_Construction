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


#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "parserDef.h"
#include "parseTree.h"
#include "stack.h"
#include "parser.h"
#include "lexer.h"
#include "stack.h"
#include <stdbool.h>




lookupTable* create_parser_lut(){
   lookupTable* lut = (lookupTable*) calloc(1, sizeof(lookupTable));
   lut->hashTable = (List**) calloc(LUT_ARRAY_SIZE, sizeof(List*));
   for(int i=0; i< LUT_ARRAY_SIZE; i++){
      lut->hashTable[i] = (List*) calloc(1, sizeof(List));
      lut->hashTable[i]->head = NULL;
   }

   int i=0;
   while(i < MAX_TERMINALS){
      addNodeToChain(lut, tk_and_nt_array[i], i);
      i++;
   }
   int offset = NON_TERMINAL_OFFSET - MAX_TERMINALS;
   while(i < NUM_NON_TERMINALS + MAX_TERMINALS){
      addNodeToChain(lut, tk_and_nt_array[i], i+offset);
      i++;
   }

   return lut; 
}

int lookup_parser_lut(lookupTable* lut, char* str){
   int index = lookupHashFunc(str);
   Node* temp = lut->hashTable[index]->head;
   while(temp != NULL){
      if(strcmp(str, temp->pattern) == 0){
         return temp->tkn;
      }
      temp = temp->next;
   }
   return -1;
}

grammar getGrammar(FILE* fp, lookupTable* parser_lut){
   grammar g = (grammar) calloc(NUM_NON_TERMINALS, sizeof(NT_rule));
   int i=0;
   while(fscanf(fp, "%d\n", &g[i].numRules) != EOF){
      g[i].prod_rule = (int**) calloc(g[i].numRules, sizeof(int*));
      for(int j=0; j < g[i].numRules; j++){
         char temp[MAX_TandNT_LENGTH];
         fscanf(fp, "%[^ ] ", temp);
         int prod_size;
         fscanf(fp, "%d ", &prod_size);
         g[i].prod_rule[j] = (int*) calloc(prod_size+1, sizeof(int));
         g[i].prod_rule[j][0] = prod_size;
         for(int k=1; k<prod_size; k++){
            char* str = (char*) calloc(MAX_TandNT_LENGTH, sizeof(char));
            fscanf(fp, "%[^ ] ", str);
            // printf("-%s-\n", str);
            int int_val = lookup_parser_lut(parser_lut, str);
            if(int_val == -1){
               printf("Non-Terminal/Terminal not found\n");
               return NULL;
            }
            g[i].prod_rule[j][k] = int_val;
            free(str);
         }
         char* str = (char*) calloc(MAX_TandNT_LENGTH, sizeof(char));
         fscanf(fp, "%s\n", str);
         int int_val = lookup_parser_lut(parser_lut, str);
         if(int_val == -1){
            printf("Non-Terminal/Terminal not found\n");
            return NULL;
         }
         g[i].prod_rule[j][prod_size] = int_val;
         free(str);
      }
      i += 1;
   }
   return g;
}


void computeFirst(int nt, grammar G, FirstAndFollow* F, int* isFirComputed){
   if(isFirComputed[nt]) return;
   isFirComputed[nt]=1;

   for(int i=0;i<G[nt].numRules;i++){
      int ruleLen=G[nt].prod_rule[i][0];

      for(int j=1;j<=ruleLen;j++){
         int symbol=G[nt].prod_rule[i][j];

         if(symbol<MAX_TERMINALS){
            F[nt].firstSet[F[nt].firstCount++] = symbol;
            break;
         }

         else{
            int nonTerminalIndex = symbol-100;
            if(!isFirComputed[nonTerminalIndex]){
               computeFirst(nonTerminalIndex,G,F,isFirComputed);
            }

            for (int k=0;k<F[nonTerminalIndex].firstCount;k++) {
               if (F[nonTerminalIndex].firstSet[k]!=59) {  
                   F[nt].firstSet[F[nt].firstCount++] = F[nonTerminalIndex].firstSet[k];
               }
           }

           int hasEpsilon=0;
           for (int k=0;k<F[nonTerminalIndex].firstCount;k++) {
               if (F[nonTerminalIndex].firstSet[k]==59) {
                   hasEpsilon = 1;
                   break;
               }
           }
           if (!hasEpsilon) break;
           else if(hasEpsilon && j == ruleLen){
            F[nt].firstSet[F[nt].firstCount++]=59;
           }
         }
      }
   }
}

bool inSet(const int* arr, int count, int val) {
   for(int i = 0; i < count; i++) {
       if(arr[i] == val) return true;
   }
   return false;
}
bool firstHasEpsilon(FirstAndFollow* F, int ntIndex) {
   for(int i=0; i < F[ntIndex].firstCount; i++){
       if(F[ntIndex].firstSet[i] == 59) return true;
   }
   return false;
}

void computeAllFollows(grammar G, FirstAndFollow* F) {
   if (!inSet(F[0].followSet, F[0].followCount, TK_EOF)) {
       F[0].followSet[F[0].followCount++] = TK_EOF;
   }

   bool changed = true;
   while (changed) {
       changed = false;

       
       for (int A = 0; A < NUM_NON_TERMINALS; A++) {
           for (int r = 0; r < G[A].numRules; r++) {
               int* rule = G[A].prod_rule[r];
               int len = rule[0]; 
               for (int i = 1; i <= len; i++) {
                   int symbol = rule[i];
                   if (symbol >= NON_TERMINAL_OFFSET) {
                       int B = symbol - NON_TERMINAL_OFFSET; 
                       bool allNullable = true;
                       int index = i + 1;

                       while (index <= len && allNullable) {
                           int nextSymbol = rule[index];
                           if (nextSymbol < MAX_TERMINALS) {
               
                               if (nextSymbol != TK_EPS) {
                                   if (!inSet(F[B].followSet, F[B].followCount, nextSymbol)) {
                                       F[B].followSet[F[B].followCount++] = nextSymbol;
                                       changed = true;
                                   }
                               }
                               
                               allNullable = false;
                           }
                           
                           else {
                               int C = nextSymbol - NON_TERMINAL_OFFSET;
                               for (int f = 0; f < F[C].firstCount; f++) {
                                   int value1 = F[C].firstSet[f];
                                   if (value1 != TK_EPS && !inSet(F[B].followSet, F[B].followCount, value1)) {
                                       F[B].followSet[F[B].followCount++] = value1;
                                       changed = true;
                                   }
                               }

         
                               if (!firstHasEpsilon(F, C)) {
                                   allNullable = false;
                               }
                           }
                           index++;
                       } 
                       if (allNullable) {
                           for (int f = 0; f < F[A].followCount; f++) {
                               int value2 = F[A].followSet[f];
                               if (!inSet(F[B].followSet, F[B].followCount, value2)) {
                                   F[B].followSet[F[B].followCount++] = value2;
                                   changed = true;
                               }
                           }
                       }
                       
                   }
               } 
         } 
      } 
      }
}

FirstAndFollow* ComputeFirstAndFollowSets(grammar G){
   int* isFirComputed = (int*) calloc(NUM_NON_TERMINALS,sizeof(int));
   FirstAndFollow* F = (FirstAndFollow*) malloc(NUM_NON_TERMINALS*sizeof(FirstAndFollow));
   
   for(int i=0;i<NUM_NON_TERMINALS;i++){
      F[i].firstSet = (int*)malloc(MAX_TERMINALS*sizeof(int));
      F[i].followSet = (int*)malloc(MAX_TERMINALS*sizeof(int));
      F[i].firstCount = 0;
      F[i].followCount = 0;
   }
   for(int i=0; i<NUM_NON_TERMINALS; i++){
      if(F[i].firstSet == NULL){
         printf("Null detect for nt:> %d\n", i);
      }
   }

   for(int i=0;i<NUM_NON_TERMINALS;i++){
      computeFirst(i,G,F,isFirComputed);
   }

   computeAllFollows(G,F);

   return F;
}

void createParseTable(FirstAndFollow* F, table T, grammar G){
   for(int i=0; i< NUM_NON_TERMINALS; i++){
      for(int j=0; j<TK_EOF+1; j++){
         T[i][j].nt = -1; // This should be -1 as some table_items should be error/syn
         T[i][j].prod_number = -1;
      }
   }
   for(int i=0; i< NUM_NON_TERMINALS; i++){

      int num_rules = G[i].numRules;
      for(int j=0; j<num_rules; j++){
         int prod_size = G[i].prod_rule[j][0];
         for(int k=1; k<=prod_size; k++){

            int ele = G[i].prod_rule[j][k];
            if(ele < TK_EOF){ 
               T[i][ele].prod_number = j;
               break;
            }
            else if(ele != EPS_TOKEN_VALUE){   
               int hasEps = 0;
               for(int l=0; l<F[ele-NON_TERMINAL_OFFSET].firstCount; l++){
                  int first_ele = F[ele-NON_TERMINAL_OFFSET].firstSet[l];
                  if(first_ele == EPS_TOKEN_VALUE){
                     hasEps = 1;
                  }
                  else{
                     T[i][first_ele].prod_number = j;
                  }
               }
               if(hasEps == 0){
                  break;
               }
            }
            if((ele == TK_EPS) && (k == prod_size)){ 
               for(int l=0; l<F[i].followCount; l++){
                     T[i][F[i].followSet[l]].prod_number = j;
               }
            }
         }  
      }
   }
   
   for(int i=0; i< NUM_NON_TERMINALS; i++){
      int followSize = F[i].followCount;
      for(int j=0; j<followSize; j++){
         int index = F[i].followSet[j];
         if(T[i][index].prod_number < 0){
            
            T[i][index].prod_number = -2;
         }
      }
   }
} 




bool tokenInFollowSet(int A, int token, FirstAndFollow* F) {
   for(int i = 0; i < F[A].followCount; i++){
       if(F[A].followSet[i] == token) return true;
   }
   return false;
}

void panicModeSynchronize(int A, tokenInfo* lookahead, Stack* stack, lookupTable* lut, FirstAndFollow* F) {
   pop(stack);
   while((lookahead->tkn != TK_EOF) && !tokenInFollowSet(A, lookahead->tkn, F)) {
       *lookahead = getNextToken(lut);
   }
   
}


ParseTreeNode* parseInputSourceCode(char *testcaseFile, table T, grammar G, FirstAndFollow* F) {
   
   FILE* fp = fopen(testcaseFile, "r");
    if(!fp) {
        printf("Cannot open file %s\n", testcaseFile);
        return NULL;
    } 
   getStream(fp);
   lookupTable* lut = createLookupTable();
   tokenInfo lookahead = getNextToken(lut);

   ParseTreeNode* root = createParseTreeNode(program, false);
   Stack* stack = createStack();
   push(stack, root);
   int first_Non_terminal_used = 0;

   bool parseError = false;

   while((!isEmpty(stack))) {
       ParseTreeNode* topNode = top(stack);
       int topSymbol = topNode->symbol;  
      
       if(lookahead.tkn == TK_COMMENT){
         lookahead = getNextToken(lut);
         continue;
       }

       if(topSymbol < MAX_TERMINALS) {
           if(topSymbol == lookahead.tkn) {
               pop(stack);
               topNode->isTerminal = true;
               topNode->tokenData = lookahead;
               lookahead = getNextToken(lut);
           }
           else {
               parseError = true;
               if(lookahead.tkn == TK_ERROR){
                  printf("Line %d %s\n", lookahead.line_no, lookahead.pattern);
                  lookahead = getNextToken(lut);
               }
               else if(lookahead.tkn == TK_EOF) {
                  break;
              }
              else{
                  printf("Line %d Error: The token %s for lexeme %s does not match with the expected token %s\n", lookahead.line_no, tk_and_nt_array[lookahead.tkn], lookahead.pattern, tk_and_nt_array[topSymbol]);
                     pop(stack);
                  
               }
           }
       }
       else {
           int A = topSymbol - NON_TERMINAL_OFFSET;  
           int t = lookahead.tkn;
           int prodIndex = T[A][t].prod_number; 

           if(prodIndex == -1) {
               parseError = true;
               printf("Line %d Error: Invalid token %s encountered with value %s stack top %s\n",
                      lookahead.line_no,
                      tk_and_nt_array[lookahead.tkn],
                      lookahead.pattern,
                     tk_and_nt_array[A]);
               panicModeSynchronize(A, &lookahead, stack, lut, F);
           }
           else if(prodIndex == -2) {
               parseError = true;
               printf("SYNCH: discarding non-terminal '%s' at line %u\n",
                      tk_and_nt_array[topSymbol], lookahead.line_no);
               pop(stack);
           }
           else {
               pop(stack);
               int* rule = G[A].prod_rule[prodIndex]; 
               int rhsLen = rule[0]; 
               if(rhsLen == 1 && rule[1] == TK_EPS) {
                   // no children
               }
               else {
                   ParseTreeNode* prevChild = NULL;
                   for(int i=1; i <= rhsLen; i++){
                       int childSymbol = rule[i];
                       bool isTerm = (childSymbol < MAX_TERMINALS);
                        
                       ParseTreeNode* childNode = createParseTreeNode(childSymbol, isTerm);
                       childNode->parent = topNode;

                       if(i == 1) {
                           topNode->firstChild = childNode;
                       }
                       else {
                           prevChild->nextSibling = childNode;
                       }
                       prevChild = childNode;
                   }

                  ParseTreeNode** childArray = (ParseTreeNode**) malloc(rhsLen * sizeof(ParseTreeNode*));
                  int idx=0;
                  ParseTreeNode* ctemp = topNode->firstChild;
                  while(ctemp) {
                      childArray[idx++] = ctemp;
                      ctemp = ctemp->nextSibling;
                  }
                  for(int i=rhsLen-1; i>=0; i--){
                      if(childArray[i]->symbol != TK_EPS) {
                          push(stack, childArray[i]);
                      }
                  }
                  free(childArray);
               }
           }
       }
   } 

   if(!parseError && lookahead.tkn == TK_EOF){
       printf("Input source code is syntactically correct...........\n");
       return root;
   }
   else {
       printf("Parsing ended with errors or leftover tokens.\n");
       return root; 
   }
}



void printNodeInfo(ParseTreeNode* node, FILE* fp) {
   count++;
   if(node->symbol == program){
      char no[] = "no";
      char blank[] = "----";
      fprintf(fp, "%-30s %-30d %-30s %-30s %-30s %-30s %-30s %-30s\n", blank, count, blank, tk_and_nt_array[node->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], blank, "No parent", no, tk_and_nt_array[node->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS]);
   }
   else if(node->isTerminal){
      char yes[] = "yes"; 
      if(node->tokenData.tkn==TK_NUM){
         
         fprintf(fp, "%-30s %-30d %-30d %-30s %-30d %-30s %-30s %-30s\n", node->tokenData.pattern, count, node->tokenData.line_no, tk_and_nt_array[node->tokenData.tkn], node->tokenData.intVal, tk_and_nt_array[node->parent->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], yes, tk_and_nt_array[node->tokenData.tkn]);
      }
      else if(node->tokenData.tkn==TK_RNUM){
         
         fprintf(fp, "%-30s %-30d %-30d %-30s %-30.2f %-30s %-30s %-30s\n", node->tokenData.pattern, count, node->tokenData.line_no, tk_and_nt_array[node->tokenData.tkn], node->tokenData.floatVal, tk_and_nt_array[node->parent->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], yes, tk_and_nt_array[node->tokenData.tkn]);
      }
      else{                                                                                                                                                                                                         
         fprintf(fp, "%-30s %-30d %-30d %-30s %-30s %-30s %-30s %-30s\n", node->tokenData.pattern, count, node->tokenData.line_no, tk_and_nt_array[node->tokenData.tkn], "----", tk_and_nt_array[node->parent->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], yes, tk_and_nt_array[node->tokenData.tkn]);
      }
   }

   else{
      char no[] = "no";
      char blank[] = "----";
      fprintf(fp, "%-30s %-30d %-30s %-30s %-30s %-30s %-30s %-30s\n", blank, count, blank, tk_and_nt_array[node->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], blank, tk_and_nt_array[node->parent->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS], no, tk_and_nt_array[node->symbol - NON_TERMINAL_OFFSET + MAX_TERMINALS]);

   }
}


void printParseTreeInorder(ParseTreeNode* node, FILE* fp) {
   if (!node) return;

   ParseTreeNode** child = NULL;
   int capacity = 0, n = 0;
   ParseTreeNode* temp = node->firstChild;
   while (temp) {
       if (n == capacity) {
           capacity = (capacity == 0 ? 4 : capacity * 2);
           child = (ParseTreeNode**)realloc(child, capacity * sizeof(ParseTreeNode*));
       }
       child[n++] = temp;
       temp = temp->nextSibling;
   }

  
   if (n > 0) {
      printParseTreeInorder(child[0], fp);
   }

   
   printNodeInfo(node, fp);

   
   for (int i = 1; i < n; i++) {
       printParseTreeInorder(child[i], fp);
   }

   free(child);
}


void printParseTree(ParseTreeNode* root, char* outfile) {
   count = 0;
   FILE* fp = fopen(outfile, "w");
   if(!fp) {
       printf("Could not open %s for writing parse tree!\n", outfile);
       return;
   }
   fprintf(fp, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s\n",
           "lexeme", "CurrentNode", "lineno", "tokenName", "valueIfNumber", 
           "parentNodeSymbol", "isLeafNode", "NodeSymbol");
   fprintf(fp, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

   printParseTreeInorder(root, fp);

   fclose(fp);
}


