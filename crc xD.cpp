#include <iostream>
#include <fstream>

using namespace std;

int szukaniecrc(fstream &plik)
{
    int bufor = 0, wielomian = 0x04C11DB7, zm;
    char znak;
    while (1)
    {
        zm = 0;
        znak = plik.get();
        if (plik.good()!=true) break;
        while (zm < 8)
        {
            if ((bufor & 0x80000000) == 0x000000000)
            {
                bufor = bufor << 1;
                bufor = bufor | ((znak & 0x80) >> 7);
                znak = znak << 1;
            }
            else
            {
                bufor = bufor << 1;
                bufor = bufor | ((znak & 0x80) >> 7);
                bufor = bufor ^ wielomian;
                znak = znak << 1;
            }
            zm++;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        if ((bufor & 0x80000000) == 0x00000000) bufor = bufor << 1;
        else
        {
            bufor = bufor << 1;
            bufor = bufor ^ wielomian;
        }
    }
    return bufor;
}
void zapiscrc(fstream &plik, int crc)
{
    char znak;
    for (int i = 0; i < 4; i++)
    {
        znak = ((crc & 0xFF000000) >> 24);
        plik << znak;
        crc = crc << 8;
    }
    plik << '\n';
    return;
}

int main()
{

    string plik_nazwa,kod;
    int crc;
    cout << "Podaj nazwe pliku z rozszerzeniem\n";
    cin >> plik_nazwa;
    fstream plik(plik_nazwa, ios::in | ios::out | ios::binary);
    plik.open(plik_nazwa);
    plik >> kod;
    if (plik.good() == true)
    {
        crc = szukaniecrc(plik);
        cout << "Sprawdzanie poprawnosci pliku\n";
        zapiscrc(plik, crc);
        kod = "";
        plik >> kod;
        crc = szukaniecrc(plik);
        if (crc == 0) cout << "Nie naruszono integralnosci danych\n";
        else cout << "Naruszono integralnosc danych\n";
        cout << "Obliczona reszta: " << crc << '\n';
    }
    else cout << "Blad otwarcia pliku";
    plik.close();
    return 0;
}