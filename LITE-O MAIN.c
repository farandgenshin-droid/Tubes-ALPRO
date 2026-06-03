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

/* ===================== PROGRAM UTAMA ===================== */

int main() {
    printf("Selamat Datang di Program Lite-O\n");
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);

    /* TODO: tampilkan menu utama */

    return 0;
}
