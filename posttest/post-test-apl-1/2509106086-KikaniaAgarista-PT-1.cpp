#include <iostream>
using namespace std; 

int main() {
    string nama;
    string password;
    string passwordBenar = "086";
    int percobaan = 0;

    cout << "======================================"<<endl;
    cout << "         PROGRAM KONVERSI PANJANG      "<<endl;
    cout << "======================================"<<endl;

    while (percobaan < 3) {
        cout << "======================================"<<endl;
        cout << "            LOGIN SISTEM              "<<endl;
        cout << "======================================"<<endl;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, nama);
        cout << "Masukkan Password: ";
        cin >> password;

        if (password == passwordBenar) {
            cout << "\nLogin Berhasil! Selamat datang, " << nama << "!"<<endl;
            break;
        } else {
            percobaan++;
            cout << "Password salah! Percobaan ke-" << percobaan <<endl;
        } 
    }
    if (percobaan == 3) {
        cout << "Password salah! Sisa percobaan: " << 3 - percobaan <<endl;
        return 0;
    }

    //====MENU UTMA====//
    int pilihan;
    double nilai;

    do {
        cout << "======================================"<<endl;
        cout << "         MENU KONVERSI PANJANG        "<<endl;
        cout << "======================================"<<endl;
        cout << "1. Konversi Centimeter ke Meter dan Kilometer"<<endl;
        cout << "2. Konversi Meter ke Centimeter dan Kilometer"<<endl;
        cout << "3. Konversi Kilometer ke Meter dan Centimeter"<<endl;
        cout << "4. Keluar"<<endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                cout << "Masukkan nilai dalam Centimeter: ";
                cin >> nilai;
                cout << "Hasil konversi: " << nilai / 100 << " Meter, " << nilai / 100000 << " Kilometer"<<endl;
                break;
            case 2:
                cout << "Masukkan nilai dalam Meter: ";
                cin >> nilai;
                cout << "Hasil konversi: " << nilai * 100 << " Centimeter, " << nilai / 1000 << " Kilometer"<<endl;
                break;
            case 3:
                cout << "Masukkan nilai dalam Kilometer: ";
                cin >> nilai;
                cout << "Hasil konversi: " << nilai * 1000 << " Meter, " << nilai * 100000 << " Centimeter"<<endl;
                break;
            case 4:
                cout << "Terima kasih telah menggunakan program ini!"<<endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan pilih menu yang tersedia."<<endl;
        }

    } while (pilihan != 4);
    return 0;
}

      