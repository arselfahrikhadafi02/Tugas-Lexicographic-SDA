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
        char input[100];
        char suggestions[50][100]; /* tampung maks 50 suggestion */
        int count = 0;
        char kataAktif[100];

        /* State 0: input */
        printf("Masukkan kata: ");
        scanf("%s", input);

        if (strlen(input) < 3)
        {
            printf("  (input minimal 3 huruf)\n");
            /* ulangi State 0 */
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

        printf("\nLanjut? (1: ya, 0: tidak): ");
        scanf("%d", &lanjut);
    }

    /* lanjut State 2 ... */

    return 0;
}