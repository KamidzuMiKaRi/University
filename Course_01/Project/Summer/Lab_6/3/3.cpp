#include <iostream>
#include <iterator>
#include <list>

using namespace std;

void out(const list<int>& l) 
{
	for (auto it = l.begin(); it != l.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int n, m, x;	// объявление переменных
	cout << "Введите количество элементов в первом списке: ";
	cin >> n;
	list<int> list1;	// объявление двусвязного списка 1
	for (int i = 0; i < n; i++)	// заполнение списка
	{	
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> x;
		list1.push_back(x);
	}	// вставка введенного элемента в конец списка
	list<int>::iterator num;
	cout << "\nВведите количество элементов во втором списке: ";
	cin >> m;
	list<int> list2;	// объявление списка 2
	for (int i = 0; i < m; i++) 
	{
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> x;
		list2.push_back(x);
	}
	cout << "\nСписок 1: ";
	out(list1);
	cout << "Список 2: ";
	out(list2);
	list1.splice(list1.end(), list2, list2.begin(), list2.end());	// объединение списков в первый
	cout << "Список после слияния: ";
	out(list1);
	return 0;
}