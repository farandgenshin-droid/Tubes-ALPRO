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
int i,j;
int tambahataurewrite;
int menu;
int x,y;
Gerak g;
Hadiah h;
char player = '0'; 
int skor = 0;
char move; 
char bentukhadiah = '*';
char map;
int a,b;
Hadiah dataHadiah[100];
int jumlahHadiah;


void writehadiah() {
      FILE *Thadiah= fopen("thadiah.txt", "w") ;
            printf("Jumlah hadiah : ");
            scanf("%d", &hadiah);
            for(i = 0; i < hadiah; i++){
            printf("Input hadiah ke-%d:\n", i + 1);
             printf("x, y, nama, skor1 : ");
             scanf("%d %d %s %d", &h.x, &h.y, h.nama, &h.skor);
             fprintf(Thadiah, "%d %d %s %d\n", h.x, h.y, h.nama, h.skor);
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
        while (fscanf(Thadiah, "%d %d %s %d", &dataHadiah[jumlahHadiah].x, &dataHadiah[jumlahHadiah].y, dataHadiah[jumlahHadiah].nama, &dataHadiah[jumlahHadiah].skor) == 4)
        {
            jumlahHadiah++;
        }
        for (i = 0; i < jumlahHadiah - 1; i++)
        {
            for (j = 0; j < jumlahHadiah - 1 - i; j++)
            {
                if (dataHadiah[j].y > dataHadiah[j + 1].y)
                {
                    temp = dataHadiah[j];
                    dataHadiah[j] = dataHadiah[j + 1];
                    dataHadiah[j + 1] = temp;
                }
            }
        }
        fclose(Thadiah);
        Thadiah = fopen("thadiah.txt", "w");
        printf("\nData hadiah saat ini:\n");

        for (i = 0; i < jumlahHadiah; i++)
        {
            fprintf(Thadiah, "%d %d %s %d\n", dataHadiah[i].x, dataHadiah[i].y, dataHadiah[i].nama, dataHadiah[i].skor);
            printf(" Posisi (X:%d, Y:%d) |  nama: %s  | Skor: %d\n", dataHadiah[i].x, dataHadiah[i].y, dataHadiah[i].nama, dataHadiah[i].skor);
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
        scanf("%d %d %s %d", &dataHadiah[jumlahHadiah].x, &dataHadiah[jumlahHadiah].y, dataHadiah[jumlahHadiah].nama, &dataHadiah[jumlahHadiah].skor);
        jumlahHadiah++; 
    }
    fclose(Thadiah);
}

/* PROGRAM UTAMA */

int main() {

    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
     char map[panjang+1][lebar+1];

 while(1) {
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
                    fprintf(Thadiah, "%d %d %s %d\n", dataHadiah[i].x, dataHadiah[i].y, dataHadiah[i].nama, dataHadiah[i].skor);
                }
                fprintf(Thadiah, "###");
                fclose(Thadiah);
            } 
            else {
                writehadiah();
                readhadiah();
            FILE *Thadiah= fopen("thadiah.txt", "w");

            for(i = 0; i < jumlahHadiah; i++) {
                 fprintf(Thadiah, "%d %d %s %d\n", dataHadiah[i].x, dataHadiah[i].y, dataHadiah[i].nama, dataHadiah[i].skor);
            }
            fprintf(Thadiah, "###");
            fclose(Thadiah);
            }
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
        break;
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

FILE *Thadiah = fopen("thadiah.txt", "r");
while (fscanf(Thadiah, "%d %d %s %d", &h.x, &h.y, h.nama, &h.skor) == 4) {
    map[h.y][h.x] = bentukhadiah;
}
fclose(Thadiah);


FILE *gerak = fopen("tgerak.txt", "r");
while (fscanf(gerak,"%d %d", &g.x, &g.y) == 2 ){
map[g.y][g.x] = player;
}fclose(gerak);



    for (a = 0; a < panjang; a++) {
        for (b = 0; b < lebar; b++) {
            printf("%c ", map[a][b]);
    }
    printf("\n");
}
    printf("\nSkor O : %d\n", skor);    
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
