#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void printVector(vector<int>& vec)	// вывод вектора
{
	cout << "Массив чисел: ";
	for (int i = 0; i < vec.size(); i++)	// пока i меньше размера вектора
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

int main() 
{
	setlocale(LC_ALL, "rus");
	ifstream f("input.txt");
	vector<int> arr;
	int n;
	f >> n;
	while (f >> n) arr.push_back(n);
	int evenCount = 0, oddCount = 0;	// считаем количество четных и нечетных элементов
	for (auto& num : arr) 
	{
		if (num % 2 == 0) 
		{
			evenCount++;
		}
		else 
		{
			oddCount++;
		}
	}
	cout << "Кол-во четных чисел: " << evenCount << endl;
	cout << "Кол-во нечетных чисел: " << oddCount << endl;
	sort(arr.begin(), arr.end());	// сортируем массив по убыванию
	printVector(arr);
	return 0;
}