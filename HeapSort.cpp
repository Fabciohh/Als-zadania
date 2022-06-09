#include <iostream>
#include <cstdlib>

using namespace std;

void Heapify(int *t,int n, int i)
{
	int largest = i, 
		left = 2 * i + 1, 
		right = 2 * i + 2;
	if (left<n && t[left]>t[largest])
	{
		largest = left;
	}
	if (right<n && t[right]>t[largest])
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(t[i], t[largest]);
		Heapify(t, n, largest);
	}
}

void HeapSort(int *t, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(t, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(t[0], t[i]);
		Heapify(t, i, 0);
	}
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
	HeapSort(t,10);
	cout << '\n';
	for (int i = 0; i < 10; i++)
	{
		cout << t[i] << '\t';
	}
	return 0;
}
