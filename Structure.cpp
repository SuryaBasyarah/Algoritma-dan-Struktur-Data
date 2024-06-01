#include <iostream>

using namespace std;

struct Data_Mahasiswa
{
    int NIM[3] = {105222016, 105222027, 105222022};
    string nama[3] = {"surya", "athirah", "jia"};
    string prodi[3] = {"ilkom", "ilkom", "ilkom"};
};

struct Data_Mahasiswa_UP
{
    int NIM[3] = {105222027, 105222022, 105222016};
    string nama[3] = {"athirah", "jia", "surya"};
    string prodi[3] = {"ilkom", "ilkom", "ilkom"};
};

int main(){
    Data_Mahasiswa datamahasiswa;
    Data_Mahasiswa_UP datamahasiswaUP;

    for (int i = 0; i < 3; i++)
    {
        cout << datamahasiswa.NIM[i] << " ";
        cout << datamahasiswa.nama[i] << " ";
        cout << datamahasiswa.prodi[i] << endl;
    }

    cout  << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << datamahasiswaUP.nama[i] << " ";
        cout << datamahasiswaUP.NIM[i] << " ";
        cout << datamahasiswaUP.prodi[i] << endl;
    }

    return 0;
}