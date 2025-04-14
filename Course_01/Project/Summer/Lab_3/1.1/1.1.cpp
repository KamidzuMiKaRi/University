#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	int data;
	Node* next;
};
Node* head = nullptr;

void createFile() 
{
	ofstream file("numbers.txt");
	if (file.is_open()) {
		cout << "Файл успешно создан" << endl;
		for (int i = 0; i < 20; i++) {
			file << i << " ";
		}
		file.close();
	}
	else {
		cout << "Ошибка при создании файла" << endl;
	}
}

void readFile() 
{
	ifstream file("numbers.txt");
	int num;
	while (file >> num) {
		Node* newNode = new Node;
		newNode->data = num;
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
	}
	file.close();
}

void printList() 
{
	Node* current = head;
	cout << "Список: " << endl;
	while (current != nullptr) 
	{
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl << endl;
}

void addElement(int value) 
{
	Node* newNode = new Node;
	newNode->data = value;
	if (head != nullptr) 
	{
		head->next = newNode;
	}
	else 
	{
		return;
	}
}

int main() 
{
	setlocale(LC_ALL, "rus");
	createFile();
	readFile();
	char choice;
	do 
	{
		printf("Выберите пункт меню:");
		printf("1. Формирование списка");
		printf("2. Добавление элемента");
		printf("3. Вывод списка");
		printf("4. Вывести элемент с заданным номером");
		printf("Введите номер пункта меню (1/2/3/4): ");
		cin >> choice;
		switch (choice) 
		{
		case '1':
			readFile();
			break;
		case '2':
			int value;
			cout << "Введите значение добавляемого элемента: ";
			cin >> value;
			addElement(value);
			break;
		case '3':
			printList();
			break;
		case '4':
			printf("Введите значение элемента: ");
			int num;
			cin >> num;
			Node* current = head;
			while (current != nullptr && current->data != num) {
				current = current->next;
			}
			if (current == nullptr) {
				cout << "Элемент отсутствует в списке." << endl;
			}
			else {
				printf("Адрес элемента с данным значением: %p", current);
				break;
			}
		default:
			cout << "Неверный пункт меню." << endl;
		}
	} while (choice != 'x');
	delete head;
	return 0;
}