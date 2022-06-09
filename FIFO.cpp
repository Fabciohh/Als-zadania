#include <iostream>
using namespace std;
struct node     //tworzymy strukture
{
    int value;
    struct node* next;
};

int front(node* head)
{
    if (head == NULL) return -1;   //sprawdzamy czy nie jest pusty
    else return head->value;
}
void enqueue(node** head, int value)
{
    node* el = new node;        //wstawiamy nowy element
    el->value = value;          //przypisujemy wartosc do elementu
    el->next = NULL;
    if (*head == NULL) *head = el; //sprawdzamy czy nie jest pusty
    else {
        node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = el;
    }
}
void dequeue(node** head)
{
    if (*head == NULL) return; //sprawdzamy czy nie jest pusty
    node* temp = *head;
    *head = (*head)->next;
    delete temp;    //usuwamy element
}
void clear(node** head)
{
    if (*head==NULL) return; //sprawdzamy czy nie jest pusty
    while (*head) {     //dzialamy na calej kolejce
        dequeue(head);  //usuwamy elementy
    }
}
int main()
{
    int option = 1, value;
    node* head = NULL;
    cout << "Witaj uzytkowniku \n";
    while (option != 0)
    {
        cout << "Front(1), Enqueue(2), Dequeue(3), Clear(4), Koniec(0)\n";
        cin >> option;
        switch (option)
        {
        case 1: //odczytujemy element ze szczytu
            if (front(head) != -1) cout << "Element przodujacy: \n" << front(head) << '\n';
            else cout << "Nie ma takiego elementu \n";
            break;
        case 2: //wpisujemy wartosc
            cout << "Wpisz wartosc \n";
            cin >> value;
            enqueue(&head, value);
            break;
        case 3: //usuwanie elementu
            cout << "Usuwamy element \n";
            dequeue(&head);
            break;
        case 4: //czyszczenie kolejki
            cout << "Czyscimy kolejke\n";
            clear(&head);
            break;
        case 0:     //zakonczenie programu
            cout << "Do zobaczenia pozniej  \n";
            break;
        }
    }
    return 0;
}