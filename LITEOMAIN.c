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
    int dimakan;
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
char player = 'O'; 
int skor = 0;
char bentukhadiah = '*';
int a,b,k;
int jumlahHadiah;
char letter;

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
                if (h[j].y > h[j + 1].y || (h[j].y == h[j + 1].y && h[j].x > h[j + 1].x))
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
            printf("| Posisi (X:%3d, Y:%3d) | Nama: %-15s | Skor: %3d | \n", h[i].x, h[i].y, h[i].nama, h[i].skor);
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
void tampilanAwal() {
    printf("\033[93m");
    printf("#      #####  #####  #####         #####\n");
    printf("#        #      #    #             #   #\n");
    printf("#        #      #    #####  #####  #   #\n");
    printf("#        #      #    #             #   #\n");
    printf("#####  #####    #    #####         #####\n");
    printf("\033[0m");
    printf("\033[92mTITLE LITE-O\033[0m\n\n");
}
/* PROGRAM UTAMA */

int main() {
    tampilanAwal();   // panggil di sini
    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
     char map[panjang+3][lebar+3];

 while(1) {
        printf("Menu:\n");
        printf("1.Tambah hadiah\n");
        printf("2.Tambah gerak\n");
        printf("3.Simulasi Lite-O\n");  
        printf("4.Keluar\n");
        printf("Masukan Menu (1-4) : ");

        scanf(" %d", &menu);

       if(menu == 1) {
          printf("\n Y/N: ");
          scanf(" %c", &letter);
          if ( letter == 'Y' || letter == 'y'){
            readhadiah();
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
        } else { continue;
        }}

        
        else if(menu == 2) {
          printf("\n Y/N: ");
          scanf(" %c", &letter);
          if ( letter == 'Y' || letter == 'y'){
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
     } else { continue;
    }}
        else if(menu == 3){
j = 0;
FILE *gerak = fopen("tgerak.txt", "r");
if (gerak == NULL){
    break;}

i = 0;
FILE *ThadiahAwal = fopen("thadiah.txt", "r");
if (ThadiahAwal != NULL) {
    while (fscanf(ThadiahAwal, "%d %d %s %d", &h[i].x, &h[i].y, h[i].nama, &h[i].skor) == 4) {
        h[i].dimakan = 0;
        i++;
    }
    jumlahHadiah = i;
    fclose(ThadiahAwal);
}
skor = 0;

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

/* cek apakah O memakan hadiah di posisi sekarang -> skor bertambah, hadiah hilang */
for (i = 0; i < jumlahHadiah; i++) {
    if (!h[i].dimakan && h[i].x == g[j].x && h[i].y == g[j].y) {
        skor += h[i].skor;
        h[i].dimakan = 1;
    }
}

/* gambar hadiah yang belum dimakan, ditulis sebagai nama+skor (mis. "aa5") */
for (i = 0; i < jumlahHadiah; i++) {
if (h[i].dimakan) continue;
if (h[i].y >= 0 && h[i].y < panjang+1 && h[i].x >= 0 && h[i].x < lebar+1) {
    char tulisan[64];
    sprintf(tulisan, "%s%d", h[i].nama, h[i].skor); /* gabungkan nama dan skor jadi satu teks, contoh: "aa5" */
    for (k = 0; tulisan[k] != '\0' && (h[i].x + 1 + k) < lebar+2; k++) {
        map[h[i].y + 1][h[i].x + 1 + k] = tulisan[k]; /* tulis huruf per huruf ke map */
    }
}
}

if (g[j].y >= 0 && g[j].y < panjang+1 && g[j].x >= 0 && g[j].x < lebar+1){
map[g[j].y + 1][g[j].x + 1] = player;
}  

        for (a = 0; a < panjang + 3; a++)
        {
            for (b = 0; b < lebar + 3; b++)
            {
                if (map[a][b] == player) {
                    printf("\033[95m%c \033[0m", map[a][b]); // player warna ungu
                }
                else if (map[a][b] == '-' || map[a][b] == '|') {
                    printf("\033[90m%c \033[0m", map[a][b]); // dinding warna abu-abu
                }
                else if (map[a][b] != ' ') {
                    printf("\033[96m%c \033[0m", map[a][b]); // hadiah warna (bukan dinding, bukan player, bukan spasi)
                }
                else {
                printf("%c ", map[a][b]);
            }
        }
            printf("\n");
    }

        printf("\nPosisi O : (%d,%d)\n", g[j].x, g[j].y);
        printf("Skor O : %d\n", skor);

        tahan(1);
    } 
    fclose(gerak);
}
    else if(menu == 4) {
            printf("\nTerima kasih telah bermain!\n");
            system("exit");
        }
        else {
            printf("\nPilihan tidak valid! Silakan masukkan angka 1-4.\n");
        }
    } 
    return 0;
}