#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Tubes ASD Kelompok 1

//global declaration
int I_InputOption, I_NumTable;
string S_BuyerName, S_US, S_PW;
char C_InputOption;
bool Table[20]; //biar tau meja nya tersedia atau ga true = tersedia, false = udah di booking
//note: I = int, S = string, C = char, F = float

void TableMakeTrue()
{
    for (int i = 0; i < 20; i++)
    {
        Table[i] = true;
        if (i == 3 || i == 4 || i == 5)
            Table[i] = false;
    }
}

bool CheckingAccount(string SUsername, string SPassword)
{
    ifstream account;
    string InputUsername, InputPassword;
    account.open("Account.txt");
    while (account >> InputUsername >> InputPassword)
    {
        if (InputUsername == SUsername && InputPassword == SPassword)
            return true;
    }
    account.close();
    return false;
}


//fitur ga guna anjg hapus aja.
void CreateAdminAccount()
{
    string S_temp;
    ofstream AddAccount("Account.txt");
    ADD:
    system("cls");
    cout << "---Create Account---" << endl;
    cout << "Enter new username: ";
    cin >> S_US;
    cout << "Enter password: ";
    cin >> S_PW;
    system("cls");
    cout << "Enter new username: " << S_US << endl;
    cout << "Confirm password: ";
    cin >> S_temp;
    if (S_PW != S_temp)
    {
        cout << "Incorect password!" << endl;
        system("pause");
        goto ADD;
    }
    else
    {
        AddAccount << S_US << " " << S_PW << endl;
        AddAccount.close();
        cout << "New account created!" << endl;
        system("pause");
    }
}

void TableStatus()
{
    for (int i = 0; i < 20; i++)
    {
        cout << "Table " << i + 1 << " : ";
        cout << (Table[i] ? "Available" : "Booked");
        cout << endl;
    }
}


void LoginAsBuyer()
{
    cout << "Buyer name: ";
    cin >> S_BuyerName;
    TABLE:
    system("cls");
    TableStatus();
    cout << "No Table: ";
    cin >> I_NumTable;
    if (I_NumTable < 1 || I_NumTable > 20)
    {
        cout << "Wrong Choice!" << endl;
        system("pause");
        goto TABLE;
    }
    if (Table[I_NumTable - 1] == false)
    {
        cout << "Table already booked!" << endl;
        system("pause");
        goto TABLE;
    }
    else
    {
        cout << "Name: " << S_BuyerName << endl;
        cout << "Your table is " << I_NumTable << endl;
        Table[I_NumTable - 1] = false;
    }
    cout << endl;
    // TableStatus();
    //function();
    cout << "login as buyer succeed";
}


//menurut kalian mending jadi subprogram "LoginPage" atau masukin ke main()?
void LoginPage()
{
    TableMakeTrue();

    LOGINPAGE:
    system("cls");
    cout << "#######-Login Page-#######" << endl;
    cout << "1. Login as admin" << endl;
    cout << "2. Login as buyer" << endl;
    cout << "3. Create admin account" << endl;
    cout << "Input: ";
    cin >> I_InputOption;
    switch (I_InputOption)
    {
    case 1:
        LOGIN:
        system("cls");
        cout << "Username: ";
        cin >> S_US;
        cout << "Password: ";
        cin >> S_PW;
        if (CheckingAccount(S_US, S_PW) == true)
        {
            //Login as admin
            cout << "login as admin succeed";
            //AdminFunction();
        }
        else
        {
            cout << "Wrong username or password! Try again? (y/n): ";
            cin >> C_InputOption;

            if (C_InputOption == 'y' || C_InputOption == 'Y')
                goto LOGIN;
            else
                goto LOGINPAGE;
        }
        break;
    
    case 2:
        LoginAsBuyer();
        //BuyerFunction();
        break;

    case 3:
        CreateAdminAccount();
        goto LOGINPAGE;

    default:
        goto LOGINPAGE;
    }
        
}


int main()
{
    LoginPage();

    return 0;
}