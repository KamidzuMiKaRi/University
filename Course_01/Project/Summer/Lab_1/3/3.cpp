#include <iostream>
#include <fstream>
#include <string>

using namespace std;

    // инициализация структуры
struct schooler 
{
    char fio[50];
    char school[50];
    int clas;
    float avg_score;
};
    
    // запись списка в бин файл
void WriteToDat(schooler* schoolboys, int n, const char* filename) {
    ofstream f(filename, ios::binary);  // инициализация переменной
    if (!f) {
        cout << "Ошибка открытия файла для записи." << endl;
        exit(0);
    }
    f.write(reinterpret_cast<const char*>(&n), sizeof(int)); // записываем количество учеников в начало файла
    for (int i = 0; i < n; i++) {
        f.write(schoolboys[i].fio, sizeof(schoolboys[i].fio));
        f.write(schoolboys[i].school, sizeof(schoolboys[i].school));
        f.write(reinterpret_cast<const char*>(&schoolboys[i].clas), sizeof(int));
        f.write(reinterpret_cast<const char*>(&schoolboys[i].avg_score), sizeof(float));
    }
    f.close();
}

    // чтение списка из бин файла и вывода на экран учеников 10 класса
void Out_10(const char* filename) {
    ifstream f(filename, ios::binary);
    if (!f) 
    {
        cout << "Ошибка открытия файла для чтения." << endl;
        exit(0);
    }
    int n;
    f.read(reinterpret_cast<char*>(&n), sizeof(int)); // Читаем количество школьников из начала файла
    for (int i = 0; i < n; i++) 
    {
        schooler Schuler;
        f.read(Schuler.fio, sizeof(Schuler.fio));
        f.read(Schuler.school, sizeof(Schuler.school));
        f.read(reinterpret_cast<char*>(&Schuler.clas), sizeof(int));
        f.read(reinterpret_cast<char*>(&Schuler.avg_score), sizeof(float));
        if (Schuler.clas == 10) {
            cout << "Ученик " << i + 1 << ":" << endl;
            cout << "ФИО: " << Schuler.fio << endl;
            cout << "Школа: " << Schuler.school << endl;
            cout << "Класс: " << Schuler.clas << endl;
            cout << "Средний балл: " << Schuler.avg_score << endl;
            cout << endl;
        }
    }
    f.close();
}   

    // замена балла
void ReScore(const char* filename, int number, float new_score) 
{
    fstream f(filename, ios::binary | ios::in | ios::out);
    if (!f) 
    {
        cout << "Ошибка открытия файла." << endl;
        exit(0);
    }
    int n;
    f.read(reinterpret_cast<char*>(&n), sizeof(int));
    if (number < 0 || number >= n) 
    {
        cout << "Недопустимый номер ученика." << endl;
        f.close();
        return;
    }
    f.seekp(sizeof(int) + number * sizeof(schooler) + offsetof(schooler, avg_score), ios::beg);  // указатель чтения/записи к нужному классу
    f.write(reinterpret_cast<const char*>(&new_score), sizeof(float));      // новый средний балл
    f.close();
}   

    // вывод содержимого бинарного файла в текстовый файл или на экран
void OutDat(const char* filename, const char* Out_F = nullptr) {
    ifstream bin_f(filename, ios::binary);  // инициализация бин файла
    if (!bin_f) 
    {
        cout << "Ошибка открытия файла для чтения." << endl;
        exit(0);
    }
    int n;  // инициализация счетчика
    bin_f.read(reinterpret_cast<char*>(&n), sizeof(int));
    if (Out_F != nullptr) 
    {
        ofstream out_f(Out_F);
        if (!out_f) 
        {
            cout << "Ошибка открытия файла для записи." << endl;
            bin_f.close();
            exit(0);
        }
        for (int i = 0; i < n; i++) 
        {
            schooler schoolboy;
            bin_f.read(schoolboy.fio, sizeof(schoolboy.fio));
            bin_f.read(schoolboy.school, sizeof(schoolboy.school));
            bin_f.read(reinterpret_cast<char*>(&schoolboy.clas), sizeof(int));
            bin_f.read(reinterpret_cast<char*>(&schoolboy.avg_score), sizeof(float));
            out_f << "Ученик " << i + 1 << ":" << endl;
            out_f << "ФИО: " << schoolboy.fio << endl;
            out_f << "Школа: " << schoolboy.school << endl;
            out_f << "Класс: " << schoolboy.clas << endl;
            out_f << "Средний балл: " << schoolboy.avg_score << endl;
            out_f << endl;
        }
        out_f.close();
    }
    else 
    {
        for (int i = 0; i < n; i++) 
        {
            schooler schoolboy;
            bin_f.read(schoolboy.fio, sizeof(schoolboy.fio));
            bin_f.read(schoolboy.school, sizeof(schoolboy.school));
            bin_f.read(reinterpret_cast<char*>(&schoolboy.clas), sizeof(int));
            bin_f.read(reinterpret_cast<char*>(&schoolboy.avg_score), sizeof(float));

            cout << "Школьник " << i + 1 << ":" << endl;
            cout << "ФИО: " << schoolboy.fio << endl;
            cout << "Школа: " << schoolboy.school << endl;
            cout << "Класс: " << schoolboy.clas << endl;
            cout << "Средний балл: " << schoolboy.avg_score << endl;
            cout << endl;
        }
    }
    bin_f.close();
}

int main()
{
    setlocale(LC_ALL, "rus");
    int n = 0;
    cout << "Введите количество учеников: ";
    cin >> n;
    schooler* Schuler = new schooler[n];
    for (int i = 0; i < n; i++) 
    {
        cout << "Введите данные для ученика номер " << i + 1 << ":" << endl;
        cout << "ФИО: ";
        cin.ignore(); // игноририрование символа новой строки
        cin.getline(Schuler[i].fio, 50);
        cout << "Школа: ";
        cin.getline(Schuler[i].school, 50);
        cout << "Класс: ";
        cin >> Schuler[i].clas;
        cout << "Средний балл (от 0 до 10): ";
        cin >> Schuler[i].avg_score;
        cout << endl;
    }
    WriteToDat(Schuler, n, "schooler.dat");        // запись данных в бин файл
    delete[] Schuler;   
    cout << "Список учеников 10 класса:" << endl;   // чтение из файла и вывод на экран учеников 10 класса
    Out_10("schooler.dat");
    int number;  // выбираем нужного ученика
    float new_score;    // вводим новый средний балл
    cout << "Введите номер ученика, балл которого нужно изменить: ";
    cin >> number;
    number--;
    cout << "Введите новый средний балл: ";
    cin >> new_score;
    ReScore("schooler.dat", number, new_score);
    OutDat("schooler.dat", "schooler.txt");     // вывод содержимого бин файла в тхт файл
    return (101);   // при успешном завершении салютуем 101
}