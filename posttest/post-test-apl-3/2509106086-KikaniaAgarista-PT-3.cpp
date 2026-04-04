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


int loginUser(User dataUser[], int jumlahUser, string nama, string nim) {
    for (int i = 0; i < jumlahUser; i++) {
        if (dataUser[i].statusAktif &&
            dataUser[i].namaUser == nama &&
            dataUser[i].nimUser == nim) {
            return i;
        }
    }
    return -1;
}


void registerUser(User dataUser[], int &jumlahUser) {
    if (jumlahUser >= 50) {
        cout << "User penuh!" << endl;
        return;
    }

    cin.ignore();
    cout << "Nama: ";
    getline(cin, dataUser[jumlahUser].namaUser);

    cout << "NIM: ";
    getline(cin, dataUser[jumlahUser].nimUser);

    dataUser[jumlahUser].jumlahTanaman = 0;
    dataUser[jumlahUser].statusAktif = true;

    jumlahUser++;

    cout << "Register berhasil!" << endl;
}



void tambahTanaman(User &user) {
    if (user.jumlahTanaman >= 100) {
        cout << "Tanaman penuh!" << endl;
        return;
    }

    int index = user.jumlahTanaman;

    cin.ignore();
    cout << "Nama Tanaman: ";
    getline(cin, user.daftarTanaman[index].namaTanaman);

    cout << "Jenis: ";
    getline(cin, user.daftarTanaman[index].jenisTanaman);

    cout << "Hari Siram (1-7): ";
    cin >> user.daftarTanaman[index].hariTerakhirSiram;

    cout << "Status Hidup (1=Ya,0=Tidak): ";
    cin >> user.daftarTanaman[index].statusHidup;

    user.jumlahTanaman++;

    cout << "Tanaman berhasil ditambahkan!" << endl;
}



void lihatTanaman(User user) {

    if (user.jumlahTanaman == 0) {
        cout << "Belum ada tanaman." << endl;
        return;
    }

    cout << "No | Nama | Jenis | Siram | Status" << endl;

    for (int i = 0; i < user.jumlahTanaman; i++) {
        cout << i + 1 << " | "
             << user.daftarTanaman[i].namaTanaman << " | "
             << user.daftarTanaman[i].jenisTanaman << " | "
             << user.daftarTanaman[i].hariTerakhirSiram << " | "
             << (user.daftarTanaman[i].statusHidup ? "Hidup" : "Mati")
             << endl;
    }
}



void updateTanaman(User &user) {

    int nomor;
    cout << "Nomor tanaman: ";
    cin >> nomor;

    if (nomor <= 0 || nomor > user.jumlahTanaman) {
        cout << "Tidak valid!" << endl;
        return;
    }

    int index = nomor - 1;

    cout << "Hari Siram Baru: ";
    cin >> user.daftarTanaman[index].hariTerakhirSiram;

    cout << "Status Hidup Baru (1=Ya,0=Tidak): ";
    cin >> user.daftarTanaman[index].statusHidup;

    cout << "Update berhasil!" << endl;
}



void hapusTanaman(User &user) {

    int nomor;
    cout << "Nomor tanaman: ";
    cin >> nomor;

    if (nomor <= 0 || nomor > user.jumlahTanaman) {
        cout << "Tidak valid!" << endl;
        return;
    }

    for (int i = nomor - 1; i < user.jumlahTanaman - 1; i++) {
        user.daftarTanaman[i] = user.daftarTanaman[i + 1];
    }

    user.jumlahTanaman--;

    cout << "Tanaman berhasil dihapus!" << endl;
}



int main() {

    User dataUser[50];
    int jumlahUser = 0;
    int indexUserAktif = -1;

    bool sudahLogin = false;
    bool program = true;

    while (program) {

        if (!sudahLogin) {

            cout << "\n=== LOGIN MENU ===" << endl;
            cout << "1. Login\n2. Register\n3. Keluar\n";
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

            } 
            else if (pilih == 2) {
                registerUser(dataUser, jumlahUser);
            } 
            else {
                program = false;
            }
        }

        else {

            cout << "\n=== MENU TANAMAN ===" << endl;
            cout << "1. Tambah\n2. Lihat\n3. Update\n4. Hapus\n5. Logout\n";
            cout << "Pilihan: ";

            int pilih;
            cin >> pilih;

            if (pilih == 1)
                tambahTanaman(dataUser[indexUserAktif]);

            else if (pilih == 2)
                lihatTanaman(dataUser[indexUserAktif]);

            else if (pilih == 3)
                updateTanaman(dataUser[indexUserAktif]);

            else if (pilih == 4)
                hapusTanaman(dataUser[indexUserAktif]);

            else if (pilih == 5) {
                sudahLogin = false;
                indexUserAktif = -1;
                cout << "Logout berhasil." << endl;
            }
        }
    }

    cout << "\nProgram selesai." << endl;

    return 0;
} 

 