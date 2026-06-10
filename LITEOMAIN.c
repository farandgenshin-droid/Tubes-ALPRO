#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===================== TIPE DATA ===================== */

typedef struct {
    int x;
    int y;
    char nama[50];
    int skor;
} Hadiah;

typedef struct {
    int x;
    int y;
} Gerak;

/* ===================== MESIN WAKTU ===================== */

void tahan(float x) {
    time_t start;
    time_t current;
    time(&start);
    do
        time(&current);
    while (difftime(current, start) < x);
}

/* ===================== VARIABEL GLOBAL ===================== */

int panjang, lebar;
int menu; 

/* ===================== PROGRAM UTAMA ===================== */

int main() {
    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
 
 while(1) {
        printf("");
        printf("Menu:\n");
        printf("1.Tambah hadiah\n");
        printf("2.Tambah gerak\n");
        printf("3.Simulasi Lite-O\n");
        printf("4.Keluar\n");
        printf("Masukan Menu (1-4) : ");

        scanf(" %d", &menu);

        if(menu == 1) {
             Hadiah h;
            FILE *Hadiah = fopen("thadiah.txt", "w") ;
            printf("Input hadiah yang diinginkan : ");
            scanf("%d %d %c %d", &h.x, &h.y, &h.nama, &h.skor);
            fprintf(Hadiah, "###");
            fclose(Hadiah); 
        }
        else if(menu == 2) {
        Gerak g;
       int n, i;
    FILE *gerak = fopen("tgerak.txt", "w");
    printf("Jumlah gerakan : ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    { 
        printf("Gerakan ke-%d \n", i + 1);
        printf("x : ");
        scanf("%d", &g.x);
        printf("y : ");
        scanf("%d", &g.y);
        fprintf(gerak, "%d %d\n", g.x, g.y);
    }
    fprintf (gerak,"###");
    fclose(gerak);
}
        else if(menu == 3) {
            // Memanggil fungsi simulasi  gameplay
        }
        else if(menu == 4) {
            printf("\nTerima kasih telah bermain!\n");
            break;
        }
        else {
            printf("\nPilihan tidak valid! Silakan masukkan angka 1-4.\n");
        }
    }



    Hadiah h;
    FILE *Hadiah = fopen("thadiah.txt", "w") ;
    printf("Input hadiah yang diinginkan : ");
    scanf("%d %d %c %d", &h.x, &h.y, &h.nama, &h.skor);
    fprintf(Hadiah, "###");
    fclose(Hadiah); 


    return 0;
}
