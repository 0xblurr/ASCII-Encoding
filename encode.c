#include<stdio.h>
#include<stdlib.h>
#include "defns.h"

#define MAXLEN 100

int getLine(char[], int);
void initializeSymbolArray(char*, int, struct symbol*);
int countAlpha(struct symbol*, char);
void initizalizeAlphaArrays(struct symbol*, struct tree*, struct tree*);
void printSymbols(struct tree*);
void insertionSort(struct tree[], int);

int main(void){

    /************Step 1****************************************/

    struct symbol Symbols[NSYMBOLS];
    struct symbol *symbolPtr = Symbols;
    char s[MAXLEN];
    int len;

    //initizalies array before pulling values from preprocess
    for(int i = 0; i < NSYMBOLS; i++, symbolPtr++){
        symbolPtr->symbol = i;
        symbolPtr->freq = 0;
        symbolPtr->parent = NULL;
        symbolPtr->left = NULL;
        symbolPtr->right = NULL;
        symbolPtr->encoding[E_LEN] = '\0';
    }
    while((len = getLine(s, MAXLEN)) > 0){
        initializeSymbolArray(s, len, Symbols);
    }
    
    /************Step 2****************************************/
    struct tree Alpha[countAlpha(Symbols, 'a')];
    struct tree nonAlpha[countAlpha(Symbols,0)];
    initizalizeAlphaArrays(Symbols, Alpha, nonAlpha);


    /************Step 3****************************************/
    insertionSort(Alpha, 11);
    printSymbols(Alpha);


    return 0;
}

/* read new line into s, return the length*/
int getLine(char s[], int maxLen){
    int i, c;

    for(i = 0; i < maxLen - 1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if(c == '\n'){
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
    
}

//takes a line as input and extracts symbol and freq and places them in the
//appropriate index in Symbols
void initializeSymbolArray(char *string, int len, struct symbol *symbolPtr){
    char sym[E_LEN];
    char freq[E_LEN];
    int i = 0;
    
    while(*string != '\t'){  
        sym[i] = *string;
        string++;
        i++;
    }

    sym[i] = '\0';
    string++;
    i = 0;

    while(*string != '\n'){
        freq[i] = *string;
        i++;
        string++;
    }
    freq[i] = '\0';
    
    (symbolPtr + atoi(sym))->freq = atoi(freq);
  
}

//counts alpha characters and non alphacharacters
int countAlpha(struct symbol *symbolPtr, char op){
    int alphaCount = 0;
    int nonAlphaCount = 0;
    for(int i = 0; i < NSYMBOLS; i++, symbolPtr++){
        if(((i >= 65 && i <= 90) || (i >= 97 && i <= 122)) && symbolPtr->freq > 0)
            alphaCount++;
        else
            nonAlphaCount++;
    }

    //op parameter allows to switch between which value to return
    if(op == 'a')
        return alphaCount;
    else
        return nonAlphaCount;

}

void initizalizeAlphaArrays(struct symbol *symbolPtr, struct tree *alphaPtr, struct tree *nonAlphaPtr){
     for(int i = 0; i < NSYMBOLS; i++, symbolPtr++){
        if(((i >= 65 && i <= 90) || (i >= 97 && i <= 122)) && symbolPtr->freq > 0){
            alphaPtr->index = symbolPtr->symbol;
            alphaPtr->symbol = symbolPtr->symbol;
            alphaPtr->freq = symbolPtr->freq;
            alphaPtr->root = symbolPtr;
            alphaPtr++;
        }else if(symbolPtr->freq > 0){
            nonAlphaPtr->index = symbolPtr->symbol;
            nonAlphaPtr->symbol = symbolPtr->symbol;
            nonAlphaPtr->freq = symbolPtr->freq;
            nonAlphaPtr->root = symbolPtr;
            nonAlphaPtr++;
        }       
    }
}

/* print symbols with a freq > 0 */
void printSymbols(struct tree *treePtr){
    for(int i = 0; i < 11; i++, treePtr++){
        printf("%d %c\n", treePtr->index, treePtr->symbol);
    }
}

void insertionSort(struct tree treeArray[], int len){
    int i;
    struct tree key;
    for(int j = 1; j < len; j++){
        key = treeArray[j];

        i = j - 1;
        while(i >= 0 && treeArray[i].freq > key.freq){
            treeArray[i + 1] = treeArray[i];
            i -= 1;
        }
        treeArray[i + 1] = key;
    }
}