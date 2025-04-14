#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "rus");
	int n, m, x;	// объявление переменных
	cout << "Введите количество элементов в первом списке: ";
	cin >> n;
	list<int> list1;	// объявление двусвязного списка 1
	for (int i = 0; i < n; i++)	{	// заполнение списка
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> x;
		list1.push_back(x);}	// вставка введенного элемента в конец списка
	cout << endl;
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) {
		cout << *it << " ";
	}
	cout << "\nВведите количество элементов во втором списке: ";
	cin >> m;
	list<int> list2(m);	// объявление списка 2
	for (int i = 0; i < m; i++)	{
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> x;
		list2.push_back(x);}
	for (list<int>::iterator df = list2.begin(); df != list2.end(); df++) {
		cout << *df << " ";
	}
	cout << endl;
	for (list<int>::iterator ti = list1.begin(); ti != list1.end(); ti++) {	// вывод списка 1
		cout << *ti << " ";}
	cout << endl;
	for (list<int>::iterator ty = list2.begin(); ty != list2.end(); ty++) {	// вывод списка 2
		cout << *ty << " ";}
	cout << endl;
	list1.splice(list1.end(), list2, list2.begin(), list2.end());	// объединение списков в первый
	cout << "Список после слияния: ";
	for (list<int>::iterator we = list1.begin(); we != list1.end(); we++) {
		cout << *we << " ";}
	list1.remove(0);	// удаление из списка всех 0
	cout << "\nСписок после удаления 0: ";	
	for (list<int>::iterator qw = list1.begin(); qw != list1.end(); qw++) {
		cout << *qw << " ";	}
	return 0;
}