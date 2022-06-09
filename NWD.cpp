#include<iostream>
using namespace std;

int NWD(int a, int b)
{
    while (a != b)
        if (a > b)
            a -= b; 
        else
            b -= a; 
    return a; 
}

int main()
{
    int a, b;

    cout << "Podaj dwie liczby: ";
    cin >> a >> b;

    cout << "NWD(" << a << "," << b << ") = " << NWD(a, b) << endl;

    return 0;
}