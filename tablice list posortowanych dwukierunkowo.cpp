#include <iostream>
#include <cstdlib>
using namespace std;

struct list {

	int value;
	struct list* next;
	struct list* prev;
};

void addvalue(list** head, int value)
{
	list* added = new list;
	list* temp = NULL;
	added->value = value;
	if ((*head == NULL))
	{
		added->next = *head;
		added->prev = *head;
		*head = added;
	}
	else if (added->value <= (*head)->value)
	{
		added->next = *head;
		added->next->prev = added;
		*head = added;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL && temp->next->value < added->value)
		{
			temp = temp->next;
		}
		added->next = temp->next;
		if (temp->next != NULL)
		{
			added->next->prev = added;
		}
		temp->next = added;
		added->prev = temp;
	}
	
}

void deletevalue(list** head, int value)
{
	if (*head == NULL)
	{
		cout << "brak elementow w tablicy\n";
		return;
	}
	list* temp1 = *head;
	list* temp2 = NULL;
	if (temp1->value == value)
	{
		*head = temp1->next;
		(*head)->prev = temp1->prev;
		delete temp1;
		return;
	}

		while (temp1->value != value)
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
		if (temp1 == NULL) return;
		temp2->next = temp1->next;
		temp2->next->prev = temp1->prev;
		delete temp1;
	
}

void show(list* head)
{
	list* temp = head;
	if (head == NULL)
	{
		cout << "brak elementow w tablicy\n";
		return;
	}
	while (temp != NULL)
	{
		cout << temp->value << "\t";
		temp = temp->next;
	}
}

void clear(list** head)
{
	if (*head == NULL)
	{
		cout << "brak elementow w tablicy\n";
		return;
	}
	list* temp;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		delete temp;
	}
}

int main()
{
	list* head[10];
	for (int i = 0; i < 10; i++)
	{
		head[i]= NULL;
	}
	int option=1;
	string stemp;
	int ch;
	
	while (option != 0)
	{
		cout << "Podaj element do dodania(1), Podaj element do usuniecia(2), Podaj tablice do wyswietlenia(3), Usun zawartosc tablicy(4), Koniec(0) \n";
		cin >> option;
		switch (option)
		{
		case 1: //dodawanie elementu do danej tablicy
			cout << "Podaj liczbe do dodania \n";
			cin >> stemp;
			ch = stemp[0];
			ch -= 48;
			addvalue(&head[ch], strtol(stemp.c_str(), NULL, 10));
			break;
		case 2: //usuniecie elementu z danej tablicy
			cout << "Podaj liczbe do usuniecia \n";
			cin >> stemp;
			ch = stemp[0];
			ch -= 48;
			deletevalue(&head[ch], strtol(stemp.c_str(), NULL, 10));
			break;
		case 3:
			cout << "Podaj wartosc pierwszej cyfry dla ktorej chcesz wyswietlic tablice \n";
			cin >> stemp;
			ch = stemp[0];
			ch -= 48;
			show(head[ch]);
			break;
		case 4:
			cout << "Podaj wartosc pierwszej cyfry dla ktorej chcesz usunac wartosci w tablicy \n";
			cin >> stemp;
			ch = stemp[0];
			ch -= 48;
			clear(&head[ch]);
			break;
		}
		cout << "\n";
	}
	return 0;
}