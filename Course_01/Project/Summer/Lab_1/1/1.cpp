#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct subj     // структура предметов
{ 
    string subject;
    int grade{};
};

int const NoI = 5; // константа количества предметов

struct stud      // структура студентов
{
    string fio;
    string fac;
    string group;
    subj arr[NoI];
};

int const NoS = 5; // константа количества студентов

stud StInfo[NoS]; // объявляем массив структур student

void avg()          // функция вывода на экран списка студентов со средним баллом выше 41
{
    float Avg = 0;
    for (int i = 0; i < NoS; i++) // перебор учеников
    {
        for (int j = 0; j < NoI; j++) // перебор предметов
        {
            Avg += StInfo[i].arr[j].grade; // сумма балллов всех предметов
        }
        Avg = Avg / NoI; // средний балл по всем предметам
        if (Avg > 41)    // вывод ФИО студента, если его средний балл выше 41
        {
            cout << "У студента " << StInfo[i].fio << " балл выше 41. Средний балл: " << Avg << endl;
        }
        Avg = 0; // обнуление
    }
}

int main() 
{
    setlocale(LC_ALL, "rus");

    // инициализация массива струтур student

    StInfo[0].fio = "Кадыров Михаил Ринатович";
    StInfo[0].fac = "Институт IT";
    StInfo[0].group = "ИТЗ-2023";
    StInfo[0].arr[0].subject = "АиП-2";
    StInfo[0].arr[0].grade = 41;
    StInfo[0].arr[1].subject = "Английский язык";
    StInfo[0].arr[1].grade = 25;
    StInfo[0].arr[2].subject = "Теоретические основы информатики";
    StInfo[0].arr[2].grade = 54;
    StInfo[0].arr[3].subject = "Алгебра";
    StInfo[0].arr[3].grade = 15;
    StInfo[0].arr[4].subject = "Математический анализ";
    StInfo[0].arr[4].grade = 70;

    StInfo[1].fio = "Муравьёва Зинаида Петровна";
    StInfo[1].fac = "Институт IT";
    StInfo[1].group = "ИТЗ-2023";
    StInfo[1].arr[0].subject = "АиП-2";
    StInfo[1].arr[0].grade = 60;
    StInfo[1].arr[1].subject = "Английский язык";
    StInfo[1].arr[1].grade = 54;
    StInfo[1].arr[2].subject = "Теоретические основы информатики";
    StInfo[1].arr[2].grade = 74;
    StInfo[1].arr[3].subject = "Алгебра";
    StInfo[1].arr[3].grade = 68;
    StInfo[1].arr[4].subject = "Математический анализ";
    StInfo[1].arr[4].grade = 83;

    StInfo[2].fio = "Нечаев Сергей Алексеевич";
    StInfo[2].fac = "Механико-математический";
    StInfo[2].group = "ИТЗ-2023";
    StInfo[2].arr[0].subject = "Физическая культура";
    StInfo[2].arr[0].grade =100;
    StInfo[2].arr[1].subject = "Английский язык";
    StInfo[2].arr[1].grade = 19;
    StInfo[2].arr[2].subject = "Теоретические основы информатики";
    StInfo[2].arr[2].grade = 5;
    StInfo[2].arr[3].subject = "Алгебра";
    StInfo[2].arr[3].grade = 53;
    StInfo[2].arr[4].subject = "Математический анализ";
    StInfo[2].arr[4].grade = 36;

    StInfo[3].fio = "Дмитрий Сергеевич Сеченов";
    StInfo[3].fac = "Институт IT";
    StInfo[3].group = "ИТЗ-2023";
    StInfo[3].arr[0].subject = "АиП-2";
    StInfo[3].arr[0].grade = 93;
    StInfo[3].arr[1].subject = "Английский язык";
    StInfo[3].arr[1].grade = 94;
    StInfo[3].arr[2].subject = "Теоретические основы информатики";
    StInfo[3].arr[2].grade = 84;
    StInfo[3].arr[3].subject = "Алгебра";
    StInfo[3].arr[3].grade = 74;
    StInfo[3].arr[4].subject = "Математический анализ";
    StInfo[3].arr[4].grade = 69;

    StInfo[4].fio = "Захаров Харитон Радеонович";
    StInfo[4].fac = "Институт IT";
    StInfo[4].group = "ИТЗ-2023";
    StInfo[4].arr[0].subject = "АиП-2";
    StInfo[4].arr[0].grade = 83;
    StInfo[4].arr[1].subject = "Английский язык";
    StInfo[4].arr[1].grade = 98;
    StInfo[4].arr[2].subject = "Теоретические основы информатики";
    StInfo[4].arr[2].grade = 98;
    StInfo[4].arr[3].subject = "Алгебра";
    StInfo[4].arr[3].grade = 98;
    StInfo[4].arr[4].subject = "Математический анализ";
    StInfo[4].arr[4].grade = 100;

    ofstream f; 
    f.open("std_congr.txt", ios::out); // открытие файла
    for (int i = 0; i < NoS; i++)   // перебор студентов
    {
        f << "Студент - " << StInfo[i].fio << endl;
        f << "Факультет - " << StInfo[i].fac << endl;
        f << "Группа - " << StInfo[i].group << endl;
        for (int j = 0; j < NoI; j++)   // перебор предметов
        {
            f << "Предмет - " << StInfo[i].arr[j].subject << endl;
            f << "Оценка: " << StInfo[i].arr[j].grade << endl;
        }
        f << endl << endl;
    }
    f.close();      // закрываем файл
    avg();      // вызов функции среднего балла
    return 0;
}