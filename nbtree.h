#ifndef NBTREE_H
#define NBTREE_H

#include "boolean.h"
#include "dictionary.h"

typedef struct tTrieNode* addressTrie;

typedef struct tTrieNode{
    char info;
    boolean isEndWord;

    addressWord synonims;
    addressWord thesaurus;

    addressTrie firstChild;
    addressTrie nextSibling;
};

#define Info(P)        (P)->info
#define IsEndWord(P)   (P)->isEndWord
#define Synonims(P)    (P)->synonims
#define Thesaurus(P)   (P)->thesaurus
#define FirstChild(P)  (P)->firstChild
#define NextSibling(P) (P)->nextSibling

addressTrie AlokasiTrieNode(char c);

void InsertWordToTrie(addressTrie* root, char* word);

void PrintSuggestions(addressTrie prefixNode, char* currentWord, int* suggestionCount);

void AddSynonymToTrie(addressTrie root, char* word, char* synonym);

void AddThesaurusToTrie(addressTrie root, char* word, char* thesaurusWord);

#endif