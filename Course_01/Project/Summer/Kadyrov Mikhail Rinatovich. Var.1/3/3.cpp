#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int n = 5; // количество элементов в массиве
	vector<int> arr(n); // создание динамического массива
	// заполнение массива случайными числами
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 40 - 20;	// заполнение массива числами 
		cout << arr[i] << " ";
	}
	cout << endl;
	// вставка нуля перед нечетными элементами
	int index = 0;
	for (int i = 0; i < n; i++)	 // вставка нуля перед каждым нечетным элементом
	{
		if ((abs(arr[i]) % 2) == 1)
		{
			arr.insert(arr.begin()+i, 0);
			n++;
			i++;
		}
	}
	cout << "После вставки нуля: ";
	for (int j = 0; j < n; j++) 
	{
		cout << arr[j] << " ";
	}
	cout << endl;
	index = 0;	// обнуление счетчика
	for (int i = 0; i < n; i++)	 // удаление отрицательных элементов
	{
		if (arr[i] < 0)
		{
			arr.erase(arr.begin() + i);
			i--;
			n--;
		}
	}
	cout << "Массив после удаления отрицательных элементов: ";
	for (int m = 0; m < n; m++) 
	{
		cout << arr[m] << " ";
	}
	cout << endl << endl;
	int middle = n / 2;
	// сортировка средних 10 элементов массива по возрастанию
	sort(arr.begin(), arr.begin() + middle);
	cout << "Отсортированные средние элементы: ";
	for (int o = 0; o < middle; o++) {
		cout << arr[o] << " ";
	}
	cout << endl;
	return 0;
}
