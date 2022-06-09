#include <iostream>

using namespace std;

int ciag[1000];
int szukanie_elementu(int lewa_strona, int prawa_strona, int liczba)
{
    int srodek_ciagu;
    while (lewa_strona <= prawa_strona)
    {
        srodek_ciagu = (lewa_strona + prawa_strona) / 2;

        if (ciag[srodek_ciagu] == liczba)
            return srodek_ciagu;

        if (ciag[srodek_ciagu] > liczba)
            prawa_strona = srodek_ciagu - 1;
        else
            lewa_strona = srodek_ciagu + 1;
    }
    return -1; 
}

int main()
{
    int lz, liczba;

    cout << "podaj liczbe znakow w ciagu: ";
    cin >> lz;
    for (int i = 0; i < lz; i++)
        cin >> ciag[i];

    cout << "podaj liczbe szukana: ";
    cin >> liczba;

    if (szukanie_elementu(0, lz - 1, liczba))
        cout << "liczba " << liczba << " znajduje sie na pozycji " << szukanie_elementu(0, lz - 1, liczba) + 1 << endl;
    else
        cout << "brak elementu w ciagu" << endl;
    return 0;
}