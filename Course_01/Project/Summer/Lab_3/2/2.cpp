#include <iostream>
#include <cstdlib>
using namespace std;
struct Node 
{
	double data;
	Node* prev;
	Node* next;
};

class DoublyLinkedList {
private:
	Node* head, * tail;
public:
	DoublyLinkedList() {
		head = NULL;
		tail = NULL;
	}
	void insertAtBeginning(double num) {
		Node* newNode = new Node;
		newNode->data = num;
		if (head == NULL) {
			head = tail = newNode;
		}
		else {
			newNode->prev = head;
			head->next = newNode;
			head = newNode;
		}
		cout << "Number inserted at beginning: " << num << endl;
	}
	void insertAfter(double num, double afterNum) {
		Node* newNode = new Node;
		newNode->data = afterNum;
		Node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
		temp = newNode->next;
		// Make newNode point to the next node in the list
		newNode->prev = temp;
		cout << "Number inserted after: " << afterNum << endl;
	}
	void deleteNumber(double numToDelete) {
		int count = 0;
		for (Node* temp = head, *prev = head; temp != NULL; prev = temp, temp = temp->next) {
			if (temp->data == numToDelete) {
				if (prev == head) {
					head = temp;
				}
				else if (prev->next == temp) {
					prev->next = temp->next;
				}
				delete temp;
				count++;
			}
		}
		if (count == 1) {
			cout << "Element not found" << endl;
		}
	}
	void swapNumbers(double a, double b) {
		// swap a and b
		double temp = a;
		a = b;
		b = temp;
	}
	void printList() {
		for (Node* temp = head; temp; temp = temp->next) {
			cout << temp->data << " ";
		}
		cout << endl;
	}
};
int main() {
	DoublyLinkedList* list = new DoublyLinkedList;
	// Insert some elements in the list
	list->insertAtBeginning(1.0);
	list->insertAfter(2.0, 3.0);
	cout << "Press 1 to insert a number at beginning, " << endl
		<< "Press 2 to insert a number after another, " << endl
		<< "Press 3 to delete a number, " << endl
		<< "Press 4 to swap two numbers, " << endl
		<< "Press 5 to print the list, " << endl
		<< "Press q to quit." << endl << endl;
	char choice;
	do {
		cin >> choice;
		switch (choice) {
		case '1':
			double num;
			cout << "Enter a number to insert at beginning: ";
			cin >> num;
			list->insertAtBeginning(num);
			break;
		case '2':
			double a;
			double b;
			cout << "Enter two numbers to insert after each other: ";
			cin >> a >> b;
			list->insertAfter(a, b);
			break;
		case '3':
			double toDelete;
			cout << "Enter the number to delete: ";
			cin >> toDelete;
			list->deleteNumber(toDelete);
			break;
		case '4':
			double firstNum;
			double secondNum;
			cin >> firstNum >> secondNum;
			list->swapNumbers(firstNum, secondNum);
			break;
		case '5':
			list->printList();
			break;
		default:
			cout << "Invalid choice." << endl;
		}
	} while (choice != 'q');
	return 0;
}