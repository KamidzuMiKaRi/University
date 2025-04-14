#include <iostream>
#include <fstream>
#include <cstring>
#include<windows.h>


using namespace std;

const int MAX_FIO_LENGTH = 50;
const int MAX_SCHOOL_NAME_LENGTH = 50;

// Структура "школьник"
struct Schoolboy {
    char fio[MAX_FIO_LENGTH];
    char school[MAX_SCHOOL_NAME_LENGTH];
    int grade;
    float averageScore;
};

// Функция записи списка школьников в бинарный файл
void writeSchoolboysToFile(Schoolboy* schoolboys, int n, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Ошибка открытия файла для записи." << endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&n), sizeof(int)); // Записываем количество школьников в начало файла

    for (int i = 0; i < n; i++) {
        file.write(schoolboys[i].fio, sizeof(schoolboys[i].fio));
        file.write(schoolboys[i].school, sizeof(schoolboys[i].school));
        file.write(reinterpret_cast<const char*>(&schoolboys[i].grade), sizeof(int));
        file.write(reinterpret_cast<const char*>(&schoolboys[i].averageScore), sizeof(float));
    }

    file.close();
}

// Функция чтения списка школьников из бинарного файла и вывода на экран школьников с баллом выше 5
void readAndPrintSchoolboys(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    int n;
    file.read(reinterpret_cast<char*>(&n), sizeof(int)); // Читаем количество школьников из начала файла

    for (int i = 0; i < n; i++) {
        Schoolboy schoolboy;
        file.read(schoolboy.fio, sizeof(schoolboy.fio));
        file.read(schoolboy.school, sizeof(schoolboy.school));
        file.read(reinterpret_cast<char*>(&schoolboy.grade), sizeof(int));
        file.read(reinterpret_cast<char*>(&schoolboy.averageScore), sizeof(float));

        if (schoolboy.averageScore > 5.0) {
            cout << "Школьник " << i + 1 << ":" << endl;
            cout << "ФИО: " << schoolboy.fio << endl;
            cout << "Школа: " << schoolboy.school << endl;
            cout << "Класс: " << schoolboy.grade << endl;
            cout << "Средний балл: " << schoolboy.averageScore << endl;
            cout << endl;
        }
    }

    file.close();
}

// Функция замены балла заданного школьника в бинарном файле
void replaceScore(const char* filename, int index, float newScore) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Ошибка открытия файла." << endl;
        return;
    }

    int n;
    file.read(reinterpret_cast<char*>(&n), sizeof(int));
    if (index < 0 || index >= n) {
        cout << "Недопустимый индекс школьника." << endl;
        file.close();
        return;
    }

    // Перемещаем указатель чтения/записи к нужному школьнику
    file.seekp(sizeof(int) + index * sizeof(Schoolboy) + offsetof(Schoolboy, averageScore), ios::beg);

    // Записываем новый средний балл
    file.write(reinterpret_cast<const char*>(&newScore), sizeof(float));

    file.close();
}

// Функция вывода содержимого бинарного файла в текстовый файл или на экран
void printBinaryFile(const char* filename, const char* outputFilename = nullptr) {
    ifstream binaryFile(filename, ios::binary);
    if (!binaryFile) {
        cout << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    int n;
    binaryFile.read(reinterpret_cast<char*>(&n), sizeof(int));

    if (outputFilename != nullptr) {
        ofstream outputFile(outputFilename);
        if (!outputFile) {
            cout << "Ошибка открытия файла для записи." << endl;
            binaryFile.close();
            return;
        }

        for (int i = 0; i < n; i++) {
            Schoolboy schoolboy;
            binaryFile.read(schoolboy.fio, sizeof(schoolboy.fio));
            binaryFile.read(schoolboy.school, sizeof(schoolboy.school));
            binaryFile.read(reinterpret_cast<char*>(&schoolboy.grade), sizeof(int));
            binaryFile.read(reinterpret_cast<char*>(&schoolboy.averageScore), sizeof(float));

            outputFile << "Школьник " << i + 1 << ":" << endl;
            outputFile << "ФИО: " << schoolboy.fio << endl;
            outputFile << "Школа: " << schoolboy.school << endl;
            outputFile << "Класс: " << schoolboy.grade << endl;
            outputFile << "Средний балл: " << schoolboy.averageScore << endl;
            outputFile << endl;
        }

        outputFile.close();
    }
    else {
        for (int i = 0; i < n; i++) {
            Schoolboy schoolboy;
            binaryFile.read(schoolboy.fio, sizeof(schoolboy.fio));
            binaryFile.read(schoolboy.school, sizeof(schoolboy.school));
            binaryFile.read(reinterpret_cast<char*>(&schoolboy.grade), sizeof(int));
            binaryFile.read(reinterpret_cast<char*>(&schoolboy.averageScore), sizeof(float));

            cout << "Школьник " << i + 1 << ":" << endl;
            cout << "ФИО: " << schoolboy.fio << endl;
            cout << "Школа: " << schoolboy.school << endl;
            cout << "Класс: " << schoolboy.grade << endl;
            cout << "Средний балл: " << schoolboy.averageScore << endl;
            cout << endl;
        }
    }

    binaryFile.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    cout << "Введите количество школьников: ";
    cin >> n;

    Schoolboy* schoolboys = new Schoolboy[n];

    for (int i = 0; i < n; i++) {
        cout << "Введите данные для школьника " << i + 1 << ":" << endl;
        cout << "ФИО: ";
        cin.ignore(); // Игнорируем символ новой строки
        cin.getline(schoolboys[i].fio, MAX_FIO_LENGTH);
        cout << "Школа: ";
        cin.getline(schoolboys[i].school, MAX_SCHOOL_NAME_LENGTH);
        cout << "Класс: ";
        cin >> schoolboys[i].grade;
        cout << "Средний балл (от 0 до 10): ";
        cin >> schoolboys[i].averageScore;
        cout << endl;
    }

    // Записываем данные в бинарный файл
    writeSchoolboysToFile(schoolboys, n, "schoolboys.dat");

    delete[] schoolboys;

    // Читаем данные из файла и выводим на экран школьников с баллом выше 5
    cout << "Список школьников со средним баллом выше 5:" << endl;
    readAndPrintSchoolboys("schoolboys.dat");

    // Заменяем балл заданного школьника в бинарном файле
    int index;
    float newScore;

    cout << "Введите индекс школьника, чей балл нужно заменить: ";
    cin >> index;
    cout << "Введите новый средний балл: ";
    cin >> newScore;

    replaceScore("schoolboys.dat", index, newScore);

    // Выводим содержимое бинарного файла в текстовый файл
    printBinaryFile("schoolboys.dat", "schoolboys.txt");

    return 0;
}
