#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// заполнение файла рандомными числами
void frand(int n, const string& filename)
{
	ofstream f(filename);
	for (int i = 0; i < n; i++)
	{
		f << (rand()) << " ";
	}
}

// проверка бинарных чисел
void out(const char* binaryfile)
{
	ifstream f(binaryfile, ios_base::binary);
	int n;
	while (f.peek() != EOF)
	{
		f.read((char*)&n, sizeof(n));
		cout << n << " ";
	}
	f.close();
}

// замена указанной переменной
void swap(const char* binaryfile, int n)
{
	int x;
	fstream bin(binaryfile, ios_base::out | ios_base::in | ios_base::binary);
	bin.seekg((n - 1) * sizeof(int), ios::beg);
	bin.read((char*)&x, sizeof(x));
	x = x * 2 - 9;
	bin.seekg((n - 1) * sizeof(int), ios::beg);
	bin.write((char*)&x, sizeof(x));
	bin.close();
}

// проверка простоты числа
bool Prime(int x)
{
	if (x < 2)
		return 0;
	for (int i = 2; i <= sqrt(x); i++)
		if (x % i == 0)
			return 0;
	return 1;
}

int main()
{
	srand(time(NULL));	// создание отправной точки в генерации чисел
	setlocale(LC_ALL, "rus");
	int i = 0, n, x;
	fstream f, bin, easy, comp;	// объявление переменных
	f.open("f.txt", ios_base::out);	// открытие текстового файла в режиме записи
	if (f.fail())
	{
		cout << "Ошибка открытия файла";
		exit(0);
	}
	n = rand() % (30 - 20 + 1) + 20;	// задание рандомного числа чисел
	frand(n, "f.txt");	// вызов функции заполения тестового файла
	f.close();	// закрытие текстового файла
	f.open("f.txt", ios_base::in);	// открытие текстового файла в режиме чтения
	bin.open("fbin.dat", ios_base::binary | ios::out); // открытие бин файла в редиме записи
	if (bin.fail())
	{
		cout << "Ошибка открытия файла";
		exit(0);
	}
	while (f >> x)	// пока читается текстовый файл, записывать его в бин файл
		bin.write((char*)&x, sizeof(x));
	bin.close();	// закрыть бин файл
	f.close();	// закрыть текст файл
	cout << "Элементы бинарного файла:" << endl;	// вывод содержимого бин файла
	out("fbin.dat");
	cout << "\nКакую запись стоит изменить? Введите номер: ";	// диалог
	cin >> n;
	swap("fbin.dat", n); // вызов функции по замене n-ого элемента
	cout << "Элементы бинарного файла:" << endl;
	out("fbin.dat");	// вывод содержимого измененного файла
	bin.close();
	bin.open("fbin.dat", ios_base::binary | ios::in);	// открытие файла в режиме чтение
	if (bin.fail())
	{
		cout << "\nОшибка открытия файла";
		exit(0);
	}
	easy.open("easy.dat", ios_base::binary | ios_base::out);	// открытие в режиме запись
	if (easy.fail())
	{
		cout << "\nОшибка открытия файла";
		exit(0);
	}
	comp.open("compos.dat", ios_base::binary | ios_base::out);	// открытие в режиме запись
	if (comp.fail())
	{
		cout << "\nОшибка открытия файла";
		exit(0);
	}
	while (bin.read((char*)&i, sizeof(i)))	// считываем элемент
	{
		if (Prime(i)) 	// в зависимости от возвращенного результата
			easy.write((char*)&i, sizeof(i));	// пишем в простые числа, если 0
		else
			comp.write((char*)&i, sizeof(i)); // пишем в составные числа, если 1
	}
	bin.close();	// закрытие файлов
	easy.close();
	comp.close();
	cout << "\nПростые числа:" << endl;	// вывод простых чисел
	out("easy.dat");
	cout << "\nСоставные числа:" << endl;	// вывод составных чисел
	out("compos.dat");
}