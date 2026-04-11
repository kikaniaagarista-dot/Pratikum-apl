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
    Tanaman* daftarTanaman; 
    int jumlahTanaman;
    bool statusAktif;
};

void sortNamaBubbleDesc(Tanaman arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].namaTanaman < arr[j + 1].namaTanaman) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortHariSelectionAsc(Tanaman arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indeksMin = i; 
        for (int j = i + 1; j < n; j++) {
            if (arr[j].hariTerakhirSiram < arr[indeksMin].hariTerakhirSiram) {
                indeksMin = j;
            }
        }
        if (indeksMin != i) {
            swap(arr[i], arr[indeksMin]);
        }
    }
}

void sortStatusInsertion(Tanaman arr[], int n) {
    for (int i = 1; i < n; i++) {
        Tanaman key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].statusHidup == false && key.statusHidup == true) {
            arr[j + 1] = arr[j]; 
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int loginUser(User* dataUser, int jumlahUser, string nama, string nim) {
    for (int i = 0; i < jumlahUser; i++) {
        if ((dataUser + i)->statusAktif &&
            (dataUser + i)->namaUser == nama &&
            (dataUser + i)->nimUser == nim) {
            return i; 
        }
    }
    return -1; 
}

void registerUser(User* dataUser, int &jumlahUser) { 
    if (jumlahUser >= 50) {
        cout << "User penuh!" << endl;
        return;  
    }

    cin.ignore();
    cout << "Nama: ";
    getline(cin, (dataUser + jumlahUser)->namaUser);

    cout << "NIM: ";
    getline(cin, (dataUser + jumlahUser)->nimUser);

    (dataUser + jumlahUser)->daftarTanaman = new Tanaman[100];  
    (dataUser + jumlahUser)->jumlahTanaman = 0;
    (dataUser + jumlahUser)->statusAktif = true;

    jumlahUser++; 
    cout << "Register berhasil!" << endl;
}

void tambahTanaman(User* user) { 
    if (user->jumlahTanaman >= 100) {
        cout << "Tanaman penuh!" << endl;
        return;  
    }

    int index = user->jumlahTanaman;

    cin.ignore();
    cout << "Nama Tanaman: ";
    getline(cin, (user->daftarTanaman + index)->namaTanaman);

    cout << "Jenis: ";
    getline(cin, (user->daftarTanaman + index)->jenisTanaman);

    cout << "Hari Siram (1-7): ";
    cin >> (user->daftarTanaman + index)->hariTerakhirSiram;

    cout << "Status Hidup (1=Ya, 0=Tidak): ";
    cin >> (user->daftarTanaman + index)->statusHidup;

    user->jumlahTanaman++;
    cout << "Tanaman berhasil ditambahkan!" << endl;
}

void lihatTanaman(User* user) { 
    if (user->jumlahTanaman == 0) {
        cout << "Belum ada tanaman." << endl;
        return;  
    }

    cout << "\nNo | Nama           | Jenis          | Siram | Status" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < user->jumlahTanaman; i++) {
        cout << (i + 1) << "  | "
             << (user->daftarTanaman + i)->namaTanaman << " | "
             << (user->daftarTanaman + i)->jenisTanaman << " | "
             << (user->daftarTanaman + i)->hariTerakhirSiram << "     | "
             << ((user->daftarTanaman + i)->statusHidup ? "Hidup" : "Mati")
             << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}

void updateTanaman(User* user) { 
    int nomor;
    cout << "Nomor tanaman: ";
    cin >> nomor;

    if (nomor <= 0 || nomor > user->jumlahTanaman) {
        cout << "Tidak valid!" << endl;
        return; 
    }

    int index = nomor - 1;
    cout << "Hari Siram Baru: ";
    cin >> (user->daftarTanaman + index)->hariTerakhirSiram;

    cout << "Status Hidup Baru (1=Ya, 0=Tidak): ";
    cin >> (user->daftarTanaman + index)->statusHidup;

    cout << "Update berhasil!" << endl;
}

void hapusTanaman(User* user) { 
    int nomor;
    cout << "Nomor tanaman: ";
    cin >> nomor;

    if (nomor <= 0 || nomor > user->jumlahTanaman) {
        cout << "Tidak valid!" << endl;
        return;  
    }

    for (int i = nomor - 1; i < user->jumlahTanaman - 1; i++) {
        *(user->daftarTanaman + i) = *(user->daftarTanaman + i + 1);
    }
    user->jumlahTanaman--;
    cout << "Tanaman berhasil dihapus!" << endl;
}

void cleanupMemory(User* dataUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser; i++) {
        if ((dataUser + i)->daftarTanaman != nullptr) {
            delete[] (dataUser + i)->daftarTanaman; 
        }
    }
}

int main() {
    User* dataUser = new User[50]; 
    int jumlahUser = 0;
    int indexUserAktif = -1;

    bool sudahLogin = false;
    bool program = true;

    for (int i = 0; i < 50; i++) {
        (dataUser + i)->daftarTanaman = nullptr;
        (dataUser + i)->statusAktif = false;
    }

    while (program) {
        if (!sudahLogin) {
            cout << "\n=== LOGIN MENU ===" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilihan: ";

            int pilih;
            cin >> pilih;

            if (pilih == 1) {
                string nama, nim;
                cin.ignore();
                cout << "Nama: ";
                getline(cin, nama);
                cout << "NIM: ";
                getline(cin, nim);

                indexUserAktif = loginUser(dataUser, jumlahUser, nama, nim);
                if (indexUserAktif != -1) {
                    sudahLogin = true;
                    cout << "Login berhasil!" << endl;
                } else {
                    cout << "Login gagal!" << endl;
                }
            } else if (pilih == 2) {
                registerUser(dataUser, jumlahUser);  
            } else if (pilih == 3) {
                program = false;
            }
        } else {
            cout << "\n=== MENU TANAMAN ===" << endl;
            cout << "1. Tambah" << endl;
            cout << "2. Lihat" << endl;
            cout << "3. Update" << endl;
            cout << "4. Hapus" << endl;
            cout << "5. Logout" << endl;
            cout << "6. Urutkan" << endl;
            cout << "Pilihan: ";

            int pilih;
            cin >> pilih;

            if (pilih == 1) {
                tambahTanaman(&dataUser[indexUserAktif]);  
            } else if (pilih == 2) {
                lihatTanaman(&dataUser[indexUserAktif]);  
            } else if (pilih == 3) {
                updateTanaman(&dataUser[indexUserAktif]);  
            } else if (pilih == 4) {
                hapusTanaman(&dataUser[indexUserAktif]);  
            } else if (pilih == 5) {
                sudahLogin = false;
                indexUserAktif = -1;
                cout << "Logout berhasil." << endl;
            } 

            else if (pilih == 6) {
                cout << "\nPilih metode sorting:" << endl;
                cout << "1. Nama Tanaman (Huruf Descending: Z s/d A) [Bubble Sort]" << endl;
                cout << "2. Hari Terakhir Siram (Angka Ascending: Kecil s/d Besar) [Selection Sort]" << endl;
                cout << "3. Status Hidup (Hidup diutamakan s/d Mati) [Insertion Sort]" << endl;
                cout << "Pilihan: ";
                
                int subPilih;
                cin >> subPilih;

                Tanaman* arr = dataUser[indexUserAktif].daftarTanaman;
                int count = dataUser[indexUserAktif].jumlahTanaman;

                if (count < 2) {
                    cout << "Data kurang dari 2, tidak perlu diurutkan." << endl;
                    continue;
                }

                if (subPilih == 1) {
                    sortNamaBubbleDesc(arr, count);
                    cout << "Diurutkan dengan Bubble Sort (Nama Descending)!" << endl;
                } else if (subPilih == 2) {
                    sortHariSelectionAsc(arr, count);
                    cout << "Diurutkan dengan Selection Sort (Hari Siram Ascending)!" << endl;
                } else if (subPilih == 3) {
                    sortStatusInsertion(arr, count);
                    cout << "Diurutkan dengan Insertion Sort (Status Hidup)!" << endl;
                } else {
                    cout << "Pilihan tidak valid." << endl;
                }
                
                if (subPilih >= 1 && subPilih <= 3) {
                    lihatTanaman(&dataUser[indexUserAktif]);
                }
            }
        }
    }

    cleanupMemory(dataUser, jumlahUser);
    delete[] dataUser; 

    cout << "\nProgram selesai." << endl;
    return 0;  
}