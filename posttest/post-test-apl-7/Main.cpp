#include <iostream>
#include <string>
#include <algorithm>
#include "TANAMAN_LIB.H"
using namespace std;

// ========== IMPLEMENTASI FUNGSI ==========

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

int linearSearchNama(Tanaman* arr, int n, string target) {
    for (int i = 0; i < n; i++) {
        if ((arr + i)->namaTanaman == target) {
            return i; 
        }
    }
    return -1; 
}

int binarySearchHari(Tanaman* arr, int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if ((arr + mid)->hariTerakhirSiram == target) {
            return mid;
        } else if ((arr + mid)->hariTerakhirSiram < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
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
    try {
        if (jumlahUser >= 50) {
            throw OutOfRangeException("User penuh! Maksimal 50 user.");
        }
        
        cin.ignore();
        cout << "Nama: ";
        string nama;
        getline(cin, nama);
        if (nama.empty()) {
            throw InvalidInputException("Nama tidak boleh kosong!");
        }
        
        cout << "NIM: ";
        string nim;
        getline(cin, nim);
        if (nim.empty()) {
            throw InvalidInputException("NIM tidak boleh kosong!");
        }
        
        (dataUser + jumlahUser)->daftarTanaman = new Tanaman[100];
        (dataUser + jumlahUser)->namaUser = nama;
        (dataUser + jumlahUser)->nimUser = nim;
        (dataUser + jumlahUser)->jumlahTanaman = 0;
        (dataUser + jumlahUser)->statusAktif = true;
        jumlahUser++; 
        
        cout << " Register berhasil!" << endl;
        
    } catch (const bad_alloc&) {
        throw MemoryException("Gagal alokasi memori untuk user baru!");
    }
}

void tambahTanaman(User* user) {
    try {
        if (user == nullptr) {
            throw InvalidInputException("User tidak valid!");
        }
        
        if (user->jumlahTanaman >= 100) {
            throw OutOfRangeException("Kapasitas tanaman penuh (maks 100)!");
        }
        
        int index = user->jumlahTanaman;
        cin.ignore();
        
        cout << "Nama Tanaman: ";
        string nama;
        getline(cin, nama);
        if (nama.empty()) {
            throw InvalidInputException("Nama tanaman tidak boleh kosong!");
        }
        (user->daftarTanaman + index)->namaTanaman = nama;
        
        cout << "Jenis: ";
        string jenis;
        getline(cin, jenis);
        if (jenis.empty()) {
            throw InvalidInputException("Jenis tanaman tidak boleh kosong!");
        }
        (user->daftarTanaman + index)->jenisTanaman = jenis;
        
        cout << "Hari Siram (1-7): ";
        int hari;
        cin >> hari;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        if (hari < 1 || hari > 7) {
            throw OutOfRangeException("Hari siram harus antara 1-7!");
        }
        (user->daftarTanaman + index)->hariTerakhirSiram = hari;
        
        cout << "Status Hidup (1=Ya, 0=Tidak): ";
        int status;
        cin >> status;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        if (status != 0 && status != 1) {
            throw OutOfRangeException("Status hanya boleh 0 atau 1!");
        }
        (user->daftarTanaman + index)->statusHidup = (status == 1);
        
        user->jumlahTanaman++;
        cout << " Tanaman berhasil ditambahkan!" << endl;
        
    } catch (const bad_alloc&) {
        cout << " Memory Error: Gagal alokasi memori!" << endl;
    } catch (const exception& e) {
        cout << " Error: " << e.what() << endl;
    }
}

void lihatTanaman(User* user) {
    try {
        if (user == nullptr) {
            throw InvalidInputException("User tidak valid!");
        }
        
        if (user->jumlahTanaman == 0) {
            cout << " Belum ada tanaman." << endl;
            return;  
        }
        
    cout << "\nNo | Nama           | Jenis          | Siram | Status" << endl;
    cout << "-------------------------------------------------------" << endl;
        
        for (int i = 0; i < user->jumlahTanaman; i++) {
            cout << "│ " << (i + 1);
            cout.width(2); cout << "│ ";
            cout.width(14); cout << left << (user->daftarTanaman + i)->namaTanaman << " │ ";
            cout.width(14); cout << left << (user->daftarTanaman + i)->jenisTanaman << " │ ";
            cout.width(5); cout << right << (user->daftarTanaman + i)->hariTerakhirSiram << " │ ";
            cout << ((user->daftarTanaman + i)->statusHidup ? "Hidup  │" : "Mati   │") << endl;
        }
        cout << "=======================================================" << endl;
        
    } catch (const exception& e) {
        cout << " Error: " << e.what() << endl;
    }
}

void updateTanaman(User* user) {
    try {
        if (user == nullptr) {
            throw InvalidInputException("User tidak valid!");
        }
        
        if (user->jumlahTanaman == 0) {
            cout << " Belum ada tanaman untuk diupdate!" << endl;
            return;
        }
        
        int nomor;
        cout << "Nomor tanaman: ";
        cin >> nomor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        
        if (nomor <= 0 || nomor > user->jumlahTanaman) {
            throw OutOfRangeException("Nomor tidak valid! Pilih 1-" + to_string(user->jumlahTanaman));
        }
        
        int index = nomor - 1;
        
        cout << "Hari Siram Baru (1-7): ";
        int hari;
        cin >> hari;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        if (hari < 1 || hari > 7) {
            throw OutOfRangeException("Hari siram harus antara 1-7!");
        }
        (user->daftarTanaman + index)->hariTerakhirSiram = hari;
        
        cout << "Status Hidup Baru (1=Ya, 0=Tidak): ";
        int status;
        cin >> status;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        if (status != 0 && status != 1) {
            throw OutOfRangeException("Status hanya boleh 0 atau 1!");
        }
        (user->daftarTanaman + index)->statusHidup = (status == 1);
        
        cout << " Update berhasil!" << endl;
        
    } catch (const exception& e) {
        cout << " Error: " << e.what() << endl;
    }
}

void hapusTanaman(User* user) {
    try {
        if (user == nullptr) {
            throw InvalidInputException("User tidak valid!");
        }
        
        if (user->jumlahTanaman == 0) {
            cout << " Belum ada tanaman untuk dihapus!" << endl;
            return;
        }
        
        int nomor;
        cout << "Nomor tanaman: ";
        cin >> nomor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInputException("Input harus berupa angka!");
        }
        
        if (nomor <= 0 || nomor > user->jumlahTanaman) {
            throw OutOfRangeException("Nomor tidak valid! Pilih 1-" + to_string(user->jumlahTanaman));
        }
        
        for (int i = nomor - 1; i < user->jumlahTanaman - 1; i++) {
            *(user->daftarTanaman + i) = *(user->daftarTanaman + i + 1);
        }
        user->jumlahTanaman--;
        cout << " Tanaman berhasil dihapus!" << endl;
        
    } catch (const exception& e) {
        cout << " Error: " << e.what() << endl;
    }
}

void cleanupMemory(User* dataUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser; i++) {
        if ((dataUser + i)->daftarTanaman != nullptr) {
            delete[] (dataUser + i)->daftarTanaman;
        }
    }
}

// ================= MAIN =================
int main() {
    try {
        User* dataUser = new User[50]; 
        int jumlahUser = 0;
        int indexUserAktif = -1;
        bool sudahLogin = false;
        bool program = true;

        for (int i = 0; i < 50; i++) {
            (dataUser + i)->daftarTanaman = nullptr;
            (dataUser + i)->statusAktif = false;
        }


        cout << "===== SISTEM PENGELOLAAN TANAMAN =====" << endl;

        while (program) {
            try {
                if (!sudahLogin) {
                    cout << "=====LOGIN MENU=====" << endl;
                    cout << " 1. Login              " << endl;
                    cout << " 2. Register           " << endl;
                    cout << " 3. Keluar             " << endl;

                    cout << "Pilihan: ";
                    
                    int pilih;
                    cin >> pilih;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        throw InvalidInputException("Pilihan harus angka!");
                    }
                    
                    if (pilih < 1 || pilih > 3) {
                        throw OutOfRangeException("Pilihan hanya 1-3!");
                    }

                    if (pilih == 1) {
                        string nama, nim;
                        cin.ignore();
                        cout << "Nama: "; getline(cin, nama);
                        cout << "NIM: "; getline(cin, nim);
                        indexUserAktif = loginUser(dataUser, jumlahUser, nama, nim);
                        if (indexUserAktif != -1) {
                            sudahLogin = true;
                            cout << " Login berhasil! Selamat datang, " << nama << endl;
                        } else {
                            cout << " Login gagal! User tidak ditemukan." << endl;
                        }
                    } else if (pilih == 2) {
                        registerUser(dataUser, jumlahUser);  
                    } else if (pilih == 3) {
                        program = false;
                        cout << " Terima kasih telah menggunakan program ini!" << endl;
                    }
                    
                } else {

                    cout << "=====MENU TANAMAN=====" << endl;
                    cout << "  1. Tambah Tanaman          " << endl;
                    cout << "  2. Lihat Tanaman           " << endl;
                    cout << "  3. Update Tanaman          " << endl;
                    cout << "  4. Hapus Tanaman           " << endl;
                    cout << "  5. Logout                  " << endl;
                    cout << "  6. Urutkan Tanaman         " << endl;
                    cout << "  7. Cari Tanaman            " << endl;
                    cout << "Pilihan: ";
                    
                    int pilih;
                    cin >> pilih;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        throw InvalidInputException("Pilihan harus angka!");
                    }
                    
                    if (pilih < 1 || pilih > 7) {
                        throw OutOfRangeException("Pilihan hanya 1-7!");
                    }

                    if (pilih == 1) tambahTanaman(&dataUser[indexUserAktif]);  
                    else if (pilih == 2) lihatTanaman(&dataUser[indexUserAktif]);  
                    else if (pilih == 3) updateTanaman(&dataUser[indexUserAktif]);  
                    else if (pilih == 4) hapusTanaman(&dataUser[indexUserAktif]);  
                    else if (pilih == 5) {
                        sudahLogin = false;
                        indexUserAktif = -1;
                        cout << " Logout berhasil." << endl;
                    } 
                    else if (pilih == 6) {
                        cout << "=====URUTKAN TANAMAN=====" << endl;
                        cout << " 1. Nama Tanaman (Z-A) [Bubble Sort]   " << endl;
                        cout << " 2. Hari Siram (Kecil-Besar) [Select]  " << endl;
                        cout << " 3. Status Hidup (Hidup dulu) [Insert] " << endl;
                        cout << "Pilihan: ";
                        
                        int subPilih;
                        cin >> subPilih;
                        
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw InvalidInputException("Pilihan harus angka!");
                        }
                        
                        if (subPilih < 1 || subPilih > 3) {
                            throw OutOfRangeException("Pilihan hanya 1-3!");
                        }

                        Tanaman* arr = dataUser[indexUserAktif].daftarTanaman;
                        int count = dataUser[indexUserAktif].jumlahTanaman;
                        
                        if (count < 2) { 
                            cout << "  Data kurang dari 2, tidak perlu sorting." << endl;
                        } else {
                            if (subPilih == 1) { 
                                sortNamaBubbleDesc(arr, count); 
                                cout << " Diurutkan (Nama Descending)!" << endl; 
                            }
                            else if (subPilih == 2) { 
                                sortHariSelectionAsc(arr, count); 
                                cout << " Diurutkan (Hari Siram Ascending)!" << endl; 
                            }
                            else if (subPilih == 3) { 
                                sortStatusInsertion(arr, count); 
                                cout << " Diurutkan (Status Hidup)!" << endl; 
                            }
                            lihatTanaman(&dataUser[indexUserAktif]);
                        }
                    }
                    // ================= FITUR CARI (SEARCHING) =================
                    else if (pilih == 7) {
                        cout << "=====CARI TANAMAN=====" << endl;
                        cout << " 1. Cari Nama              " << endl;
                        cout << " 2. Cari Hari Siram        " << endl;
                        cout << "Pilihan: ";
                        
                        int cariPilih;
                        cin >> cariPilih;
                        
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw InvalidInputException("Pilihan harus angka!");
                        }
                        
                        if (cariPilih < 1 || cariPilih > 2) {
                            throw OutOfRangeException("Pilihan hanya 1-2!");
                        }

                        Tanaman* arr = dataUser[indexUserAktif].daftarTanaman;
                        int count = dataUser[indexUserAktif].jumlahTanaman;
                        
                        if (count == 0) { 
                            cout << " Belum ada data tanaman." << endl;
                        } else {
                            if (cariPilih == 1) {
                                cin.ignore();
                                string target;
                                cout << "Masukkan nama tanaman: "; 
                                getline(cin, target);
                                
                                if (target.empty()) {
                                    throw InvalidInputException("Nama tidak boleh kosong!");
                                }
                                
                                int hasil = linearSearchNama(arr, count, target);
                                if (hasil != -1) {
                                    cout << " Ditemukan di No. " << hasil + 1 << endl;
                                    cout << "Nama: " << (arr + hasil)->namaTanaman 
                                         << " | Status: " << ((arr + hasil)->statusHidup ? "Hidup" : "Mati") << endl;
                                } else {
                                    cout << " Tanaman '" << target << "' tidak ditemukan." << endl;
                                }
                            } else if (cariPilih == 2) {
                                int target;
                                cout << "Masukkan hari terakhir siram (1-7): "; 
                                cin >> target;
                                
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    throw InvalidInputException("Input harus angka!");
                                }
                                
                                if (target < 1 || target > 7) {
                                    throw OutOfRangeException("Hari harus 1-7!");
                                }
                                
                                sortHariSelectionAsc(arr, count);
                                cout << "(Data diurutkan otomatis untuk Binary Search)" << endl;
                                
                                int hasil = binarySearchHari(arr, count, target);
                                if (hasil != -1) {
                                    cout << " Ditemukan di No. " << hasil + 1 << endl;
                                    cout << "Nama: " << (arr + hasil)->namaTanaman 
                                         << " | Hari: " << (arr + hasil)->hariTerakhirSiram << endl;
                                } else {
                                    cout << " Tidak ada tanaman dengan hari siram '" << target << "'." << endl;
                                }
                            }
                        }
                    }
                }
            } catch (const InvalidInputException& e) {
                cout << " INPUT ERROR: " << e.what() << endl;
                cout << " Silakan coba lagi dengan input yang valid." << endl;
            } catch (const OutOfRangeException& e) {
                cout << " RANGE ERROR: " << e.what() << endl;
                cout << " Silakan pilih nilai yang sesuai." << endl;
            } catch (const exception& e) {
                cout << " UNEXPECTED ERROR: " << e.what() << endl;
                cout << " Program akan melanjutkan..." << endl;
            }
        }

        cleanupMemory(dataUser, jumlahUser);
        delete[] dataUser; 
        cout << " Program selesai. Memory telah dibersihkan." << endl;
        
    } catch (const bad_alloc&) {
        cerr << " FATAL ERROR: Gagal alokasi memori!" << endl;
        return 1;
    } catch (const exception& e) {
        cerr << " FATAL ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;  
}