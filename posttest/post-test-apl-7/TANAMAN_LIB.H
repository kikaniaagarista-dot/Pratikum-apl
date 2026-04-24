#ifndef TANAMAN_LIB_H
#define TANAMAN_LIB_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <new>

using namespace std;

// Custom Exception Classes
class InvalidInputException : public invalid_argument {
public:
    InvalidInputException(const string& msg) : invalid_argument(msg) {}
};

class OutOfRangeException : public out_of_range {
public:
    OutOfRangeException(const string& msg) : out_of_range(msg) {}
};

class MemoryException : public bad_alloc {
public:
    MemoryException(const string& msg) : bad_alloc() { message = msg; }
    const char* what() const noexcept override { return message.c_str(); }
private:
    string message;
};

// Struct Definitions
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

// Function Declarations
void sortNamaBubbleDesc(Tanaman arr[], int n);
void sortHariSelectionAsc(Tanaman arr[], int n);
void sortStatusInsertion(Tanaman arr[], int n);
int linearSearchNama(Tanaman* arr, int n, string target);
int binarySearchHari(Tanaman* arr, int n, int target);

int loginUser(User* dataUser, int jumlahUser, string nama, string nim);
void registerUser(User* dataUser, int &jumlahUser);
void tambahTanaman(User* user);
void lihatTanaman(User* user);
void updateTanaman(User* user);
void hapusTanaman(User* user);
void cleanupMemory(User* dataUser, int jumlahUser);

#endif