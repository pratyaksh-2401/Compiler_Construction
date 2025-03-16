/*
Group Number:18
-------------Group Member Names and ID-------------
1]Swapnil Yadav     2021B3A72770P
2]Manav Pahwa       2021B5A72796P
3]Ishan Wani        2021B3A72772P
4]Pratyaksh Kansal  2021B4A72783P
5]Atharv Joshi      2021B4A72749P
---------------------------------------------------
-------------------------------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

clock_t start_time, end_time;
FILE* fileName ;

double total_CPU_time, total_CPU_time_in_seconds;


void measure_execution_time(char* fileName, char* outfile){
     start_time = clock();
    lookupTable* parser_lut = create_parser_lut();
    FILE* grammarFp = fopen("grammar.txt","r");
     if(grammarFp== NULL){
         printf("there is no grammar text file\n");
         return ;
     }
     grammar g = getGrammar(grammarFp,parser_lut);
     FirstAndFollow* F = ComputeFirstAndFollowSets(g);
     table T = (table) malloc(NUM_NON_TERMINALS*sizeof(struct table_item*));
     for(int i=0; i<MAX_TERMINALS; i++){
         T[i] = (struct table_item*) malloc((TK_EOF+1)*sizeof(struct table_item));
     }
     createParseTable(F, T, g);
     ParseTreeNode* root = parseInputSourceCode(fileName,T,g,F);
     if(root==NULL){
         printf("The Source Code contains lexical/syntactical errors\n");
     }
     fclose(grammarFp);

     end_time = clock();

     double total_CPU_time = (double) (end_time - start_time);

     total_CPU_time_in_seconds = total_CPU_time/CLOCKS_PER_SEC ;

     printf("THE TOTAL TIME TAKEN FOR EXECUTION: %lf seconds",total_CPU_time_in_seconds);
     return;
}

// Print both total_CPU_time and total_CPU_time_in_seconds

int main(int argc, char* argv[]){
     if(argc == 2){
          printf("Please enter source code file\n");
          return 0;
     }
     int choice;
     extern char* token_table[];
    printf("----------IMPORTANT POINTS TO CONSIDER----------\n");
    printf("1]WE HAVE AUTOMATED COMPUTATION OF FIRST AND FOLLOW SET\n");
    printf("2]FOR CALCULATION OF EXECUTION TIME ,PARSER IS CALLED WHICH IMPLICITLY CALLS LEXER FUNCTIONS.\n");
    printf("3]WE HAVE USED FILE I/O FOR READING THE GRAMMAR INSTEAD OF HARDCODING\n");
    printf("4]FOR REMOVING COMMENTS THE FILE WILL BE WRITTEN WHEN WE EXIT THE SEQUENCE\n");

    while (1) {
        printf("\nMenu:\n");
        printf("0: Exit\n");
        printf("1: Remove comments\n");
        printf("2: Print token list\n");
        printf("3: Parse code\n");
        printf("4: Measure execution time\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {

            case 0:
                printf("Exiting program.\n");
                return 0;

            case 1:
                removeComments(argv[1], "Clean_Code.txt");//Printing the contents, and file will be written after exiting the program         
                break;

            case 2:
                printf("%-30s%-30s%-30s\n","Token","Lexeme","Line Number\n");
                printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                lookupTable* lut = createLookupTable();
                FILE* fp = fopen(argv[1], "r");
                getStream(fp);
                tokenInfo tknInfo = getNextToken(lut);
                while(strcmp(tknInfo.pattern, "EOF") != 0){
                    if(tknInfo.tkn!=TK_ERROR){
                        printf("%-30s%-30s%-30d\n",token_table[tknInfo.tkn],tknInfo.pattern,tknInfo.line_no);
                    }
                    tknInfo = getNextToken(lut);
                }
                printf("%-30s%-30s%-30d\n",token_table[tknInfo.tkn],tknInfo.pattern,tknInfo.line_no);
                fclose(fp);
                break;

            case 3: {
                    lookupTable* parser_lut = create_parser_lut();
                    FILE* grammarFp = fopen("grammar.txt","r");
                    if(grammarFp== NULL){
                        printf("there is no grammar text file\n");
                        return 0;
                    }
                    grammar g = getGrammar(grammarFp,parser_lut);
                    FirstAndFollow* F = ComputeFirstAndFollowSets(g);
                    table T = (table) malloc(NUM_NON_TERMINALS*sizeof(struct table_item*));
                    for(int i=0; i<MAX_TERMINALS; i++){
                        T[i] = (struct table_item*) malloc((TK_EOF+1)*sizeof(struct table_item));
                    }
                    createParseTable(F,T,g);
                    ParseTreeNode* root = parseInputSourceCode(argv[1],T,g,F);
                    if(root!=NULL){
                        printParseTree(root,argv[2]);
                     }
                    else{
                        printf("The Source Code contains lexical/syntactical errors\n");
                    }
                    fclose(grammarFp);
                    break;
                }
            case 4:
                measure_execution_time(argv[1],argv[2]);
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    return 0;
}

/* ---------------------------------------------------------------------------------------------------------

Perform actions appropriately by invoking appropriate functions.

Also during its execution, the driver displays necessary information regarding the implementation status of your work at the beginning on the console such as

(a) FIRST and FOLLOW set automated
(b) Only Lexical analyzer module developed
(c) Both lexical and syntax analysis modules implemented
(d) modules compile but give segmentation fault
(e) modules work with testcases 2, 3 and 4 only
(f) parse tree could not be constructed

and so on which ever is applicable.*/
