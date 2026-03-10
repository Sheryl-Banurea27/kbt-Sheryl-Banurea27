#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>  

typedef struct {
    int kodeTujuan;
    char namaTujuan[20];
    long hargaReguler;
} TujuanTransportasi;

typedef struct {
    char namaLengkap[101]; 
    char nomorHP[14];     
    int tujuanDipilih;
    int jumlahKursi;
    char tanggalKeberangkatan[11]; 
    char jenisPembayaran[10];      
    long totalHarga;
    char tipeTiket[10]; 
} DataPemesanan;


void tampilkanDaftarTujuan(TujuanTransportasi tujuan[], int ukuran);
int getInputTujuan(int ukuran);
int getInputJumlahKursi();
void getInputTanggal(char *tanggal);
void getInputNama(char *nama);
void getInputNomorHP(char *hp);
void getInputJenisPembayaran(char *pembayaran);
void tampilkanRingkasanPemesanan(DataPemesanan data, TujuanTransportasi tujuan[], int ukuran);
long hitungTotalHarga(int kodeTujuan, int jumlahKursi, char *tipeTiket, TujuanTransportasi tujuan[], int ukuran);
char* pilihTipeTiket();
int isValidDate(const char *dateStr);

int main() {
    
    TujuanTransportasi daftarTujuan[] = {
        {1, "Medan", 100000},
        {2, "Siantar", 90000},
        {3, "Sibolga", 95000},
        {4, "Sidikalang", 100000},
        {5, "Samosir", 95000}
    };
    int jumlahTujuan = sizeof(daftarTujuan) / sizeof(daftarTujuan[0]);

    DataPemesanan pemesanan;

    printf("=======================================\n");
    printf(" SISTEM TIKETING KBT (Komuter Bus Terbaik)\n");
    printf("=======================================\n");

    
    getInputNama(pemesanan.namaLengkap);

  
    getInputNomorHP(pemesanan.nomorHP);

    tampilkanDaftarTujuan(daftarTujuan, jumlahTujuan);

    pemesanan.tujuanDipilih = getInputTujuan(jumlahTujuan);

    pemesanan.jumlahKursi = getInputJumlahKursi();
   
    strcpy(pemesanan.tipeTiket, pilihTipeTiket());

    getInputTanggal(pemesanan.tanggalKeberangkatan);

    getInputJenisPembayaran(pemesanan.jenisPembayaran);

    pemesanan.totalHarga = hitungTotalHarga(pemesanan.tujuanDipilih, pemesanan.jumlahKursi, pemesanan.tipeTiket, daftarTujuan, jumlahTujuan);

    printf("\n--- Proses Pemesanan Selesai ---\n");

    tampilkanRingkasanPemesanan(pemesanan, daftarTujuan, jumlahTujuan);

    return 0;
}

void tampilkanDaftarTujuan(TujuanTransportasi tujuan[], int ukuran) {
    printf("\n--- Daftar Tujuan KBT ---\n");
    printf("Kode | Tujuan     | Harga Reguler\n");
    printf("----------------------------------\n");
    for (int i = 0; i < ukuran; i++) {
        printf("%-4d | %-10s | Rp %ld\n", tujuan[i].kodeTujuan, tujuan[i].namaTujuan, tujuan[i].hargaReguler);
    }
    printf("----------------------------------\n");
}

int getInputTujuan(int ukuran) {
    int pilihan;
    int valid = 0;
    while (!valid) {
        printf("Masukkan kode tujuan (1-%d): ", ukuran);
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Mohon masukkan angka.\n");
            while (getchar() != '\n'); 
        } else if (pilihan < 1 || pilihan > ukuran) {
            printf("Kode tujuan tidak valid. Mohon pilih antara 1 dan %d.\n", ukuran);
        } else {
            valid = 1;
        }
    }
    while (getchar() != '\n'); 
    return pilihan;
}

int getInputJumlahKursi() {
    int jumlah;
    int valid = 0;
    while (!valid) {
        printf("Masukkan jumlah kursi (maksimal 10): ");
        if (scanf("%d", &jumlah) != 1) {
            printf("Input tidak valid. Mohon masukkan angka.\n");
            while (getchar() != '\n'); 
        } else if (jumlah < 1 || jumlah > 10) {
            printf("Jumlah kursi tidak valid. Maksimal 10 kursi per pemesanan.\n");
        } else {
            valid = 1;
        }
    }
    while (getchar() != '\n'); 
    return jumlah;
}
void getInputTanggal(char *tanggal) {
    int valid = 0;
    while (!valid) {
        printf("Masukkan tanggal keberangkatan (DD-MM-YYYY): ");
        fgets(tanggal, 11, stdin); 
        tanggal[strcspn(tanggal, "\n")] = 0; 

        if (strlen(tanggal) == 10 && isValidDate(tanggal)) {
            valid = 1;
        } else {
            printf("Format tanggal tidak valid atau tanggal tidak masuk akal. Mohon gunakan DD-MM-YYYY.\n");
        }
    }
}

int isValidDate(const char *dateStr) {
    if (strlen(dateStr) != 10) return 0;
    if (dateStr[2] != '-' || dateStr[5] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(dateStr[i])) return 0;
    }

    int day = atoi(dateStr);
    int month = atoi(dateStr + 3);
    int year = atoi(dateStr + 6);

    if (year < 1900 || year > 2100) return 0; 
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;


    if (month == 2) {
        int isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (28 + isLeap)) return 0;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return 0;
    }
    return 1;
}

void getInputNama(char *nama) {
    printf("Masukkan nama lengkap (maksimal 100 karakter): ");
    fgets(nama, 101, stdin);
    nama[strcspn(nama, "\n")] = 0; 
    while (strlen(nama) == 0 || strlen(nama) > 100) {
        printf("Nama lengkap tidak boleh kosong dan maksimal 100 karakter. Masukkan lagi: ");
        fgets(nama, 101, stdin);
        nama[strcspn(nama, "\n")] = 0;
    }
}

void getInputNomorHP(char *hp) {
    int valid = 0;
    while (!valid) {
        printf("Masukkan nomor HP (maksimal 13 karakter): ");
        fgets(hp, 14, stdin);
        hp[strcspn(hp, "\n")] = 0; 

        if (strlen(hp) > 0 && strlen(hp) <= 13) {
            int is_digit = 1;
            for (int i = 0; i < strlen(hp); i++) {
                if (!isdigit(hp[i])) {
                    is_digit = 0;
                    break;
                }
            }
            if (is_digit) {
                valid = 1;
            } else {
                printf("Nomor HP hanya boleh berisi angka. Masukkan lagi: ");
            }
        } else {
            printf("Nomor HP tidak boleh kosong dan maksimal 13 karakter. Masukkan lagi: ");
        }
    }
}

void getInputJenisPembayaran(char *pembayaran) {
    int valid = 0;
    while (!valid) {
        printf("Pilih jenis pembayaran (cash/transfer): ");
        fgets(pembayaran, 10, stdin);
        pembayaran[strcspn(pembayaran, "\n")] = 0; 


        for(int i = 0; pembayaran[i]; i++){
            pembayaran[i] = tolower(pembayaran[i]);
        }

        if (strcmp(pembayaran, "cash") == 0 || strcmp(pembayaran, "transfer") == 0) {
            valid = 1;
        } else {
            printf("Jenis pembayaran tidak valid. Mohon masukkan 'cash' atau 'transfer'.\n");
        }
    }
}


char* pilihTipeTiket() {
    char pilihan[10];
    while (1) {
        printf("Pilih tipe tiket (Reguler/Eksklusif): ");
        fgets(pilihan, sizeof(pilihan), stdin);
        pilihan[strcspn(pilihan, "\n")] = 0;

        for(int i = 0; pilihan[i]; i++){
            pilihan[i] = tolower(pilihan[i]);
        }

        if (strcmp(pilihan, "reguler") == 0) {
            return "Reguler";
        } else if (strcmp(pilihan, "eksklusif") == 0) {
            return "Eksklusif";
        } else {
            printf("Pilihan tidak valid. Mohon masukkan 'Reguler' atau 'Eksklusif'.\n");
        }
    }
}

long hitungTotalHarga(int kodeTujuan, int jumlahKursi, char *tipeTiket, TujuanTransportasi tujuan[], int ukuran) {
    long hargaDasar = 0;
    for (int i = 0; i < ukuran; i++) {
        if (tujuan[i].kodeTujuan == kodeTujuan) {
            hargaDasar = tujuan[i].hargaReguler;
            break;
        }
    }

    if (strcmp(tipeTiket, "Eksklusif") == 0) {
        hargaDasar += 20000;
    }

    return hargaDasar * jumlahKursi;
}


void tampilkanRingkasanPemesanan(DataPemesanan data, TujuanTransportasi tujuan[], int ukuran) {
    char namaTujuan[20];
    for (int i = 0; i < ukuran; i++) {
        if (tujuan[i].kodeTujuan == data.tujuanDipilih) {
            strcpy(namaTujuan, tujuan[i].namaTujuan);
            break;
        }
    }

    printf("\n--- Detail Pemesanan Tiket KBT ---\n");
    printf("Nama Lengkap        : %s\n", data.namaLengkap);
    printf("Nomor HP            : %s\n", data.nomorHP);
    printf("Tujuan              : %s (Kode: %d)\n", namaTujuan, data.tujuanDipilih);
    printf("Jumlah Kursi        : %d\n", data.jumlahKursi);
    printf("Tipe Tiket          : %s\n", data.tipeTiket);
    printf("Tanggal Keberangkatan: %s\n", data.tanggalKeberangkatan);
    printf("Jenis Pembayaran    : %s\n", data.jenisPembayaran);
    printf("----------------------------------\n");
    printf("TOTAL HARGA         : Rp %ld\n", data.totalHarga);
    printf("===================================\n");
}
