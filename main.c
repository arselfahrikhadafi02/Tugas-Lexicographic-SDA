#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbtree.h"
#include "dictionary.h"
#include "initData.h"
#include "boolean.h"

// gcc main.c nbtree.c initData.c  -o Program

int main()
{
    addressTrie root = NULL;
    InitData(&root);
    
    int programJalan = 1;
    char kalimat[1000] = ""; /* Buffer Sentence Builder */

    while (programJalan == 1)
    {
        char input[100] = ""; 
        char suggestions[50][100]; 
        int count = 0;
        char kataAktif[100];

        /* ================= STATE 0: INPUT ================= */
        while(strlen(input) < 3){
            printf("\nMasukkan kata: ");
            scanf(" %s", input);
            if(strlen(input) < 3){
                printf("Input harus minimal 3 karakter. Coba lagi.\n");
            }
        }

        /* ================= STATE 1: SUGGESTION ================= */
        PrintSuggestions(root, input, &count, suggestions);

        if (count > 0)
        {
            printf("  [0] Lewati (pakai \"%s\")\n", input);
            printf("Pilih nomor: ");

            int pilihan;
            scanf("%d", &pilihan);

            if (pilihan == 0 || pilihan > count) {
                strcpy(kataAktif, input); 
            } else {
                strcpy(kataAktif, suggestions[pilihan - 1]); 
            }
        }
        else
        {
            strcpy(kataAktif, input); 
        }

        /* ================= STATE 2: MENU UTAMA KATA ================= */
        int state2_jalan = 1;
        while(state2_jalan == 1) {
            printf("\nKata aktif: \"%s\"\n", kataAktif);
            printf("  [1] Lihat Sinonim\n");
            printf("  [2] Lihat Thesaurus\n");
            printf("  [3] Simpan & lanjut input\n");
            printf("  [4] Keluar\n");
            printf("Pilih aksi: ");

            int aksi;
            scanf("%d", &aksi);

            switch(aksi) {
                case 1: {
                    /* ================= STATE 3: SINONIM ================= */
                    addressTrie nodeKata = SearchNode(root, kataAktif);
                    
                    /* Cek apakah kata ada di Trie dan punya sinonim */
                    if (nodeKata != NULL && Synonims(nodeKata) != NULL) {
                        printf("\nSinonim untuk \"%s\":\n", kataAktif);
                        
                        /* Panggil fungsi Print dari dictionary.c buatan Arsel */
                        PrintWordList(Synonims(nodeKata)); 
                        
                        printf("  [0] Kembali\n");
                        printf("Pilih nomor: ");
                        
                        int pilSinonim;
                        scanf("%d", &pilSinonim);
                        
                        if (pilSinonim > 0) {
                            /* Ambil string kata menggunakan fungsi buatan Arsel */
                            char* kataBaru = SearchWord(Synonims(nodeKata), pilSinonim);
                            if (kataBaru != NULL) {
                                strcpy(kataAktif, kataBaru); /* Timpa kata aktif */
                            } else {
                                printf("  (Nomor tidak valid)\n");
                            }
                        }
                    } else {
                        printf("\n  (Tidak ada data sinonim untuk \"%s\")\n", kataAktif);
                    }
                    break;
                }
                case 2:
                    /* Bagian Thesaurus (Kerjakan Nanti) */
                    printf("\n  (Fitur Thesaurus belum tersedia)\n");
                    break;
                case 3:
                    /* Sentence Builder: Gabungkan kata ke kalimat */
                    if (strlen(kalimat) > 0) {
                        strcat(kalimat, " "); /* Tambah spasi jika bukan kata pertama */
                    }
                    strcat(kalimat, kataAktif);
                    
                    printf("\n[Kata disimpan! Kalimat sementara: \"%s\"]\n", kalimat);
                    state2_jalan = 0; /* Kembali ke input (State 0) */
                    break;
                case 4:
                    /* Keluar Program dan Cetak Kalimat */
                    if (strlen(kalimat) > 0) {
                        strcat(kalimat, " ");
                    }
                    strcat(kalimat, kataAktif); /* Masukkan kata terakhir */
                    
                    printf("\n=====================================\n");
                    printf("KALIMAT YANG TERBENTUK:\n\"%s\"\n", kalimat);
                    printf("=====================================\n");
                    
                    state2_jalan = 0;
                    programJalan = 0; /* Matikan program */
                    break;
                default:
                    printf("Input tidak valid! Harap pilih 1 - 4.\n");
            }
        }
    }

    return 0;
}