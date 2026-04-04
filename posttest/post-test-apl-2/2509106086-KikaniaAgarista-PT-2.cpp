#include <iostream>
#include <string>
using namespace std;


struct Tanaman {
    string namaTanaman;
    string jenisTanaman;
    int hariTerakhirSiram;
    bool statusHidup;
};

struct User {
    string namaUser;
    string nimUser;
    Tanaman daftarTanaman[100];
    int jumlahTanaman;
    bool statusAktif;
};

int main() {
    User dataUser[50];
    int jumlahUser = 0;
    int indexUserAktif = -1;
    int percobaanLogin = 0;
    string inputNama, inputNIM;
    bool programBerjalan = true;
    bool sudahLogin = false;


    while (programBerjalan) {
        if (!sudahLogin) {  
            cout << "\n=== LOGIN ===" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilihan: ";
            int pilihan; 
            cin >> pilihan;

            if (pilihan == 1) { 
                if (jumlahUser == 0) {
                    cout << "Belum ada user. Silakan Register." << endl;
                } else {
                    cin.ignore();
                    cout << "Nama: "; 
                    getline(cin, inputNama);
                    cout << "NIM: "; 
                    getline(cin, inputNIM);

                    bool ketemu = false;

                    for (int i = 0; i < jumlahUser; i++) {
                        if (dataUser[i].statusAktif && 
                            dataUser[i].namaUser == inputNama && 
                            dataUser[i].nimUser == inputNIM) {
                            
                            indexUserAktif = i;
                            sudahLogin = true;
                            percobaanLogin = 0;
                            ketemu = true;
                            cout << "Login Berhasil!" << endl;
                            break;
                        }
                    }

                    if (!ketemu) {
                        percobaanLogin++;
                        cout << "Salah! Percobaan " << percobaanLogin << "/3" << endl;
                        if (percobaanLogin >= 3) {
                            cout << "Program berhenti." << endl;
                            programBerjalan = false;
                        }
                    }
                }
            }
            else if (pilihan == 2) { 
                if (jumlahUser < 50) {
                    cin.ignore();
                    cout << "Nama: "; 
                    getline(cin, dataUser[jumlahUser].namaUser);
                    cout << "NIM: "; 
                    getline(cin, dataUser[jumlahUser].nimUser);
                    
                    if (!dataUser[jumlahUser].namaUser.empty() && 
                        !dataUser[jumlahUser].nimUser.empty()) {
                        
                        dataUser[jumlahUser].jumlahTanaman = 0;
                        dataUser[jumlahUser].statusAktif = true;
                        jumlahUser++;
                        cout << "Register Berhasil!" << endl;
                    } else {
                        cout << "Jangan kosong!" << endl;
                    }
                } else {
                    cout << "User penuh." << endl;
                }
            }
            else if (pilihan == 3) { 
                programBerjalan = false;
            }
        } 

        else {
            cout << "\n=== MENU - " << dataUser[indexUserAktif].namaUser << " ===" << endl;
            cout << "1. Tambah tanaman" << endl;
            cout << "2. Lihat tanaman" << endl;
            cout << "3. Update tanaman" << endl;
            cout << "4. Hapus tanaman" << endl;
            cout << "5. Logout" << endl;
            cout << "Pilihan: ";
            int pilihan; 
            cin >> pilihan;

            if (pilihan == 1) { 
                if (dataUser[indexUserAktif].jumlahTanaman < 100) {
                    int index = dataUser[indexUserAktif].jumlahTanaman;
                    cin.ignore();
                    cout << "Nama Tanaman: "; 
                    getline(cin, dataUser[indexUserAktif].daftarTanaman[index].namaTanaman);
                    cout << "Jenis: "; 
                    getline(cin, dataUser[indexUserAktif].daftarTanaman[index].jenisTanaman);
                    cout << "Hari Siram (1-7): "; 
                    cin >> dataUser[indexUserAktif].daftarTanaman[index].hariTerakhirSiram;
                    cout << "Hidup? (1=Ya, 0=Tidak): "; 
                    cin >> dataUser[indexUserAktif].daftarTanaman[index].statusHidup;
                    
                    dataUser[indexUserAktif].jumlahTanaman++;
                    cout << "Berhasil!" << endl;
                } else {
                    cout << "Penuh!" << endl;
                }   
            }
            else if (pilihan == 2) { 
                if (dataUser[indexUserAktif].jumlahTanaman == 0) {
                    cout << "Kosong." << endl;
                } else {
                    cout << "No|Nama|Jenis|Siram|Status" << endl;
                    
                    for (int i = 0; i < dataUser[indexUserAktif].jumlahTanaman; i++) {
                        cout << i + 1 << "|" 
                             << dataUser[indexUserAktif].daftarTanaman[i].namaTanaman << "|"
                             << dataUser[indexUserAktif].daftarTanaman[i].jenisTanaman << "|"
                             << dataUser[indexUserAktif].daftarTanaman[i].hariTerakhirSiram << "|"
                             << (dataUser[indexUserAktif].daftarTanaman[i].statusHidup ? "Hidup" : "Mati") 
                             << endl;
                    }
                }
            }
            else if (pilihan == 3) { 
                cout << "Nomor tanaman: "; 
                cin >> pilihan;
                if (pilihan > 0 && pilihan <= dataUser[indexUserAktif].jumlahTanaman) {
                    int index = pilihan - 1;
                    cout << "Hari Siram Baru: "; 
                    cin >> dataUser[indexUserAktif].daftarTanaman[index].hariTerakhirSiram;
                    cout << "Status Baru (1=Ya,0=Tidak): "; 
                    cin >> dataUser[indexUserAktif].daftarTanaman[index].statusHidup;
                    cout << "Update OK!" << endl;
                } else {
                    cout << "Tidak valid." << endl;
                }
            }
            else if (pilihan == 4) {
                cout << "Nomor tanaman: "; 
                cin >> pilihan;
                if (pilihan > 0 && pilihan <= dataUser[indexUserAktif].jumlahTanaman) {
                    cout << "Yakin? (1=Ya,0=Tidak): "; 
                    int konfirmasi; 
                    cin >> konfirmasi;
                    if (konfirmasi == 1) {
                        
                        for (int i = pilihan - 1; i < dataUser[indexUserAktif].jumlahTanaman - 1; i++) {
                            dataUser[indexUserAktif].daftarTanaman[i] = 
                            dataUser[indexUserAktif].daftarTanaman[i + 1];
                        }
                        dataUser[indexUserAktif].jumlahTanaman--;
                        cout << "Hapus OK!" << endl;
                    }
                } else {
                    cout << "Tidak valid." << endl;
                }
            }
            else if (pilihan == 5) { 
                sudahLogin = false;
                indexUserAktif = -1;
                cout << "Logout." << endl;
            }
        }
    }

    cout << "\n=== SELESAI ===" << endl;
    return 0;
}