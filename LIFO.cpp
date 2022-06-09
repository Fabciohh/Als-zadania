#include <iostream>
using namespace std;
struct node     //tworzymy strukture
{
    int value;
    struct node* next;
};
bool isempty(node* head)
{
    if (head == NULL) return 1; //sprawdzamy czy nie jest pusty
    else return 0;
}
int top(node* head)
{
    if (isempty(head)) return -1;   //sprawdzamy czy nie jest pusty
    else return head->value;
}
void push(node** head, int value)
{
    node* el = new node;        //wstawiamy nowy element
    el->value = value;
    el->next = *head;
    *head = el;

}
void pop(node** head)
{
    if (isempty(*head)) return; //sprawdzamy czy nie jest pusty
    node* temp = *head;
    *head = (*head)->next;
    delete temp;    //usuwamy element
}
void clear(node** head)
{
    if (isempty(*head)) return; //sprawdzamy czy nie jest pusty
    while (*head) {     //dzialamy na calym stosie
        pop(head);      //usuwamy elemety
    }
}
void show(node** head)
{
    if (isempty(*head)) return;
    node* temp = *head;
    while (temp)
    {
        cout << temp->value << '\n';
        temp = temp->next;
    }
}
int main()
{
    int option = 1, value;
    node* head = NULL;
    cout << "Witaj uzytkowniku :) \n";
    while (option != 0)
    {
        cout << "Top(1), Push(2), POP(3), IsEmpty(4), Clear(5), Show(6), Koniec(0)\n";
        cin >> option;
        switch (option)
        {
        case 1:  //odczytujemy element ze szczytu
            if (top(head) != -1) cout << "Element przodujacy: \n" << top(head) << '\n';
            else cout << "Nie ma takiego elementu \n";
            break;
        case 2: //wpisujemy wartosc
            cout << "Wpisz wartosc \n";
            cin >> value;
            push(&head, value);
            break;
        case 3:  //usuwanie elementu
            cout << "Usuwamy element \n";
            pop(&head);
            break;
        case 4: //sprawdzamy czy kolejka jest pusta
            cout << "Sprawdzamy czy kolejka jest pusta tak(1), nie(0)\n" << isempty(head) << '\n';
            break;
        case 5: //czyszczenie kolejki
            cout << "Czyscimy kolejke\n";
            clear(&head);
            break;
        case 6:
            cout << "wypisuje wszystkie elementy: \n";
            show(&head);
            break;
        case 0:     //zakonczenie programu
            cout << "Do zobaczenia pozniej  \n";
            break;
        }
    }
    return 0;
}