#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>


using namespace std;

void znalezienie_ciagu(string* slownik, string* bufor, int slownik_dl, int bufor_dl, int* dl, int* poz)
{
	string temp = "";
	string wynik = "";
	int zmpoz = 0, zmdl = 0;
	for (int i = 0; i < bufor_dl; i++)
	{
		temp = temp + (*bufor)[i];
		if ((*slownik).find(temp) != -1)
		{
			wynik = temp;
			if ((*slownik).find(temp) != NULL) zmpoz = (*slownik).find(temp);
			zmdl = i + 1;
		}
		else
		{
			break;
		}
	}
	*poz = zmpoz;
	*dl = zmdl;
}

void uzupelnienie(string* wejscie, string* slownik, string* bufor, int slownik_dl, int bufor_dl)
{
	if ((*bufor).length() != bufor_dl)
	{
		for (int i = (*bufor).length(); i < bufor_dl; i++)
		{
			(*bufor) = (*bufor) + (*wejscie)[0];
			(*wejscie).erase(0, 1);
		}
	}
}

string kodowanie_lz77(string* wejscie, string* slownik, string* bufor, int slownik_dl, int bufor_dl)
{
	string kod;
	int dl = 0, poz = 0, zmdl = 0;
	char a, b;
	if ((*slownik) == "")
	{
		for (int i = 0; i < slownik_dl; i++)
		{
			*slownik = *slownik + (*wejscie)[0];
		}
		cout << "<0,0," << (*slownik)[0] << ">\n";
		kod = "00";
		kod = kod + (*slownik)[0];
		wejscie->erase(0, 1);
	}
	while (!wejscie->empty())
	{
		uzupelnienie(wejscie, slownik, bufor, slownik_dl, bufor_dl);
		znalezienie_ciagu(slownik, bufor, slownik_dl, bufor_dl, &dl, &poz);
		zmdl = dl;
		if (dl < bufor_dl)
		{
				slownik->erase(0, ++zmdl);
				cout << "<" << poz << "," << dl << "," << (*bufor)[dl] << ">\n";
				a = poz + '0';
				b =dl + '0';
				kod = kod + a;
				kod = kod + b;
				kod = kod + (*bufor)[dl];
				for (int i = 0; i < zmdl; i++)
				{
					(*slownik) = (*slownik) + (*bufor)[0];
					bufor->erase(0, 1);
				}
		}
	}
	while (!bufor->empty() && (*bufor)[1] != '\0')
	{
		znalezienie_ciagu(slownik, bufor, slownik_dl, (*bufor).length(), &dl, &poz);
		zmdl = dl;
		slownik->erase(0, ++zmdl);
		cout << "<" << poz << "," << dl << "," << (*bufor)[dl] << ">\n";
		a = poz + '0';
		b = dl + '0';
		kod = kod + a;
		kod = kod + b;
		kod = kod + (*bufor)[dl];
		for (int i = 0; i < zmdl; i++)
		{
			(*slownik) = (*slownik) + (*bufor)[0];
			bufor->erase(0, 1);
		}
	}
	if ((*bufor)[0] != '\0')
	{
		cout << "<0,0," << (*bufor)[0] << ">\n";
		kod = kod + "00";
		kod = kod + (*bufor)[0];
		slownik->erase(0, 1);
		(*slownik) = (*slownik) + (*bufor)[0];
		bufor->erase(0, 1);
	}
	cout << "<0,0,EOF>\n";
	return kod;
}
string dekodowanie_lz77(string* wejscie, string* wyjscie, int slownik_dl, int bufor_dl)
{
	string dekod;
	while (!wejscie->empty())
	{
		int zmdl,zmpoz;
		int dl = wyjscie->length();
		zmdl = (*wejscie)[1]-48;
		zmpoz = (*wejscie)[0]-48;
		if (zmdl == 0)
		{
			*wyjscie = *wyjscie + (*wejscie)[2];
			cout << (*wyjscie) <<'\n';
			dekod = (*wyjscie);
			wejscie->erase(0, 3);
		}
		else
		{
			if (dl < zmpoz)
			{
				for (int i = 0; i < zmdl; i++)
				{
					*wyjscie = *wyjscie + (*wyjscie)[dl - zmdl + i];
					dekod = dekod + (*wyjscie)[dl - zmdl + i];
				}
			}
			else
			{
				for (int i = 0; i < zmdl; i++)
				{
					*wyjscie = *wyjscie + (*wyjscie)[dl - bufor_dl + zmpoz+i];
					dekod = dekod + *wyjscie + (*wyjscie)[dl - bufor_dl + zmpoz + i];
				}
			}
			dekod = dekod + (*wejscie)[2];
			*wyjscie = *wyjscie + (*wejscie)[2];
			wejscie->erase(0, 3);
			cout << (*wyjscie) << '\n';
		}
	}
	return dekod;
}

int main()
{
	int slownik_dl, bufor_dl, wybor;
	string wejsciedekod, bufor, slownik, wejsciekod, wyjscie, nazwawej, nazwawyj;
	fstream plikwej(nazwawej, ios::in);
	fstream plikwyj(nazwawyj, ios::out);

	cout << "Podaj dlugosc slownika: \n";
	cin >> slownik_dl;
	cout << "Podaj dlugosc bufora: \n";
	cin >> bufor_dl;

	cout << "Wybierz opcje programu:\n1.Kodowanie\n2.Dekodowanie\n";
	cin >> wybor;
	if (wybor == 1)
	{
		cout << "Podaj nazwe pliku tekstowego z danymi w formacie nazwa.txt\n";
		cin >> nazwawej;
		plikwej.open(nazwawej);
		plikwyj.open("odpowiedzkod.txt");
		if (plikwej.good() && plikwyj.good())
		{
			plikwej >> wejsciekod;
			plikwyj << kodowanie_lz77(&wejsciekod, &slownik, &bufor, slownik_dl, bufor_dl);
		}
		else cout << "Blad otwarcia plikow!\n";
	}
	else
	{
		cout << "Podaj nazwe pliku tekstowego z danymi w formacie nazwa.txt\n";
		cin >> nazwawej;
		plikwej.open(nazwawej);
		plikwyj.open("odpowiedzdekod.txt");
		if (plikwej.good() && plikwyj.good())
		{
			plikwej >> wejsciedekod;
			plikwyj << dekodowanie_lz77(&wejsciedekod, &wyjscie, slownik_dl, bufor_dl);
		}
		else cout << "Blad otwarcia plikow!\n";
	}
	plikwej.close();
	plikwyj.close();
	return 0;
}