#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbtree.h"
#include "initData.h"
#include "boolean.h"

// gcc main.c nbtree.c initData.c  -o Program

int main()
{
    addressTrie root = NULL;
    InitData(&root);
    int lanjut = 1;

    while (lanjut == 1)
    {
        char input[100] = ""; /* buffer untuk input pengguna */
        char suggestions[50][100]; /* tampung maks 50 suggestion */
        int count = 0;
        char kataAktif[100];

        /* State 0: input */
        while(strlen(input) < 3){
            printf("Masukkan kata: ");
            scanf(" %s", input);
            if(strlen(input) < 3){
                printf("Input harus minimal 3 karakter. Coba lagi.\n");
            }
        }

        /* State 1: tampilkan suggestion */
        PrintSuggestions(root, input, &count, suggestions);

        if (count > 0)
        {
            printf("  [0] Lewati (pakai \"%s\")\n", input);
            printf("Pilih nomor: ");

            int pilihan;
            scanf("%d", &pilihan);

            if (pilihan == 0 || pilihan > count)
            {
                strcpy(kataAktif, input); /* pakai input asli */
            }
            else
            {
                strcpy(kataAktif, suggestions[pilihan - 1]); /* pakai pilihan */
            }
        }
        else
        {
            strcpy(kataAktif, input); /* tidak ada suggestion */
        }

        printf("Kata aktif: %s\n", kataAktif);

        lanjut = -1; /* Set ke nilai awal yang tidak valid */
        while (lanjut != 0 && lanjut != 1) {
            printf("\nLanjut? (1: ya, 0: tidak): ");
            
            /* scanf mereturn 1 jika berhasil membaca tipe data yang sesuai (%d) */
            if (scanf("%d", &lanjut) != 1) {
                printf("Input tidak valid! Harap masukkan angka 1 atau 0.\n");
                
                /* Bersihkan sisa karakter di buffer agar tidak terjadi infinite loop */
                while(getchar() != '\n'); 
                
                lanjut = -1; /* Pastikan loop terus berjalan */
            } 
            else if (lanjut != 0 && lanjut != 1) {
                /* Jika yang diinput berupa angka, tapi bukan 0 atau 1 */
                printf("Pilihan tidak ada. Harap masukkan angka 1 atau 0.\n");
            }
        }
    }

    /* lanjut State 2 ... */

    return 0;
}