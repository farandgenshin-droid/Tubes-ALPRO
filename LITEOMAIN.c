#include <stdio.h>   /* Library untuk fungsi input/output dasar, seperti printf dan scanf */
#include <stdlib.h>  /* Library untuk fungsi umum, seperti exit() dan alokasi memori */
#include <string.h> /* Library untuk fungsi-fungsi yang berhubungan dengan teks/string */
#include <time.h>    /* Library untuk fungsi yang berhubungan dengan waktu, dipakai di fungsi tahan() */

/* Struktur data untuk menyimpan informasi satu hadiah di dalam permainan */
typedef struct {
    int x;          /* posisi hadiah pada sumbu x (kolom) */
    int y;          /* posisi hadiah pada sumbu y (baris) */
    char nama[50];  /* nama atau simbol untuk hadiah, contoh "aa" */
    int skor;       /* jumlah skor yang didapat jika hadiah ini dimakan oleh pemain */
    int dimakan;    /* status hadiah: 0 berarti belum dimakan, 1 berarti sudah dimakan */
} Hadiah;

/* Struktur data untuk menyimpan satu gerakan pemain, berupa koordinat x dan y */
typedef struct {
    int x; /* posisi x tujuan gerakan pemain */
    int y; /* posisi y tujuan gerakan pemain */
} Gerak;

/* Kode waktu dari Pak Panji */
/* Fungsi tahan() ini dibuat untuk memberikan jeda waktu eksekusi. jadi waktu saat fungsi 
ini dipanggil, saat menjalankan loop akan menahan alur eksekusi sampai selisih waktunya (difftime)
mencapai x detik. Efeknya, saat simulasi berjalan, pergerakan karakter 'O' nggak akan langsung selesai dalam sekejap */
void tahan(float x) {
    time_t start;
    time_t current;
    time(&start);
    do
        time(&current);
    while (difftime(current, start) < x); // Loop menahan eksekusi selama selisih waktu belum x detik
}

/* VARIABEL GLOBAL */

int panjang, lebar;    /* panjang dan lebar papan permainan, diisi oleh pengguna di awal program */
int hadiah;            /* jumlah hadiah yang akan diinput oleh pengguna */
int i = 0;             /* variabel i, dipakai sebagai variabel perulangan (looping) di berbagai fungsi */
int j = 0;             /* variabel j, dipakai sebagai variabel perulangan (looping) di berbagai fungsi */
int tambahataurewrite; /* pilihan pengguna: mau menambah hadiah baru atau menulis ulang seluruh data hadiah */
int menu;              /* menyimpan pilihan menu yang diinput oleh pengguna (1 sampai 4) */
int x,y;               /* variabel x dan y, dipakai sebagai variabel bantuan umum */
Gerak g[10000];        /* array untuk menyimpan seluruh data gerakan pemain, maksimal 10000 gerakan */
Hadiah h[10000];       /* array untuk menyimpan seluruh data hadiah, maksimal 10000 hadiah */
char player = 'O';     /* karakter yang melambangkan posisi pemain di papan permainan, defaultnya 'O' */
int skor = 0;          /* total skor yang sudah didapatkan pemain selama permainan berlangsung */
char bentukhadiah = '*';/* karakter yang melambangkan bentuk hadiah di papan permainan */
int a,b,k,n;             /* variabel a, b, k, n dipakai sebagai variabel perulangan (looping) di berbagai fungsi */
int jumlahHadiah, jumlahgerak;      /* jumlah hadiah dan gerak yang sedang tersimpan dan aktif di dalam program */
char letter;           /* menyimpan jawaban Y/N dari pengguna saat ditanya konfirmasi */
int tulisan;

/*Fungsi ini jalan ketika user memilih 1, untuk menulis ulang seluruh data hadiah. Dengan
menggunakan mode "w" (write), otomatis isi file lama akan dibersihkan dari nol. Setelah itu, program
akan melakukan perulangan untuk menyimpan data-data baru yang di-input user ke dalam array
sekaligus mencetaknya langsung ke dalam file teks.*/
void writehadiah() {
      FILE *Thadiah= fopen("thadiah.txt", "w") ;
            printf("Jumlah hadiah : ");
            scanf("%d", &hadiah);
            for(i = 0; i < hadiah; i++){
            printf("Input hadiah ke-%d:\n", i + 1);
             printf("x, y, nama, skor1 : ");
             scanf("%d %d %s %d", &h[i].x, &h[i].y, h[i].nama, &h[i].skor);// Simpan ke array memori h[] dan langsung tulis ke file di fprintf
             fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
        }
            fprintf(Thadiah, "###");
            fclose(Thadiah); 
}
/*Sebelum data hadiah bisa diurutkan atau dipakai, program harus memuatnya terlebih dahulu dari
penyimpanan lokal. Berkas thadiah.txt dibuka dengan mode "r" (read). Variabel jumlahHadiah
di-reset ke angka 0 agar data tidak tumpang tindih. Kemudian, perulangan while yang
dikombinasikan dengan fscanf akan membaca data baris demi baris, lalu memasukkannya ke dalam
array h[] selama format datanya cocok (mengembalikan nilai 4). */
void readhadiah () {
    Hadiah temp;
    jumlahHadiah = 0;// Reset counter ke 0 sebelum membaca agar data tidak duplikat
    FILE *Thadiah = fopen("thadiah.txt", "r");
    if (Thadiah == NULL)
    {
        printf("Gagal membaca file thadiah.txt\n");
    }
    else
    {
        while (fscanf(Thadiah, "%d %d %s %d", &h[jumlahHadiah].x, &h[jumlahHadiah].y, h[jumlahHadiah].nama, &h[jumlahHadiah].skor) == 4) // disini transform h[i] ditimpa ke h[jumlahahdiah] (sebenrnya ga ditimpa sih wkwk, cuman di copy)
        { /*huruf kayak h[i] atau g[j], itu dipakai pas di dalam perulangan for buat ngebaca data satu-satu secara bergantian,
             contohnya pas program lagi nge-sort posisi koordinat hadiah atau lagi nge-render gerakan si 'O' di map dari awal 
             sampai akhir. Nah, kalau pakai h[jumlahHadiah] atau g[jumlahgerak], itu khusus dipakai pas fungsi append buat
              langsung nembak indeks paling akhir yang masih kosong, tujuannya murni untuk nyimpen data hadiah atau koordinat gerakan
               baru yang baru saja di-input sama user biar data lama nggak ketimpa.*/
            jumlahHadiah++;// Indeks array naik terus setiap kali ada data baru yang masuk

        }
        /* Algoritma Bubble Sort di bawah ini bertugas buat mengurutkan data hadiah di memori
secara menaik (ascending) berdasarkan koordinat Y, dan kalau koordinat Y-nya kembar, bakal
diurutin dari koordinat X.
Proses sorting ini penting banget biar urutan indeks di array global 'h[]' bener-bener urut.
Efeknya, pas program nge-render peta dari baris atas ke bawah, proses pemetaan posisi hadiah
jadi sinkron dan nggak acak-acakan. */ 

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

        /*Ketika proses pengurutan di dalam array memori selesai, kondisi isi berkas fisik thadiah.txt masih
blom kecetak dan dibaca. Oleh karena itu, file ditutup terlebih dahulu lalu langsung dibuka kembali
menggunakan mode "w" (write). Langkah penulisan ulang (overwrite) ini bertujuan untuk
memindahkan struktur data yang sudah rapi dari memori kembali ke storage berkas teks agar isinya
sinkron. */

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
/* Fungsi ini dipanggil pas user mau nambahin data hadiah baru tanpa ngehapus data yang lama
(mode append).
Buka file pake mode "a" bikin data baru langsung nempel di bagian paling bawah file 'thadiah.txt'.
Data yang di-input bakal disimpen ke array global 'h[]' mulai dari indeks ke-'jumlahHadiah',
terus variabel 'jumlahHadiah' langsung di-increment (ditambah 1) biar total hadiah yang aktif di
memori tetep akurat. */ 
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
        fprintf(Thadiah,"%d %d %s %d\n", h[jumlahHadiah].x, h[jumlahHadiah].y, h[jumlahHadiah].nama, h[jumlahHadiah].skor);
        jumlahHadiah++; 
    }
    fclose(Thadiah);
}
/* Fungsi untuk menampilkan judul program "LITE-O" dalam bentuk tulisan besar saat program dijalankan */
void tampilanAwal() {
    /* mengatur warna teks menjadi kuning untuk menampilkan judul besar */
    printf("\033[93m");
    printf("#      #####  #####  #####         #####\n");
    printf("#        #      #    #             #   #\n");
    printf("#        #      #    #####  #####  #   #\n");
    printf("#        #      #    #             #   #\n");
    printf("#####  #####    #    #####         #####\n");
    printf("\033[0m");  /* mengembalikan warna teks ke warna normal/default */
    printf("\033[92mTITLE LITE-O\033[0m\n\n"); /* menampilkan tulisan "TITLE LITE-O" dengan warna hijau */
}

// sebenernya kurleb sama logika nya seperti file sequential hadiah
void writegerak() {

    FILE *gerak = fopen("tgerak.txt", "w");
    printf("Jumlah gerakan : ");
    scanf("%d", &n);

    for(j = 0; j < n; j++) {
        printf("Gerakan ke-%d\n", j + 1);
        printf("x dan y : ");
        scanf("%d %d", &g[j].x, &g[j].y);
        while (g[j].x < 0 || g[j].y < 0) {
            printf("ga bisa mines\n");
            printf("x dan y : ");
            scanf("%d %d", &g[j].x, &g[j].y);
        }
        fprintf(gerak, "%d %d\n", g[j].x, g[j].y);
    }

    fprintf(gerak, "###");
    fclose(gerak);
}

void appendgerak () {

    FILE *gerak = fopen("tgerak.txt", "a");

    printf("Jumlah gerakan tambahan : ");
    scanf("%d", &n);

    for(j = 0; j < n; j++) {

        printf("Input gerakan ke-%d:\n", j + 1);
        printf("x dan y : ");
        scanf("%d %d", &g[jumlahgerak].x, &g[jumlahgerak].y);
        while(g[jumlahgerak].x < 0 || g[jumlahgerak].y < 0)
        {
            printf("ga bisa mines\n");
            printf("x dan y : ");
            scanf("%d %d", &g[jumlahgerak].x, &g[jumlahgerak].y);
        }
        fprintf(gerak,"%d %d\n", g[jumlahgerak].x, g[jumlahgerak].y);
        jumlahgerak++;
    } fclose(gerak);
}

void readgerak() {
    jumlahgerak = 0;
    FILE *gerak = fopen("tgerak.txt", "r");
    if (gerak == NULL) {
        printf("gagal membaca file gerak\n");
    }
    else {
     while(fscanf(gerak,"%d %d", &g[jumlahgerak].x, &g[jumlahgerak].y) == 2){
      jumlahgerak++;
     } fclose(gerak);
     printf("\nData gerak saat ini:\n");
     for(j = 0; j < jumlahgerak; j++)
     {
        printf("Posisi (X:%3d, Y:%3d)\n", g[j].x, g[j].y);
     }
    }
}

/* PROGRAM UTAMA */
int main() {
    /* memanggil fungsi tampilanAwal() agar judul program ditampilkan saat program pertama kali dijalankan */
    tampilanAwal();  /* panggil di sini */
    printf("Selamat Datang di Program Lite-O\n"); 
    /* meminta pengguna memasukkan ukuran papan permainan (panjang dan lebar) */
    printf("Masukan Panjang dan Lebar (pisahkan dengan spasi) : ");
    scanf("%d %d", &panjang, &lebar);
    /* membuat papan permainan berupa array 2 dimensi, sesuai ukuran panjang dan lebar yang diinput */
     char map[panjang+3][lebar+3];// karena di modul pa panji itu + 3, artinya koordinat  dari 0,0 dan atas/bawah/kiri/kanan itu kepotong

/* perulangan utama program, akan terus berjalan selama belum dihentikan (menu 4 / keluar) */
 while(1) {
        /* menampilkan daftar pilihan menu kepada pengguna */
        printf("Menu:\n");
        printf("1.Tambah hadiah\n");
        printf("2.Tambah gerak\n");
        printf("3.Simulasi Lite-O\n");  
        printf("4.Keluar\n");
        printf("Masukan Menu (1-4) : ");

        /* membaca dan menyimpan pilihan menu yang diinput oleh pengguna */
        scanf(" %d", &menu);
        
       /* jika pengguna memilih menu 1, program akan menjalankan proses untuk menambah atau mengubah data hadiah */
       if(menu == 1) { 
        readhadiah();
          printf("\n Y/N: "); //Meminta konfirmasi dari pengguna untuk menambahkan hadiah, Y/y untuk yes dan N/n untuk no
          scanf(" %c", &letter);
          if ( letter == 'Y' || letter == 'y'){
            printf("Ketik 1 untuk tambah hadiah atau angka berapapun untuk rewrite hadiah: ");
            scanf("%d", &tambahataurewrite);
            
            if (tambahataurewrite == 1) {
            /*
            nah kalo si pengguna input angka 1, maka akan masuk ke mode append
            yaitu mode yang memungkinkan kita menambah hadiah baru 
            tanpa menghilangkan hadiah yang sudah ada sebelumnya
             */
                appendhadiah();
                FILE *Thadiah= fopen("thadiah.txt", "w");
                /*
                Proses penginputan hadiah baru
                diawali dengan membuka file thadiah.txt
                kemudian melakukan input pada hadiah sesuai dengan struct
                dan diakhiri dengan menutup sekaligus menyimpan file thadiah.txt
                */

                for(i = 0; i < jumlahHadiah; i++) {
                    fprintf(Thadiah, "%d %d %s %d\n", h[i].x, h[i].y, h[i].nama, h[i].skor);
                }
                fprintf(Thadiah, "###");
                fclose(Thadiah);
                readhadiah();
            } 
            else {
            /*
            nah kalo ini kondisi dimana si pengguna tadi tuh menginputkan selain angka 1
            yang membuat program ini masuk ke mode rewrite
            yaitu menghapus semua data hadiah yang sudah ada, dan memasukkan data hadiah yang baru*/
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

        
        /* jika pengguna memilih menu 2, program akan menjalankan proses untuk menambah data gerakan pemain */
        /* Pas masuk menu 2, fungsi readgerak() dipanggil duluan buat ngasih liat riwayat gerakan saat
ini sebagai referensi.
Kalau user konfirmasi pilihan dengan input 'Y' atau 'y', alur data bakal bercabang:
- Input '1' bakal micu mode append (nambah gerak), terus array diperbarui dan ditulis ulang ke file
via mode "w".
- Input selain '1' bakal langsung masuk ke mode rewrite (bikin dari nol).
Tapi, kalau syarat huruf 'Y/y' nggak terpenuhi, perintah 'continue' bakal langsung ngelempar alur
program balik ke awal loop menu utama. */
        else if(menu == 2) {
            readgerak();
          printf("\n Y/N: ");
          scanf(" %c", &letter);
          if ( letter == 'Y' || letter == 'y'){
            printf("Ketik 1 untuk tambah gerak atau angka berapapun untuk rewrite gerak: ");
            scanf("%d", &tambahataurewrite);
            if(tambahataurewrite == 1) {
            appendgerak();
            FILE *gerak = fopen("tgerak.txt", "w");
            for(i = 0; i < jumlahgerak; i++) {
                fprintf(gerak, "%d %d\n", g[i].x, g[i].y);
             }
            fprintf(gerak, "###");
            fclose(gerak);
            readgerak();}
            else {
            writegerak();
            readgerak();
} }
    else {
        continue;
    }
}

        /* jika pengguna memilih menu 3, program akan menjalankan simulasi permainan Lite-O */
        else if(menu == 3){
j = 0;
FILE *gerak = fopen("tgerak.txt", "r");
if (gerak == NULL){
    break;}

/* inisialiasi variabel index i dengan nilai 0 untuk menghitung jumlah data hadiah yang dibaca dari file thadiah.txt */
i = 0;

/* membuka file thadiah.txt dalam mode baca ("r") */
FILE *ThadiahAwal = fopen("thadiah.txt", "r");

/* memeriksa apakah file thadiah.txt berhasil dibuka (tidak NULL) */
if (ThadiahAwal != NULL) {

    /* membaca data dari file thadiah.txt menggunakan fscanf, dan menyimpannya ke dalam array h[] sesuai dengan struktur Hadiah */
    while (fscanf(ThadiahAwal, "%d %d %s %d", &h[i].x, &h[i].y, h[i].nama, &h[i].skor) == 4) {

        /* menginisialisasi status dimakan dari hadiah yang baru dibaca menjadi 0 (belum dimakan) */
        h[i].dimakan = 0;

        /* menambah index untuk data hadiah berikutnya */
        i++;
    }

    /* menyimpan jumlah total hadiah yang berhasil dibaca dari file ke dalam variabel jumlahHadiah */
    jumlahHadiah = i;

    /* menutup file thadiah.txt setelah selesai membaca data */
    fclose(ThadiahAwal);
}
/* mengatur skor awal pemain menjadi 0 sebelum memulai simulasi permainan */
skor = 0;

/* membaca file gerak.txt untuk setiap gerakan. 
proses berlanjut selama berhasil membaca dua nilai integer */
while (fscanf(gerak,"%d %d", &g[j].x, &g[j].y) == 2 ){

    /* membersihkan layar untuk menampilkan papan permainan yang baru */
    system ("cls");

    /* perulangan untuk menggambar papan permainan dengan ukuran panjang+3 baris dan lebar+3 kolom */
        for (a = 0; a < panjang+3; a++) {
         for (b = 0; b < lebar+3; b++) {

        /* mengatur batas papan */
        if (b == 0 || b == lebar+2)
        {
            map[a][b] = '|';
        }

        /* mengatur aturan papan */
        else if (a == 0 || a == panjang+2)
        {
            map[a][b] = '-';
        }

        /* mengatur isi papan */
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
    /*
    nah ini kalo hadiahnya belum dimakan, kemudian koordinat si O nih sama kayak koordinat hadiah
    berarti si hadiah ini otomatis kayak kemakan gitu sama si O
    terus skor yang ada di hadiah itu ditambahin ke skor si O
    */
    }
}

/* gambar hadiah yang belum dimakan, ditulis sebagai nama+skor (mis. "aa5") */
for (i = 0; i < jumlahHadiah; i++) {
if (h[i].dimakan) continue; //kalo misal status hadiahnya itu udah "dimakan", maka kita lewati/continue
if (h[i].y >= 0 && h[i].y < panjang+1 && h[i].x >= 0 && h[i].x < lebar+1) { //kode buat mastiin kalo hadiah itu ga ngelewatin batas papan
    
    char tulisan[100];
    sprintf(tulisan, "%s%d", h[i].nama, h[i].skor); /* gabungkan nama dan skor jadi satu teks, contoh: "aa5" */
    for (k = 0; tulisan[k] != '\0' && (h[i].x + 1 + k) < lebar+2; k++) {
        map[h[i].y + 1][h[i].x + 1 + k] = tulisan[k]; /* tulis huruf per huruf ke map */
    }
}
}

if (g[j].y >= 0 && g[j].y < panjang+1 && g[j].x >= 0 && g[j].x < lebar+1){
map[g[j].y + 1][g[j].x + 1] = player;
}  
        /* menampilkan seluruh isi papan permainan ke layar, baris demi baris */
        for (a = 0; a < panjang + 3; a++)
        {
            for (b = 0; b < lebar + 3; b++)
            {
                /* jika posisi ini adalah posisi pemain, tampilkan dengan warna ungu */
                if (map[a][b] == player) {
                    printf("\033[95m%c \033[0m", map[a][b]); 
                }
                /* jika posisi ini adalah dinding/batas papan, tampilkan dengan warna abu-abu */
                else if (map[a][b] == '-' || map[a][b] == '|') {
                    printf("\033[90m%c \033[0m", map[a][b]); 
                }
                /* jika posisi ini bukan dinding, bukan pemain, dan bukan kosong, berarti ini hadiah, tampilkan dengan 4 warna sesuai x / a nya */
                else if (map[a][b] != ' ') { 
                    int warna = (a) % 4;
                if (warna == 0) {
                printf("\033[91m%c \033[0m", map[a][b]); // merah
                } else if (warna == 1) {
                printf("\033[92m%c \033[0m", map[a][b]); // hijau
                } else if (warna == 2) {
                printf("\033[93m%c \033[0m", map[a][b]); // kuning
                } else if (warna == 3) {
                printf("\033[96m%c \033[0m", map[a][b]); // cyan
                }
                }
                else {
                 /* jika posisi ini kosong, tampilkan spasi biasa tanpa warna */
                printf("%c ", map[a][b]);
            }
        }
            printf("\n");
    }

        printf("\nPosisi O : (%d,%d)\n", g[j].x, g[j].y); //ini buat mencetak koordinat si O secara real time
        printf("Skor O : %d\n", skor); //ini buat mencetak total skor si O

        tahan(1); //ini buat jeda 1 detik, sebelum memproses ke gerakan selanjutnya
    } 
    fclose(gerak);
}

    /* jika pengguna memilih menu 4, program akan menampilkan ucapan terima kasih lalu mengakhiri program */
    else if(menu == 4) {
            printf("\nTerima kasih telah bermain!\n");
            system("exit");
        }
        /* jika pengguna memasukkan pilihan selain 1 sampai 4, program akan menampilkan pesan pilihan tidak valid */
        else {
            printf("\nPilihan tidak valid! Silakan masukkan angka 1-4.\n");
        }
     }
    return 0;
}