#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbtree.h"

addressTrie AlokasiTrieNode(char c){

    addressTrie P;

    P = (addressTrie)malloc(sizeof(struct tTrieNode));

    if(P != NULL){
        Info(P) = c;
        IsEndWord(P) = false;
        Synonims(P) = NULL;
        Thesaurus(P) = NULL;
        FirstChild(P) = NULL;
        NextSibling(P) = NULL;
    }

    return P;
}

void InsertWordToTrie(addressTrie* root, char* word){
    if (word == NULL || word[0] == '\0'){
        return;
    }

    if (*root == NULL){
        *root = AlokasiTrieNode(word[0]);
    }

    addressTrie current = *root;
    int i = 0;

    while (word[i] != '\0'){
        char currentChar = word[i];

        addressTrie prev = NULL;
        addressTrie temp = current;

        while (temp != NULL && Info(temp) != currentChar)
        {
            prev = temp;
            temp = NextSibling(temp);
        }
        
        if (temp == NULL)
        {
            temp = AlokasiTrieNode(currentChar);

            if (prev != NULL)
            {
                NextSibling(prev) = temp;
            }
        }
        
        if (word [i+1] == '\0')
        {
            IsEndWord(temp) = true;
            break;
        }
        
        if (FirstChild(temp) == NULL)
        {
            FirstChild(temp) = AlokasiTrieNode(word[i+1]);
        }
        
        current = FirstChild(temp);
        i++;
    }
}

void PrintSuggestions(addressTrie prefixNode, char* currentWord, int* suggestionCount);

void AddSynonymToTrie(addressTrie root, char* word, char* synonym);

void AddThesaurusToTrie(addressTrie root, char* word, char* thesaurusWord);