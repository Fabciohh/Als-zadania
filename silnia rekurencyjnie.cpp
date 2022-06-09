#include <cstdlib>
#include <iostream>
using namespace std;

long long silnia(int n)
{
    if (n < 2)
        return 1; //silnia z 0 i 1 wynosi 1

    return n * silnia(n - 1); //wywołanie funkcji przez samą siebie ze zmniejszonym argumentem
}

int main()
{
    int n;

    cout << "Podaj liczbę: ";
    cin >> n;
    cout << "n! = " << silnia(n) << endl;

    system("pause");
    return 0;
}