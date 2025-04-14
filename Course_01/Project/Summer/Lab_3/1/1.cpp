#include <iostream>
#include <fstream>

using namespace std;

struct Node 
{
    int nx;
    Node* PNext;  // переход на следующий элемент списка
};

// формирование списка из файла
void newList(Node** head) 
{
    ifstream f("numb.txt");
    if (!f.is_open()) 
    {
        cout << "Ошибка открытия файла" << endl;
        return;
    }
    int num;    // переменная-контейнер для записи
    while (f >> num) 
    {
        Node* newNode = new Node;
        newNode->nx = num;
        newNode->PNext = NULL;
        if (*head == NULL) 
        {
            *head = newNode;
        }
        else 
        {
            Node* temp = *head;
            while (temp->PNext != NULL) 
            {
                temp = temp->PNext;
            }
            temp->PNext = newNode;
        }
    }
    cout << "Список сформирован" << endl;
    f.close();
}

// добавление элемента в список с клавиатуры
void addEL(Node** head, int value) {
    Node* newNode = new Node;
    newNode->nx = value;
    newNode->PNext = NULL;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* temp = *head;
        while (temp->PNext != NULL) {
            temp = temp->PNext;
        }
        temp->PNext = newNode;
    }
}

// вывод всех элементов списка
void out(Node* head) 
{
    if (head == NULL) // если пусто, то сообщаем об этом и возвращаемся в меню
    {
        cout << "Ничего нет" << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL)    // пока текущий элемент не пустой, выводим его и переходим к следующему элементу списка
    {
        cout << temp->nx << " ";
        temp = temp->PNext;
    }
    cout << endl;
}

// вывод запрошенного жлемента, если он есть в списке
void adress_EL(Node* head, int n) 
{
    if (head == NULL)
    {
        cout << "Ничего нет" << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL)
    {
        if (temp->nx == n) 
        {
            cout << "Элемент с указанным значением "<< n <<" есть в списке" << endl;
            return;
        }
        temp = temp->PNext;
    }
    cout << "Элемент со значением " << n << " отсутствует в списке" << endl;
}

int main() 
{
    setlocale(LC_ALL, "rus"); 
    Node* head = NULL;  // указатель на голову
    int Choice, i, value;   // переменные для меню
    do 
    {
        cout << "Выберите действие:" << endl;
        cout << "1. Сформировать список" << endl;
        cout << "2. Добавить элемент списка с клавиатуры" << endl;
        cout << "3. Вывод списка" << endl;
        cout << "4. Вывод элемента с конкретным значением" << endl;
        cout << "0. Выход" << endl;
        cout << "\nВыполнить пункт: ";
        cin >> Choice;
        switch (Choice) 
        {
            case 1:
                newList(&head); // вызов функции со списком в параметрах
                break;
            case 2:
                cout << "Введите значение добавляемого элемента: ";
                cin >> value;
                addEL(&head, value);    // вызов функции со указателем на список и числом в параметрах для добавления в конец списка
                break;
            case 3:
                out(head);  // вызов функции вывода на экран со списком в параметрах
                break;
            case 4:
                cout << "Введите значение элемента: ";
                cin >> i;
                adress_EL(head, i); // вызов функции для вывода конкретного числа из списка
                break;
            case 0:
                cout << "Программа завершена." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        cout << endl;
    } while (Choice != 0);  // цикл меню, который не кончится, пока не выберем 0
    Node* temp;  // освобождение памяти, если по правильному делать
    while (head != NULL)
    {
        temp = head;
        head = head->PNext;
        delete temp;
    }
    return 0;
}