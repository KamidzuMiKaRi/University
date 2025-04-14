#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "rus");
	int n, a;
	list<int> numb;
	cout << "Введите количество чисел в списке: ";
	cin >> n;
	ifstream f("numbers.txt");
	// Считываем числа из файла
	for (int i = 0; i < n; i++) 
	{
		int nk;
		f >> nk;
		numb.push_back(nk);	
	}
	f.close();
	cout << "Список до удаления:";
	for (list<int>::iterator it = numb.begin(); it != numb.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "Введите число 'a' для удаления : ";
		cin >> a;
		numb.remove(a);
	// Выводим список после удаления
	cout << "Список после удаления:";
		for (list<int>::iterator it = numb.begin(); it != numb.end(); it++) 
		{
			if (*it == a) 
			{
				it = numb.erase(it);
			}
			else 
			{
				cout << *it << " ";
			}
		}
	cout << endl;
}
