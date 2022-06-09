//WCY20KY2S1 Maciński Fabian
//drzewo BST
#include <iostream>
using namespace std;

struct node //tworzymy drzewo
{
	int value;
	struct node* left;
	struct node* right;
	struct node* up;
};
void treeInsert(node** root, int value) //wstawiamy element do drzewa
{
	node* newnode = new node;
	newnode->value = value;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->up = NULL;
	if (*root)
	{
		node* temp1 = *root;
		node* temp2 = NULL;
		while (temp1)
		{
			temp2 = temp1;
			if (temp1->value > newnode->value)  //sprawdzamy gdzie wstawic element
			{
				temp1 = temp1->left;    //jesli mniejszy od obecnego elementu idziemy w lewo
			}
			else if (temp1->value < newnode->value)
			{
				temp1 = temp1->right;   //jesli wiekszy od obecnego elementu idziemy w prawo
			}
			else
			{
				delete newnode;
				cout << "Wartosci nie moga sie powtarzac \n" << endl; // jesli znajdziemy taki sam konczymy funkcje
				return;
			}
		}
		if (temp2->value > newnode->value) temp2->left = newnode;   //jesli wczesniejszy element jest wiekszy dodajemy po lewo
		else temp2->right = newnode;    //jesli wczesniejszy element jest mniejszy dodajemy po prawo
		newnode->up = temp2;
	}
	else    //gdy nie ma elementow dodajemy nowy jako pierwszy
	{
		*root = newnode;
	}
}

void printLVR(node* root)   //wypisujemy wszystkie elementy in order
{
	if (root->left) printLVR(root->left);   //rekurencyjnie szukamy najbardziej po lewo elementu
	cout << root->value << '\t';            //wypisujemy element
	if (root->right) printLVR(root->right); //rekurencyjnie idziemy najbardziej w prawo
}
void treeDelete(node** root, int value)
{
	node* temp1 = *root;
	node* temp2 = NULL;
	node* temp3 = NULL;
	node* temp4 = NULL;
	while (temp1)
	{
		if (temp1->value < value)
		{
			temp2 = temp1;
			temp1 = temp1->right;
		}
		else if (temp1->value > value)
		{
			temp2 = temp1;
			temp1 = temp1->left;
		}
		else if (temp1->value == value)
		{           
			if (temp2 && temp2->value < value)
			{
				if (temp1->left == NULL)
				{
					if (temp1->right == NULL)   
					{
						temp2->right = NULL;
						delete temp1;
						return;
					}
					else                        
					{
						temp1->right->up = temp2;
						temp2->right = temp1->right;
						delete temp1;
						return;
					}
				}
				else
				{
					if (temp1->right == NULL)
					{
						temp1->left->up = temp2;
						temp2->left = temp1->right;
						delete temp1;
						return;
					}
					else
					{
						temp3 = temp1->left;
						temp4 = temp1;
						while (temp3->right != NULL)
						{
							temp4 = temp3;
							temp3 = temp3->right;
						}
						temp4->left = temp3->left;
						temp3->up = temp1->up;
						temp3->right = temp1->right;
						temp2->right = temp3;
						delete temp1;
						return;
					}
				}
			}
			else if (temp2 && temp2->value > value)
			{
				if (temp1->left == NULL)
				{
					if (temp1->right==NULL)
					{
						temp2->left = NULL;
						delete temp1;
						return;
					}
					else
					{
						temp1->right->up = temp2;
						temp2->left = temp1->right;
						delete temp1;
						return;
					}
				}
				else
				{
					if (temp1->right == NULL)
					{
						temp1->left->up = temp2;
						temp2->right = temp1->left;
						delete temp1;
						return;
					}
					else
					{
						temp3 = temp1->left;
						temp4 = temp1;
						while (temp3->right != NULL)
						{
							temp4 = temp3;
							temp3 = temp3->right;
						}
						temp4->left = temp3->left;
						temp3->up = temp1->up;
						temp3->right = temp1->right;
						temp2->left = temp3;
						delete temp1;
						return;
					}
				}
			}
			else if(temp2==NULL)
			{
					if ((*root)->right == NULL && (*root)->left == NULL)
					{
						delete temp1;
						*root = NULL;
					}
					else if ((*root)->right == NULL && (*root)->left)
					{
						(*root)->left->up = NULL;
						*root = (*root)->left;
						
						delete temp1;
					}
					else if ((*root)->right && (*root)->left == NULL)
					{
						(*root)->right->up = NULL;
						*root = (*root)->right;
						delete temp1;
					}
					else
					{
						temp2 = (*root)->left;
						temp3 = (*root);
						while (temp2->right)
						{
							temp3 = temp2;
							temp2 = temp2->right;
						}
						temp3->right = temp2->left;
						temp2->left = (*root)->left;
						temp2->right = (*root)->right;
						temp2->up = NULL;
						delete temp1;
						*root = temp2;
						return;
					}
				}
			
		}

		
	}
	cout << "Nie znaleziono elementu\n";
}
void DSW(node** root)
{
	node* temp = *root;
	node* prev = NULL;
	while (temp)
	{
		if (temp->left)
		{
			node* t = temp->left;
			t->up = temp->up;
			temp->up = t;
			temp->left = t->right;
			t->right = temp;
			

		}
		else
		{
			temp = temp->right;
			
		}
	}
	temp = *root;
	int n = 0;
	while (temp)
	{
		n++;
		temp = temp->right;
	}
	
	while (n > 0)
	{
		temp = *root;
		n /= 2;
		for (int i = 0; i < n; i++)
		{
			node* t = temp->right;
			if (temp == *root) *root = t;
			t->up = temp->up;
			if(t->left) t->left->up = temp;
			t->left = temp;
			temp->right = t->left;
			
			temp = t->right;
		}
	}
}

int main()
{
	struct node* root = NULL;
	int value, option = 1;
	while (option != 0)
	{
		cout << "Podaj opcje programu:\nNowy element(1), Usun element(2), Przejscie infiksowe(3), Koniec(0)\n";   //instrukcja
		cin >> option;
		switch (option)
		{
		case 1:     //dodawanie elementu
			cout << "Podaj nowy element\n";
			cin >> value;   //pobieramy element do dodania
			treeInsert(&root, value);
			break;
		case 2:     //usuwanie elementu
			cout << "Podaj wartosc do usuniecia\n";
			cin >> value;   //pobieramy element do usuniecia
			treeDelete(&root, value);
			break;
		case 3: //przejscie infiksowe
			if (root)
			{
				printLVR(root);
				cout << '\n';
			}
			else cout << "Drzewo jest puste\n";
			break;
		case 4:
			cout << "Wykonuje algorytm DSW\n";
			DSW(&root);
		}

	}
	cout << "\nDo zobaczenia ;)\n";
	return 0;
}
/*1 5
 1 10
 1 2
 1 1
 1 4
 1 3
 1 12
 1 7
 1 11
 1 13
 */