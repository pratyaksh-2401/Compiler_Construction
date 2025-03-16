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

#include "lexer.h"
#include<stdio.h>

twinBuffer B;

void removeComments(char *testcaseFile, char *cleanFile){
    FILE* input_fp = fopen(testcaseFile, "r");
    FILE* output_fp = fopen(cleanFile, "w");
    if(input_fp == NULL || output_fp == NULL){
        printf("Error opening/creating files\n");
        return;
    }
    char c;
    while((c = fgetc(input_fp))!= EOF){
        
        if(c == '%'){
            c = fgetc(input_fp);
            while(c != '\n' && c != EOF) c = fgetc(input_fp);
            fprintf(output_fp, "%c",c);
            continue;
        }
        printf("%c",c);
        fprintf(output_fp,"%c", c);
    }
    fclose(input_fp);
    fflush(output_fp);
    fclose(output_fp);
    return;
}

char* token_table[] = {
    "TK_ASSIGNOP",
    "TK_COMMENT",
    "TK_FIELDID",
    "TK_ID",
    "TK_NUM",
    "TK_RNUM",
    "TK_FUNID",
    "TK_RUID",
    "TK_WITH",
    "TK_PARAMETERS",
    "TK_END",
    "TK_WHILE",
    "TK_UNION",
    "TK_ENDUNION",
    "TK_DEFINETYPE",
    "TK_AS",
    "TK_TYPE",
    "TK_MAIN",
    "TK_GLOBAL",
    "TK_PARAMETER",
    "TK_LIST",
    "TK_SQL",
    "TK_SQR",
    "TK_INPUT",
    "TK_OUTPUT",
    "TK_INT",
    "TK_REAL",
    "TK_COMMA",
    "TK_SEM",
    "TK_COLON",
    "TK_DOT",
    "TK_ENDWHILE",
    "TK_OP",
    "TK_CL",
    "TK_IF",
    "TK_THEN",
    "TK_ENDIF",
    "TK_READ",
    "TK_WRITE",
    "TK_RETURN",
    "TK_PLUS",
    "TK_MINUS",
    "TK_MUL",
    "TK_DIV",
    "TK_CALL",
    "TK_RECORD",
    "TK_ENDRECORD",
    "TK_ELSE",
    "TK_AND",
    "TK_OR",
    "TK_NOT",
    "TK_LT",
    "TK_LE",
    "TK_EQ",
    "TK_GT",
    "TK_GE",
    "TK_NE",
    "TK_EOF"
    ""
};

FILE *getStream(FILE* fp){
    if (fp == NULL) {
        printf("Error while opening file!\n");
        return NULL;
    }

    B.fp = fp;
    B.currentBuffer = 1;
    B.forwardPtr = 0;

    B.buffer1 = (char *)malloc((MAX_BUFFER_SIZE + 1) * sizeof(char));
    B.buffer2 = (char *)malloc((MAX_BUFFER_SIZE + 1) * sizeof(char));

    size_t n1 = fread(B.buffer1, sizeof(char), MAX_BUFFER_SIZE, B.fp);
    B.buffer1[n1] = EOF;

    return fp;
}

char getNextChar() {
    char charRead;
    if (B.currentBuffer == 1) {
        charRead = B.buffer1[B.forwardPtr];
        if (charRead == EOF) {
            size_t n = fread(B.buffer2, sizeof(char), MAX_BUFFER_SIZE, B.fp);
            B.buffer2[n] = EOF;
            B.currentBuffer = 2;
            B.forwardPtr = 0;
        }
        else {
            B.forwardPtr++;
        }
    } 
    else {
        charRead = B.buffer2[B.forwardPtr];
        if (charRead == EOF) {
            size_t n = fread(B.buffer1, sizeof(char), MAX_BUFFER_SIZE, B.fp);
            B.buffer1[n] = EOF;
            B.currentBuffer = 1;
            B.forwardPtr = 0; 
        }
        else {
            B.forwardPtr++;
        }
    }
    return charRead;
}


lookupTable* createLookupTable(){
    line_no = 1;
    lookupTable* lut = (lookupTable*) malloc(sizeof(lookupTable));
    lut->hashTable = (List**) malloc(LUT_ARRAY_SIZE*sizeof(List*));
    for(int i=0; i< LUT_ARRAY_SIZE; i++){
        lut->hashTable[i] = (List*) malloc(sizeof(List));
        lut->hashTable[i]->head = NULL;
    }

    // Entering LUT Values
    addNodeToChain(lut, "with", TK_WITH);
    addNodeToChain(lut, "parameters", TK_PARAMETERS);
    addNodeToChain(lut, "end", TK_END);
    addNodeToChain(lut, "while", TK_WHILE);
    addNodeToChain(lut, "union", TK_UNION);
    addNodeToChain(lut, "endunion", TK_ENDUNION);
    addNodeToChain(lut, "as", TK_AS);
    addNodeToChain(lut, "type", TK_TYPE);
    addNodeToChain(lut, "global", TK_GLOBAL);
    addNodeToChain(lut, "parameter", TK_PARAMETER);
    addNodeToChain(lut, "list", TK_LIST);
    addNodeToChain(lut, "input", TK_INPUT);
    addNodeToChain(lut, "output", TK_OUTPUT);
    addNodeToChain(lut, "int", TK_INT);
    addNodeToChain(lut, "definetype", TK_DEFINETYPE);
    addNodeToChain(lut, "real", TK_REAL);
    addNodeToChain(lut, "endwhile", TK_ENDWHILE);
    addNodeToChain(lut, "if", TK_IF);
    addNodeToChain(lut, "then", TK_THEN);
    addNodeToChain(lut, "endif", TK_ENDIF);
    addNodeToChain(lut, "read", TK_READ);
    addNodeToChain(lut, "write", TK_WRITE);
    addNodeToChain(lut, "return", TK_RETURN);
    addNodeToChain(lut, "call", TK_CALL);
    addNodeToChain(lut, "record", TK_RECORD);
    addNodeToChain(lut, "endrecord", TK_ENDRECORD);
    addNodeToChain(lut, "else", TK_ELSE);

    return lut; 
}

token find_tkn(char* lexeme, lookupTable* lut){
    int index = lookupHashFunc(lexeme);
    Node* temp = lut->hashTable[index]->head;
    while(temp != NULL){
        if(strcmp(lexeme, temp->pattern) == 0){
            return temp->tkn;
        }
        temp = temp->next;
    }
    return TK_FIELDID;
}

tokenInfo generateTokenInfo(char* pattern, token tkn, int line_no){
    tokenInfo tknInfo;
    tknInfo.pattern = (char*) malloc(MAX_PATTERN_SIZE*sizeof(char));
    strcpy(tknInfo.pattern, pattern);
    tknInfo.tkn = tkn;
    tknInfo.line_no = line_no;
    if(tkn == TK_NUM){
        tknInfo.intVal = atoi(pattern);
    }
    else if(tkn == TK_RNUM){
        tknInfo.floatVal = atof(pattern);
    }
    return tknInfo;
}

void retract(){
    
    if(B.forwardPtr == 0){
        
        if(B.currentBuffer == 2){
            
            B.currentBuffer = 1;
            
            B.forwardPtr = strlen(B.buffer1);
        }
        else{
            

            B.currentBuffer = 2;
            
            B.forwardPtr = strlen(B.buffer2);
        }
    }
    B.forwardPtr--;
}

tokenInfo generateErrorToken(char* error_msg){
    retract();
    
    return generateTokenInfo(error_msg, TK_ERROR, line_no); 
}

int is0to9(char c){
    return c>='0' && c<='9';
}

int isatoz(char c){
    return c>='a' && c<='z';
}

int isAtoZ(char c){
    return c>='A' && c<='Z';
}

int is2to7(char c){
    return c>='2' &&  c<='7';
}

tokenInfo getNextToken(lookupTable* lut){
    int state = 0;
    char c;
    tokenInfo tknInfo;
    char* lexeme = (char*) calloc(MAX_LEXEME_LENGTH, sizeof(char));
    char* buffer = (char*)calloc(1, sizeof(char));
    while(1){
        
        switch(state){
            case 0: c = getNextChar();
                    switch(c){
                        case ',':   state = 1;
                                    break;
                        case ']':   state = 2;
                                    break;
                        case '.':   state = 3;
                                    break;
                        case '/':   state = 4;
                                    break;
                        case '!':   state = 5;
                                    break;
                        case ':':   state = 7;
                                    break;
                        case ';':   state = 8;
                                    break;
                        case ')':   state = 9;
                                    break;
                        case '(':   state = 10;
                                    break;
                        case '%':   state = 11;
                                    break;
                        case EOF:  state = 13;
                                    break;
                        case '*':   state = 14;
                                    break;
                        case '\t':  
                        case ' ':   state = 15;
                                    break;
                        case '\n':  state = 17;
                                    break;
                        case '&':   state = 18;
                                    break;
                        case '~':   state = 21;
                                    break;
                        case '@':   state = 22;
                                    break;
                        case '[':   state = 25;
                                    break;
                        case '-':   state = 26;
                                    break;
                        case '+':   state = 27;
                                    break;
                        case '=':   state = 28;
                                    break;
                        case '<':   state = 31;
                                    break;
                        case '>':   state = 37;
                                    break;
                        case '_':   strcat(lexeme, "_");
                                    state = 40;
                                    break;
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':   buffer[0] = c;
                                    strcat(lexeme, buffer);
                                    state = 44;
                                    break;
                        case '#':   state = 55;
                                    buffer[0] = c;
                                    strcat(lexeme,buffer);
                                    break;
                        case 'b':
                        case 'c':
                        case 'd':   buffer[0] = c;
                                    strcat(lexeme,buffer);
                                    state = 58;
                                    break;
                        case 'a':
                        case 'e':
                        case 'f':
                        case 'g':
                        case 'h':
                        case 'i':
                        case 'j':
                        case 'k':
                        case 'l':
                        case 'm':
                        case 'n':
                        case 'o':
                        case 'p':
                        case 'q':
                        case 'r':
                        case 's':
                        case 't':
                        case 'u':
                        case 'v':
                        case 'w':
                        case 'x':
                        case 'y':
                        case 'z':   buffer[0] = c;
                                    strcat(lexeme,buffer);
                                    state = 59;
                                    break;
                        default:    {//printf("-%c-\n", c);
                                    // return generateErrorToken("Error: Pattern Unknown");
                                    tokenInfo tknInfo;
                                    tknInfo.pattern = (char*) malloc(MAX_PATTERN_SIZE*sizeof(char));
                                    strcpy(tknInfo.pattern, "Error: Unknown Symbol <");
                                    buffer[0] = c;
                                    strcat(tknInfo.pattern, buffer);
                                    strcat(tknInfo.pattern, ">");
                                    tknInfo.tkn = TK_ERROR;
                                    tknInfo.line_no = line_no;
                                    return tknInfo;}
                    }
                    break;
            case 1: return generateTokenInfo(",", TK_COMMA, line_no);
            case 2: return generateTokenInfo("]", TK_SQR, line_no); 
            case 3: return generateTokenInfo(".", TK_DOT, line_no); 
            case 4: return generateTokenInfo("/", TK_DIV, line_no);
            case 5: c = getNextChar();
                    if(c == '='){
                        state = 6;
                    }
                    else{
                        return generateErrorToken("Error: Unknown pattern <!>");
                    }
                    break;
            case 6: return generateTokenInfo("!=", TK_NE, line_no);
            case 7: return generateTokenInfo(":", TK_COLON, line_no);
            case 8: return generateTokenInfo(";", TK_SEM, line_no);  
            case 9: return generateTokenInfo(")", TK_CL, line_no);  
            case 10: return generateTokenInfo("(", TK_OP, line_no); 
            case 11: c = getNextChar();
                     while(1){
                        if(c == '\n'){
                            state = 12;
                            break;
                        }
                        else if(c == EOF){
                            state = 65;
                            break;
                        }
                        c = getNextChar();
                     }
                     break;
            case 12: tknInfo = generateTokenInfo("%", TK_COMMENT, line_no);
                     line_no++;
                     return tknInfo; 
            case 13: return generateTokenInfo("EOF", TK_EOF, line_no);
            case 14: return generateTokenInfo("*", TK_MUL, line_no);
            case 15: c = getNextChar(); 
                     while(1){
                        if(c!='\t'&&c!=' '){ 
                            state = 16;
                            break;
                        }
                        c = getNextChar();
                     }
                     break;
            case 16: retract();
                     state=0;
                     break;  
            case 17: line_no++;
                     state=0;
                     break;
            case 18: c = getNextChar();
                     if(c=='&'){
                        state = 19;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <&>");
                     }
                     break;
            case 19: c = getNextChar();
                     if(c=='&'){
                        state = 20;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <&&>");
                     }
                     break;
            case 20: return generateTokenInfo("&&&", TK_AND, line_no);  // yhan bhi galti hai ek baar or if(&) karna padega mp. oh achha phir ok
            case 21: return generateTokenInfo("~", TK_NOT, line_no);
            case 22: c = getNextChar();
                     if(c=='@'){
                        state = 23;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <@>");
                     }
                     break; 
            case 23: c = getNextChar();
                     if(c=='@'){
                        state = 24;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <@@>");
                     }
                     break; 
            case 24: return generateTokenInfo("@@@",TK_OR,line_no);  
            case 25: return generateTokenInfo("[",TK_SQL,line_no);  
            case 26: return generateTokenInfo("-",TK_MINUS,line_no);
            case 27: return generateTokenInfo("+",TK_PLUS,line_no);  
            case 28: c = getNextChar();
                     if(c=='='){
                        state = 29;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <=>");
                     }      
                     break;
            case 29: return generateTokenInfo("==",TK_EQ,line_no); 
            case 31: c = getNextChar();
                     if(c=='='){
                        state = 30;
                     }
                     else if(c=='-'){
                        state = 32;
                     }
                     else{
                        state = 36;
                     }
                     break;
            case 30: return generateTokenInfo("<=",TK_LE,line_no);
            case 32: c = getNextChar();
                     if(c=='-'){
                        state = 33;
                     }
                     else{
                        state = 35;
                     }
                     break;
            case 33: c = getNextChar();
                     if(c=='-'){
                        state = 34;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <<-->");
                     }
                     break;
            case 34: return generateTokenInfo("<---",TK_ASSIGNOP,line_no);
            case 35: retract();
                     retract();
                     return generateTokenInfo("<",TK_LT,line_no);
            case 36: retract();
                     return generateTokenInfo("<",TK_LT,line_no);
            case 37: c = getNextChar();
                     if(c=='='){
                        state = 38;
                     }
                     else{
                        state = 39;
                     }
                     break;
            case 38: return generateTokenInfo(">=",TK_GE,line_no);
            case 39: retract();
                     return generateTokenInfo(">",TK_GT,line_no);
            case 40: c = getNextChar();
                     if(isatoz(c)||isAtoZ(c)){
                        buffer[0] = c;
                        // printf("%s", buffer);
                        strcat(lexeme,buffer);
                        state = 41;
                        break;
                     }
                     else{
                        return generateErrorToken("Error: Unknown pattern <_>");
                     }
            case 41: c = getNextChar();
                     while(1){
                        if(is0to9(c)){
                            if(strlen(lexeme) == 30){
                                while(is0to9(c)) c= getNextChar();
                                return generateErrorToken("Error: Function Identifier is longer than the prescribed length of 30 characters.");
                            }
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                            state = 42;
                            break;
                        }
                        else if(isatoz(c)||isAtoZ(c)){
                            if(strlen(lexeme) == 30){
                                while(isatoz(c) || isAtoZ(c)) c = getNextChar();
                                while(is0to9(c)) c= getNextChar();
                                return generateErrorToken("Error: Function Identifier is longer than the prescribed length of 30 characters.");
                            }
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                            state=41;
                        }
                        else{
                            state = 43;
                            break;
                        }
                        c = getNextChar();
                     }
                     break;
            case 42: c = getNextChar();
                     while(1){
                        buffer[0] = c;
                        if(!is0to9(c)){
                            
                            state = 43;
                            break;
                        }
                        if(strlen(lexeme) == 30){
                            while(is0to9(c)) c= getNextChar();
                            return generateErrorToken("Error: Function Identifier is longer than the prescribed length of 30 characters.");
                        }
                        strcat(lexeme,buffer);
                        c = getNextChar();
                     }
                     break;
            case 43: retract();
                    //  printf("Hit---\n");
                     if(strcmp(lexeme, "_main") == 0) return generateTokenInfo(lexeme, TK_MAIN, line_no);
                    //  addNodeToChain(lut, lexeme, TK_FUNID);
                     return generateTokenInfo(lexeme, TK_FUNID, line_no);
            case 44: c = getNextChar();
                    while(1){
                        if(is0to9(c)){
                            state = 44;
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                        }
                        else if(c=='.'){
                            state = 46;
                            break;
                        }
                        else{
                            state = 45;
                            break;
                        }
                        c = getNextChar();
                    }
                    break;
            case 45: retract();
                    return generateTokenInfo(lexeme, TK_NUM, line_no);
            case 46: c = getNextChar();
                    if(is0to9(c)){
                        state = 48;
                        buffer[0] = c;
                        strcat(lexeme, ".");
                        strcat(lexeme, buffer);
                    }
                    else{
                        state = 47;
                    }
                    break;
            case 47: retract();
                     retract();
                     return generateTokenInfo(lexeme,TK_NUM,line_no);
            case 48: c = getNextChar();
                     if(is0to9(c)){
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 49;
                     }
                     else{
                        char error_msg[100] = "Error: Unknown pattern <";
                        strcat(error_msg, lexeme);
                        strcat(error_msg,">");
                        return generateErrorToken(error_msg);
                     }
                     break;
            case 49: c = getNextChar();
                    if(c == 'E'){
                        state = 51;
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 51;
                    }
                    else{
                        state = 50;
                    }
                    break;
            case 50: retract();
                     return generateTokenInfo(lexeme,TK_RNUM,line_no);
            case 51:c= getNextChar();                                              
                     if(c == '+' ||  c == '-'){
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 52;
                        break;
                     }
                     else if(is0to9(c)){
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 53;
                        break;
                     }
                     else{
                        // char* error_msg = calloc(100, sizeof(char));
                        char error_msg[100] = "Error: Unknown pattern <";
                        // strcat(error_msg, "Error: Unknown pattern <");
                        strcat(error_msg, lexeme);
                        strcat(error_msg,">");
                        return generateErrorToken(error_msg);
                     }
            case 52: c = getNextChar();
                     if(is0to9(c)){
                        buffer[0] = c;
                        strcat(lexeme, buffer);
                        state = 53;
                        break;
                     }
                     else{
                        // char* error_msg = calloc(100, sizeof(char));
                        char error_msg[100] = "Error: Unknown pattern <";
                        // strcat(error_msg, "Error: Unknown pattern <");
                        strcat(error_msg, lexeme);
                        strcat(error_msg,">");
                        return generateErrorToken(error_msg);
                     }
            case 53: c = getNextChar();
                     if(is0to9(c)){
                        state = 54;
                        buffer[0] = c;
                        strcat(lexeme, buffer);
                        break;
                     }
                     else{
                        // buffer[0] = c;
                        // strcat(lexeme, buffer);
                        // char* error_msg = calloc(100, sizeof(char));
                        char error_msg[100] = "Error: Unknown pattern <";
                        // strcat(error_msg, "Error: Unknown pattern <");
                        strcat(error_msg, lexeme);
                        strcat(error_msg,">");
                        return generateErrorToken(error_msg);
                     }
            case 54: return generateTokenInfo(lexeme,TK_RNUM,line_no);
            case 55: c = getNextChar();
                     if(isatoz(c)){
                        buffer[0] =c;
                        strcat(lexeme,buffer);
                        state = 56;
                        break;
                      }
                     else{
                         return generateErrorToken("Error: Unknown pattern <#>");
                      }
            case 56: c = getNextChar();
                     if(isatoz(c)){
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                           state = 56;
                           break;
                      }
                     else{
                        state = 57;
                      }
                     break;
            case 57: retract();
                     return generateTokenInfo(lexeme,TK_RUID,line_no);
            case 58: c = getNextChar();
                     if(isatoz(c)){
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 59;
                        break;
                     }
                     else if(is2to7(c)){
                        buffer[0] = c;
                        strcat(lexeme,buffer);
                        state = 61;
                        break;
                     }
                     else{
                        state = 64;
                     }
                     break;
            case 59: c = getNextChar();
                     while(1){
                        if(isatoz(c)){
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                            state = 59;
                            break;
                         }
                         else{
                            state = 60;
                            break;
                         }
                         c = getNextChar();
                     }
                     break;
            case 60: retract();
                     return generateTokenInfo(lexeme, find_tkn(lexeme, lut), line_no);
            case 61: c = getNextChar();
                     
                     while(1){
                        if(c == 'b'|| c == 'c'|| c=='d'){
                            if(strlen(lexeme)==20){
                                c = getNextChar();                
                                while(c =='b'||c=='c'||c=='d'){
                                    c = getNextChar();
                                }
                                while(is2to7(getNextChar()));
                                return generateErrorToken("Error: Variable Identifier is longer than the prescribed length of 20 characters.");
                            }
                            buffer[0] = c;
                            
                            strcat(lexeme,buffer);
                            state = 61;
                         }
                         else if(is2to7(c)){
                            if(strlen(lexeme)==20){
                                c = getNextChar();
                                while(is2to7(c)){
                                    c = getNextChar();
                                }
                                return generateErrorToken("Error: Variable Identifier is longer than the prescribed length of 20 characters.");
                            }
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                            state  = 62;
                            break;
                         }
                         else{
                            state = 63;
                            break; 
                         }
                        c = getNextChar();
                    }
                    break;
                        
            case 62: c = getNextChar();
                     while(1){
                        if(is2to7(c)){
                            buffer[0] = c;
                            strcat(lexeme,buffer);
                            state = 62;
                        }
                        else{
                            state = 63;
                            break;
                        }
                        c = getNextChar();
                     }
                     break;
            case 63: retract();
                     return generateTokenInfo(lexeme,TK_ID,line_no);
            case 64: retract();
                     return generateTokenInfo(lexeme, TK_FIELDID, line_no);
            case 65: tknInfo = generateTokenInfo("%", TK_COMMENT, line_no);
                     retract();
                     state = 0;
                     return tknInfo; 
            default: return generateErrorToken("Error: Unknown Symbol");
        }
    }
}

int lookupHashFunc(char* pattern){
    int sum = 0;
    for(int i=0; i<strlen(pattern); i++){
        sum += pattern[i];
    }
    int index = sum % LUT_ARRAY_SIZE;
    return index;
}


void addNodeToChain(lookupTable* lut, char* pattern, int tkn){
    int index = lookupHashFunc(pattern);
    Node* n = (Node*) malloc(sizeof(Node));
    n->pattern = (char*) malloc(strlen(pattern)*sizeof(char));
    strcpy(n->pattern, pattern);
    n->tkn = tkn;
    n->next = lut->hashTable[index]->head;
    lut->hashTable[index]->head = n;
    return;
}


void printTokenInfo(tokenInfo tknInfo){
    if(tknInfo.tkn == TK_ERROR) printf("Line no %d\t%s\n", tknInfo.line_no, tknInfo.pattern);  // Different printing style for error tokens
    else printf("Line no %d\tLexeme %s\tToken %s\n", tknInfo.line_no, tknInfo.pattern, token_table[tknInfo.tkn]);
    return;
}
