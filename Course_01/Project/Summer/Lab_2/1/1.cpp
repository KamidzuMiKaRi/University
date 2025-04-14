#include <iostream>
#include <cstdlib>

using namespace std;

// чтобы не пользоваться ссылками и указателями, объявляю массивы и переменные до всех функций и мэйна
int N, Z;   // число чисел и необходимая сумма
int choice = 0; // число решений
int* arr; 
int* exodus; 

void goback(int now, int beginn, int length) 
{
    if (now == Z)    // если найдено решение
    {
        choice++;   // увеличиваем счетчик на 1
        cout << "Вариант " << choice << ": ";
        for (int i = 0; i < length; i++)    
        {
            cout << exodus[i] << " ";
        }
        cout << endl;
    }
    else if (now < Z) 
    {
        for (int i = beginn; i < N; i++) 
        {
            exodus[length] = arr[i]; // прибавляем число к решению
            goback(now + arr[i], i + 1, length + 1); // рекурсивный вызов для следующего шага
        }
    }
}

int main() 
{
    srand(time(NULL)); // инициализируем генератор случайных чисел
    setlocale(LC_ALL, "rus");
    cout << "Введите число натуральных чисел N: ";
    cin >> N;
    arr = new int[N]; // создание динамического массива для набора чисел
    exodus = new int[N]; 
    cout << "Заполняем поле случаынйми числами: ";
    for (int i = 0; i < N; i++) 
    {
        arr[i] = rand() % 9 + 1; // генерируем случайное число от 1 до 9;
    }
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\nВведите искомую сумму чисел: "; // поиск нужного числа
    cin >> Z;
    cout << "Возможные исходы:" << endl;
    goback(0, 0, 0);
    delete[] arr;      delete[] exodus; // удаление массивов
    return 0;
}
