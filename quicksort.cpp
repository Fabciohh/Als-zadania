#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void quicksort(int* t,int lewy, int prawy)
{
    if (prawy <= lewy) return;

    int i = lewy - 1, j = prawy + 1, pivot = t[(lewy + prawy) / 2];
    while (1)
    {
        while (pivot > t[++i]);
        while (pivot < t[--j]);
        if (i <= j) swap(t[i], t[j]);
        else break;
    }
    if (j > lewy) quicksort(t, lewy, j);
    if (i < prawy) quicksort(t, i, prawy);
}

int main()
{
    srand(time(NULL));
    int t[10], opcja = 1;
    for (int i = 0; i < 10; i++)
    {
        t[i] = rand() % 100 + 1;
        cout << t[i] << '\t';
    }
    quicksort(t,0,10-1);
    cout << '\n';
    for (int i = 0; i < 10; i++)
    {
        cout << t[i] << '\t';
    }
    return 0;
}