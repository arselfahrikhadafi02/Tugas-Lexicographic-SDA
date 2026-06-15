#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

AlokasiWordNode(char* word){
    addressWord P = (addressWord)malloc(sizeof(WordNode));
    if (P != NULL) {
        strcpy(Word(P), word);
        Next(P) = NULL;
    }
    return P;
}

InsertWord(addressWord* list, char* word){
    addressWord P = AlokasiWordNode(word);
    if (P != NULL) {
        /* Tambah di akhir (Tail) agar urutannya sesuai saat data di-insert */
        if (*list == NULL) {
            *list = P;
        } else {
            addressWord last = *list;
            while (Next(last) != NULL) {
                last = Next(last);
            }
            Next(last) = P;
        }
    }
}

PrintWordList(addressWord list){
    int i = 1;
    addressWord curr = list;
    while (curr != NULL) {
        printf("  [%d] %s\n", i, Word(curr));
        curr = Next(curr);
        i++;
    }
}

SearchWord(addressWord list, int n){
    int i = 1;
    addressWord curr = list;
    while (curr != NULL) {
        if (i == n) {
            return Word(curr);
        }
        curr = Next(curr);
        i++;
    }
    return NULL;
}