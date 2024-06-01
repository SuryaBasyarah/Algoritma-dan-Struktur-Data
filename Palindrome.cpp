#include <iostream>
#include <string>
#include <stack>
using namespace std; 

bool palindrome(string stEXP)
{
    int length = stEXP.size();
    stack<char> st;

    int i = 0, mid = length / 2;

    for (i; i < mid; i++)
    {
        st.push(stEXP[i]);
    }

    if (length % 2 != 0)
    {
        i++;
    }

    char value;

    while (stEXP[i] == '.')
    {
        // value = st.top();
        // st.pop();
        i++;
    }

    while (!st.empty())
    {
        value = st.top();
        st.pop();

        if (value != stEXP[i])
        {
            return false;
        }
        i++;
    }
    
    
    return true;
}

int main()
{
    string sEXP;
    cout << "Input sEXP: ";
    getline(cin, sEXP);

    if (palindrome(sEXP) == true)
    {
        cout << "String is palindrome";
    }
    else
    {
        cout << "String isn't palindrome";
    }

    return 0;
}