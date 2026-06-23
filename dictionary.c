#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

addressWord AlokasiWordNode(char* word){
    addressWord P = (addressWord)malloc(sizeof(WordNode));
    if (P != NULL) {
        strcpy(Word(P), word);
        Next(P) = NULL;
    }
    return P;
}

void InsertWord(addressWord* list, char* word){
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

void PrintWordList(addressWord list){
    int i = 1;
    addressWord curr = list;
    while (curr != NULL && i <= 20) { /* Batasi maksimal 20 sinonim/thesaurus yang ditampilkan */
        printf("  [%d] %s\n", i, Word(curr));
        curr = Next(curr);
        i++;
    }
    
    if (curr != NULL) {
        printf("  ... (sisa kata lainnya tidak ditampilkan)\n");
    }
}

char* SearchWord(addressWord list, int n){
    int i = 1;
    addressWord curr = list;
    while (curr != NULL && i <= 20) { /* Batasi maksimal 20 sinonim/thesaurus yang ditampilkan */
        if (i == n) {
            return Word(curr);
        }
        curr = Next(curr);
        i++;
    }
    return NULL;
}