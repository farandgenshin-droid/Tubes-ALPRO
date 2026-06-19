#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* TIPE DATA */
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

/* Kode waktu dari Pak Panji */

void tahan(float x) {
    time_t start;
    time_t current;
    time(&start);
    do
        time(&current);
    while (difftime(current, start) < x);
}

/* VARIABEL GLOBAL */


int panjang, lebar;
int hadiah;
int i = 0;
int j = 0;
int tambahataurewrite;
int menu;
int x,y;
Gerak g[10000];
Hadiah h[10000];
char player = '0'; 
int skor = 0;
char bentukhadiah = '*';
int a,b;
int jumlahHadiah;

void writehadiah() {
      FILE *Thadiah= fopen("thadiah.txt", "w") ;
            printf("Jumlah hadiah : ");
            scanf("%d", &hadiah);
            for(i = 0; i < hadiah; i++){
            printf("Input hadiah ke-%d:\n", i + 1);
             printf("x, y, nama, skor1 : ");
             scanf("%d %d %s %d", &h[i].x, &h[i].y, h[i].nama, &h[i].skor);
             fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
        }
            fprintf(Thadiah, "###");
            fclose(Thadiah); 
}

void readhadiah () {
    Hadiah temp;
    jumlahHadiah = 0;
    FILE *Thadiah = fopen("thadiah.txt", "r");
    if (Thadiah == NULL)
    {
        printf("Gagal membaca file thadiah.txt\n");
    }
    else
    {
        while (fscanf(Thadiah, "%d %d %s %d", &h[jumlahHadiah].x, &h[jumlahHadiah].y, h[jumlahHadiah].nama, &h[jumlahHadiah].skor) == 4)
        {
            jumlahHadiah++;
        }
        for (i = 0; i < jumlahHadiah - 1; i++)
        {
            for (j = 0; j < jumlahHadiah - 1 - i; j++)
            {
                if (h[j].y > h[j + 1].y)
                {
                    temp = h[j];
                    h[j] = h[j + 1];
                    h[j + 1] = temp;
                }
            }
        }
        fclose(Thadiah);
        Thadiah = fopen("thadiah.txt", "w");
        printf("\nData hadiah saat ini:\n");

        for (i = 0; i < jumlahHadiah; i++)
        {
            fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
            printf(" Posisi (X:%d, Y:%d) |  nama: %s  | Skor: %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
        }
        
        fprintf(Thadiah, "###"); 
        
        fclose(Thadiah);
    }
}

void appendhadiah()
{
    FILE *Thadiah = fopen("thadiah.txt", "a");
    printf("silahkan tambahkan data: \n");
    printf("Jumlah hadiah : ");
    scanf("%d", &hadiah);
    for (i = 0; i < hadiah; i++)
    {
        printf("Input hadiah ke-%d:\n", i + 1);
        printf("x, y, nama, skor : ");
        scanf("%d %d %s %d", &h[jumlahHadiah].x, &h[jumlahHadiah].y, h[jumlahHadiah].nama, &h[jumlahHadiah].skor);
        jumlahHadiah++; 
    }
    fclose(Thadiah);
}

/* PROGRAM UTAMA */

int main() {

    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
        printf("Menu:\n");
        printf("1.Tambah hadiah\n");
        printf("2.Tambah gerak\n");
        printf("3.Simulasi Lite-O\n");  
        printf("4.Keluar\n");
        printf("Masukan Menu (1-4) : ");

        scanf(" %d", &menu);

       if(menu == 1) { // ini gw izin jadiin void yak, sama izin sortinganya gw ubah ke bubble, jujur gw ga paham ma sortingan lu aul wkkwkw
            printf("Ketik 1 untuk tambah hadiah atau angka berapapun untuk rewrite hadiah: ");
            scanf("%d", &tambahataurewrite);
            
            if (tambahataurewrite == 1) {
                readhadiah();
                appendhadiah();
                FILE *Thadiah= fopen("thadiah.txt", "w");

                for(i = 0; i < jumlahHadiah; i++) {
                    fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
                }
                fprintf(Thadiah, "###");
                fclose(Thadiah);
            } 
            else {
                writehadiah();
                readhadiah();
            FILE *Thadiah= fopen("thadiah.txt", "w");

            for(i = 0; i < jumlahHadiah; i++) {
                 fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
            }
            fprintf(Thadiah, "###");
            fclose(Thadiah);
            }
        } 
        
        else if(menu == 2) {
            int n;
            FILE *gerak = fopen("tgerak.txt", "w");
            printf("Jumlah gerakan : ");
            scanf("%d", &n);
            for(j = 0; j < n; j++)
        { 
            printf("Gerakan ke-%d \n", j + 1);
            printf("x dan y: ");
            scanf("%d %d", &g[j].x, &g[j].y);
            while (g[j].x < 0 || g[j].y < 0)
        {
           printf("ga bisa mines");
        break;
        }
        
        fprintf(gerak, "%d %d\n", g[j].x, g[j].y);
    }
    fprintf (gerak,"###");
    fclose(gerak);
    }
        else if(menu == 3){
j = 0;
FILE *gerak = fopen("tgerak.txt", "r");
if (gerak == NULL){
    break;}
while (fscanf(gerak,"%d %d", &g[j].x, &g[j].y) == 2 ){
    system ("cls");
        for (a = 0; a < panjang+3; a++) {
         for (b = 0; b < lebar+3; b++) {
        if (b == 0 || b == lebar+2)
        {
            map[a][b] = '|';
        }
        else if (a == 0 || a == panjang+2)
        {
            map[a][b] = '-';
        }
        else
        {
            map[a][b] = ' ';
        }
    }
}

FILE *Thadiah = fopen("thadiah.txt", "r");
i = 0;
while (fscanf(Thadiah, "%d %d %s %d", &h[i].x, &h[i].y, h[i].nama, &h[i].skor) == 4) {
if (h[i].y >= 0 && h[i].y < lebar+1 && h[i].x >= 0 && h[i].x < panjang+1){
map[h[i].y + 1][h[i].x + 1] = bentukhadiah;
}}fclose(Thadiah);

if (g[j].y >= 0 && g[j].y < lebar+1 && g[j].x >= 0 && g[j].x < panjang+1){
map[g[j].y + 1][g[j].x + 1] = player;
}  

        for (a = 0; a < panjang + 3; a++)
        {
            for (b = 0; b < lebar + 3; b++)
            {
                printf("%c ", map[a][b]);
            }
            printf("\n");
        }

        printf("\nPosisi O : (%d,%d)\n", g[j].x, g[j].y);
        printf("Skor O : %d\n", skor);

        tahan(1);
    } 
    fclose(gerak);
    printf("\nSimulasi selesai!\n");
    printf("Skor akhir : %d\n", skor);
   } 
    else if(menu == 4) {
            printf("\nTerima kasih telah bermain!\n");
            break;
        }
        else {
            printf("\nPilihan tidak valid! Silakan masukkan angka 1-4.\n");
        }
    } 
    return 0;
}