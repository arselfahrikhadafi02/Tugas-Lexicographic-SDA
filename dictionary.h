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

#endif