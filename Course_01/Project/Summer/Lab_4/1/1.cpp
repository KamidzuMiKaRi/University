#include <iostream>
#include <fstream>

using namespace std;

    // Структура узла дерева
struct Node 
{
    int key;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        left = NULL;
        right = NULL;
    }
};

    // Вставка узла в дерево
Node* insertNode(Node* Tree, int key) 
{
    if (Tree == NULL)    // Если дерево пустое, вернуть новый узел
    {
        return new Node(key);
    }
    if (key < Tree->key) // Иначе рекурсивно вставить новый узел в подлежащее поддерево
    {
        Tree->left = insertNode(Tree->left, key);
    }
    else if (key > Tree->key) 
    {
        Tree->right = insertNode(Tree->right, key);
    }
    return Tree;
}

    // Обход дерева в порядке "Симметричный левый" (печать узлов в отсортированном порядке)
void inorderTraversal(Node* Tree) {
    if (Tree == NULL) {
        return;
    }
    inorderTraversal(Tree->left);
    cout << Tree->key << " ";
    inorderTraversal(Tree->right);
}

    // Обход дерева боком (символ '>' означает правое поддерево, '<' - левое поддерево)
void prettyPrint(Node* node, string prefix = "", bool isLeft = true) 
{
    if (node == NULL) 
    {
        return;
    }
    cout << prefix;
    cout << (isLeft ? "I--" : "L_");
    cout << "(" << node->key << ")" << endl;   
    prettyPrint(node->left, prefix + (isLeft ? "I   " : "    "), true);  // Рекурсивно вызывать эту функцию для каждого из потомков
    prettyPrint(node->right, prefix + (isLeft ? "I   " : "    "), false);
}

    // Поиск узла по ключу
Node* findNode(Node* Tree, int key) 
{
    if (Tree == NULL || Tree->key == key)   // Если дерево пустое или ключ узла равен ключу поиска, вернуть узел
    {
        return Tree;
    }
    if (Tree->key > key)    // Если ключ узла больше ключа поиска, рекурсивно искать в левом поддереве
    {
        return findNode(Tree->left, key);
    }
    return findNode(Tree->right, key);   // Иначе рекурсивно искать в правом поддереве
}

int main() 
{
    setlocale(LC_ALL, "rus");
    ifstream f("numb.txt"); // Чтение целых чисел из текстового файла
    int number; // Переменная контейнер
    Node* Tree = NULL;
    while (f >> number)     // Перебираем каждое число
    {
        Tree = insertNode(Tree, number);
    }
    cout << "Отсортированные значения узлов дерева: ";  // Вывод отсортированных значений узлов дерева
    inorderTraversal(Tree);
    cout << endl;
    cout << "Дерево боком: " << endl;   // Вывод дерева боком
    prettyPrint(Tree);
    int key;     // Поиск узла по ключу, введенному пользователем
    cout << "Введите ключ узла для поиска: ";
    cin >> key;
    Node* foundNode = findNode(Tree, key);
    if (foundNode) 
    {
        cout << "Адрес узла с ключом " << key << ": " << foundNode << endl;
    }
    else 
    {
        cout << "Узел с ключом " << key << " не найден" << endl;
    }
    return 0;
}