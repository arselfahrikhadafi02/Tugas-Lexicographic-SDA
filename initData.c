#include "initData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fungsi sederhana ala mahasiswa untuk hapus karakter Enter (\r atau \n) di akhir baris */
void hapusNewline(char *str) {
    str[strcspn(str, "\r\n")] = 0;
}

void InitData(addressTrie *root) {
    FILE *file;
    char buffer[2048];
    char *kataDasar, *kataTerkait;

    /* =========================================================
       1. Baca Kamus Suggestion (KataIndonesia.txt)
       ========================================================= */
    file = fopen("KataIndonesia.txt", "r");
    if (file != NULL) {
        /* Baca baris per baris sampai habis */
        while (fgets(buffer, sizeof(buffer), file)) {
            hapusNewline(buffer);
            if (strlen(buffer) > 0) {
                InsertWordToTrie(root, buffer);
            }
        }
        fclose(file);
        printf("[+] Kamus KataIndonesia.txt berhasil diload!\n");
    } else {
        printf("[-] Gagal membuka KataIndonesia.txt\n");
    }

    /* =========================================================
       2. Baca Kamus Sinonim (sinonim.csv)
       ========================================================= */
    file = fopen("sinonim.csv", "r");
    if (file != NULL) {
        while (fgets(buffer, sizeof(buffer), file)) {
            hapusNewline(buffer);
            
            /* Ambil kata pertama sebelum tanda koma */
            kataDasar = strtok(buffer, ",");
            if (kataDasar != NULL) {
                
                /* Looping untuk mengambil sisa kata setelahnya */
                kataTerkait = strtok(NULL, ",");
                while (kataTerkait != NULL) {
                    AddSynonymToTrie(*root, kataDasar, kataTerkait);
                    kataTerkait = strtok(NULL, ",");
                }
            }
        }
        fclose(file);
        printf("[+] Kamus sinonim.csv berhasil diload!\n");
    } else {
        printf("[-] Gagal membuka sinonim.csv\n");
    }

    /* =========================================================
       3. Baca Kamus Thesaurus (Thesaurus.txt)
       ========================================================= */
    file = fopen("Thesaurus.txt", "r");
    if (file != NULL) {
        while (fgets(buffer, sizeof(buffer), file)) {
            hapusNewline(buffer);
            
            kataDasar = strtok(buffer, ",");
            if (kataDasar != NULL) {
                
                /* Trik sederhana: Di Thesaurus kadang ada tag kelas kata (misal: "abadi a awet").
                   Kita potong saja string-nya di spasi pertama agar kataDasar cuma berisi "abadi" */
                char *spasi = strchr(kataDasar, ' ');
                if (spasi != NULL) {
                    *spasi = '\0'; 
                }

                kataTerkait = strtok(NULL, ",");
                while (kataTerkait != NULL) {
                    /* Kalau ada spasi ekstra setelah koma (misal: ", awet"), kita geser 1 karakter */
                    if (kataTerkait[0] == ' ') {
                        kataTerkait++; 
                    }
                    
                    AddThesaurusToTrie(*root, kataDasar, kataTerkait);
                    kataTerkait = strtok(NULL, ",");
                }
            }
        }
        fclose(file);
        printf("[+] Kamus Thesaurus.txt berhasil diload!\n");
    } else {
        printf("[-] Gagal membuka Thesaurus.txt\n");
    }
}