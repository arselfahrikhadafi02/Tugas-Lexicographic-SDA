#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "boolean.h"

#define Nil NULL

typedef struct tWordNode* addressWord;

typedef struct tWordNode {
    char word[100]; 
    addressWord next;
} WordNode;

#define Word(P) (P)->word
#define Next(P) (P)->next

AlokasiWordNode(char* word);

InsertWord(addressWord* list, char* word);

PrintWordList(addressWord list);

SearchWord(addressWord list, int n);

#endif