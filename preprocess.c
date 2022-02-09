/*Zachary Heidemann
CSC310 Spring 2022
*/

#include<stdio.h>
#include "defns.h"

#define MAXLEN 1000

int getLine(char[], int);
void initializeSymbolArray(struct symbol*);
void printSymbols(struct symbol*);

int main(void){
    int len;
    char s[MAXLEN];

    struct symbol Symbols[NSYMBOLS];
    initializeSymbolArray(Symbols);

    while((len = getLine(s, MAXLEN)) > 0){
        for(int i = 0; i < len; i++){
            Symbols[s[i]].freq += 1;
        }
    }

    printSymbols(Symbols);

    return 0;
}


void initializeSymbolArray(struct symbol *symbolPtr){
    for(int i = 0; i < NSYMBOLS; i++, symbolPtr++){
        symbolPtr->symbol = i;
        symbolPtr->freq = 0;
        symbolPtr->parent = NULL;
        symbolPtr->left = NULL;
        symbolPtr->right = NULL;
        symbolPtr->encoding[E_LEN] = '\0';
    }
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

/* print symbols with a freq > 0 */
void printSymbols(struct symbol *symbolPtr){
    for(int i = 0; i < NSYMBOLS; i++, symbolPtr++){
        if(symbolPtr->freq > 0)
            printf("%d\t%d\n", i, symbolPtr->freq);
    }
}