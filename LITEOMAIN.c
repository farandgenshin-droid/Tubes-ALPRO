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
int menu;
int x,y;
Gerak g;
Hadiah h;
char player = '0'; 
int skor = 0;


/* PROGRAM UTAMA */

int main() {

    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
    if (panjang == 20 && lebar == 50) {
        printf("Papan catur Lite-O berukuran 20x50 siap dibuat.\n");
    } else {
        panjang = 20;
        lebar = 50;
        printf("Ukuran otomatis disesuaikan menjadi 20x50.\n");
    }
     char map[panjang+1][lebar+1];

 while(1) {
        printf("Menu:\n");
        printf("1.Tambah hadiah\n");
        printf("2.Tambah gerak\n");
        printf("3.Simulasi Lite-O\n");
        printf("4.Keluar\n");
        printf("Masukan Menu (1-4) : ");

        scanf(" %d", &menu);

        if(menu == 1) {
             int hadiah, i;
            FILE *TulisHadiah = fopen("thadiah.txt", "w") ;
            printf("Jumlah hadiah : ");
            scanf("%d", &hadiah);
            for(i = 0; i < hadiah; i++){
            printf("Input hadiah yang diinginkan : ");
            scanf("%d %d %s %d", &h.x, &h.y, h.nama, &h.skor);
            fprintf(TulisHadiah, "%d %d %s %d\n", h.x, h.y, h.nama, h.skor);
        }
            fprintf(TulisHadiah, "###");
            fclose(TulisHadiah); 
            
            /* TAMBAHAN SORTING */
            Hadiah dataHadiah[100];
            Hadiah temp;
            int j;
            int jumlahHadiah = 0;

            TulisHadiah = fopen("thadiah.txt", "r");

            while(fscanf(TulisHadiah,
                 "%d %d %s %d",
                 &dataHadiah[jumlahHadiah].x,
                 &dataHadiah[jumlahHadiah].y,
                 dataHadiah[jumlahHadiah].nama,
                 &dataHadiah[jumlahHadiah].skor) == 4)
    {
            jumlahHadiah++;
    }
    fclose(TulisHadiah);

    for(i = 0; i < jumlahHadiah - 1; i++)
    {
        for(j = i + 1; j < jumlahHadiah; j++)
        {
            if(dataHadiah[i].y > dataHadiah[j].y ||
              (dataHadiah[i].y == dataHadiah[j].y &&
               dataHadiah[i].x > dataHadiah[j].x))
            {
               temp = dataHadiah[i];
               dataHadiah[i] = dataHadiah[j];
               dataHadiah[j] = temp;
            }
        }
    }
    TulisHadiah = fopen("thadiah.txt", "w");

    for(i = 0; i < jumlahHadiah; i++)
    {
        fprintf(TulisHadiah,
                "%d %d %s %d\n",
                dataHadiah[i].x,
                dataHadiah[i].y,
                dataHadiah[i].nama,
                dataHadiah[i].skor);
    }
        fprintf(TulisHadiah, "###");
        fclose(TulisHadiah);
        }
        else if(menu == 2) {
            int n, i;
            FILE *gerak = fopen("tgerak.txt", "w");
            printf("Jumlah gerakan : ");
            scanf("%d", &n);
            for(i = 0; i < n; i++)
        { 
            printf("Gerakan ke-%d \n", i + 1);
            printf("x dan y: ");
            scanf("%d %d", &g.x, &g.y);
            while (g.x <= 0 || g.y <= 0)
        {
           printf("ga bisa 0 dan mines");
        return 0;
        }
        
        fprintf(gerak, "%d %d\n", g.x, g.y);
    }
    fprintf (gerak,"###");
    fclose(gerak);
    }
        else if(menu == 3){
        int a, b;
        /* set up map */
        for (a = 0; a < panjang; a++) {
         for (b = 0; b < lebar; b++) {
            if (a == 0 || a == panjang - 1)
        {
            map[a][b] = '-';
        }
        else if (b == 0 || b == lebar - 1)
        {
            map[a][b] = '|';
        }
        else
        {
            map[a][b] = ' ';
        }
    }
}
map[g.y][g.x] = player;

    for (a = 0; a < panjang; a++) {
        for (b = 0; b < lebar; b++) {
            printf("%c ", map[a][b]);
    }
    printf("\n");
}
    printf("\nSkor O : %d\n", skor);    
   }   else if(menu == 4) {
            printf("\nTerima kasih telah bermain!\n");
            break;
        }
        else {
            printf("\nPilihan tidak valid! Silakan masukkan angka 1-4.\n");
        }
    }





    return 0;
}
