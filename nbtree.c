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

static void DFS(addressTrie node, char *buffer, int depth, int *count, char suggestions[][100]){
    if (node == NULL) return;

    /* Simpan karakter node ini ke buffer */
    buffer[depth] = Info(node);

    /* Kalau ini akhir kata, cetak */
    if (IsEndWord(node)) {
        buffer[depth + 1] = '\0';
        (*count)++;
        printf("  [%d] %s\n", *count, buffer);
        strcpy(suggestions[*count - 1], buffer);  /* simpan ke array */
    }

    /* Telusuri anak (huruf berikutnya dalam kata) */
    DFS(FirstChild(node),  buffer, depth + 1, count, suggestions);
    
    /* Telusuri sibling (huruf alternatif di level yang sama) */
    DFS(NextSibling(node), buffer, depth, count, suggestions);
}

void PrintSuggestions(addressTrie root, char* prefix, int* suggestionCount, char suggestions[][100]){
    /* validasi input */
    if (root == NULL || prefix == NULL || prefix[0] == '\0') {
        return;
    }

    /* --- Fase 1: navigasi ke ujung prefix --- */
    addressTrie curr = root;
    int i = 0;

    while (prefix[i] != '\0') {
        /* cari prefix[i] di antara sibling level ini */
        while (curr != NULL && Info(curr) != prefix[i]) {
            curr = NextSibling(curr);
        }

        /* karakter tidak ditemukan: prefix tidak ada di trie */
        if (curr == NULL) {
            printf("  (tidak ada saran untuk \"%s\")\n", prefix);
            return;
        }

        /* masih ada karakter prefix selanjutnya: turun ke firstChild */
        if (prefix[i + 1] != '\0') {
            curr = FirstChild(curr);
        }

        i++;
    }

    /* curr sekarang menunjuk ke node huruf terakhir prefix */

    /* --- Fase 2: siapkan buffer, salin prefix --- */
    char buffer[100];
    int j;
    for (j = 0; j < i - 1; j++) {
        buffer[j] = prefix[j];
    }
    /* buffer[i-1] dan seterusnya akan diisi oleh DFS */

    /* --- Fase 3: DFS dari node ujung prefix --- */
    /* Fase 3: DFS dari node ujung prefix */
    *suggestionCount = 0;

    /* cek apakah prefix itu sendiri kata valid */
    buffer[i - 1] = Info(curr);
    if (IsEndWord(curr)) {
        buffer[i] = '\0';
        (*suggestionCount)++;
        printf("  [%d] %s\n", *suggestionCount, buffer);
        strcpy(suggestions[*suggestionCount - 1], buffer);
    }

    /* DFS hanya ke firstChild, BUKAN nextSibling dari ujung prefix */
    DFS(FirstChild(curr), buffer, i, suggestionCount, suggestions);

    if (*suggestionCount == 0) {
        printf("  (tidak ada saran untuk \"%s\")\n", prefix);
    }
    }

void AddSynonymToTrie(addressTrie root, char* word, char* synonym){
    if (root == NULL || word == NULL || synonym == NULL) return;

    addressTrie curr = root;
    int i = 0;

    /* Menelusuri jalur huruf dari kata dasar */
    while (word[i] != '\0') {
        while (curr != NULL && Info(curr) != word[i]) {
            curr = NextSibling(curr);
        }
        
        /* Jika jalur kata dasar terputus / tidak ada di dalam Trie */
        if (curr == NULL) return; 
        
        if (word[i+1] != '\0') {
            curr = FirstChild(curr);
        }
        i++;
    }

    /* Pastikan node terakhir benar-benar valid sebagai ujung kata */
    if (IsEndWord(curr)) {
        /* Panggil fungsi InsertWord dari dictionary.c */
        InsertWord(&Synonims(curr), synonym); 
    }
}

/* Fungsi untuk mencari dan mengembalikan alamat node dari sebuah kata utuh */
addressTrie SearchNode(addressTrie root, char* word) {
    if (root == NULL || word == NULL) return NULL;
    
    addressTrie curr = root;
    int i = 0;
    
    while (word[i] != '\0') {
        while (curr != NULL && Info(curr) != word[i]) {
            curr = NextSibling(curr);
        }
        if (curr == NULL) return NULL; /* Kata tidak ada di Trie */
        
        if (word[i+1] != '\0') {
            curr = FirstChild(curr);
        }
        i++;
    }
    
    /* Pastikan ini benar-benar ujung kata, bukan sekadar awalan */
    if (IsEndWord(curr)) return curr;
    
    return NULL;
}

void AddThesaurusToTrie(addressTrie root, char* word, char* thesaurusWord){
    if (root == NULL || word == NULL || thesaurusWord == NULL) return;

    addressTrie curr = root;
    int i = 0;

    while (word[i] != '\0') {
        while (curr != NULL && Info(curr) != word[i]) {
            curr = NextSibling(curr);
        }
        
        /* Jika jalur kata dasar terputus / tidak ada di dalam Trie */
        if (curr == NULL) return; 
        
        if (word[i+1] != '\0') {
            curr = FirstChild(curr);
        }
        i++;
    }

    if (IsEndWord(curr)) {
        /* Panggil fungsi InsertWord dari dictionary.c */
        InsertWord(&Thesaurus(curr), thesaurusWord);
    }
}