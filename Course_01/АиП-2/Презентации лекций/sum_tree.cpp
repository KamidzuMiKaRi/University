#include <iostream>

using namespace std;

struct Node
{
int key; // информационное поле (ключ)
Node *left, *right; // указатели на сыновей
};

typedef Node *PNode; // указатель на вершину

//PNode Tree = new Node; //создали вершину дерева
int min2 = 10000, sum2 = 0;
int min3 = 10000, sum3 = 0;

PNode MakeTree (int data[], int from, int n)
{
PNode Tree;
int n1, n2;
if ( n == 0 ) return NULL; // ограничение рекурсии
Tree = new Node; // выделить память под вершину
Tree->key = data[from]; // записать данные (ключ)
n1 = n / 2; // размеры поддеревьев
n2 = n - n1 - 1;
Tree->left = MakeTree(data, from+1, n1);
Tree->right = MakeTree(data, from+1+n1, n2);
return Tree;
}

void PrintTree(PNode Tree, int h) //печать дерева
{
	int i;
       if (Tree!=NULL)
	 {
         PrintTree(Tree->right, h + 1); //спуск в правое поддерево и определение количества //уровней h, чтобы определить, сколько групп пробелов необходимо поставить перед значением
         for (i=1; i<=h; i++)  //вывод h групп пробелов
		  cout<<"    ";
         cout<<Tree->key<<endl; //вывод ключа
	  cout<<endl;
         PrintTree(Tree->left, h + 1); //спуск в левое поддерево
	}
}

int min_sum1(PNode Tree)
{
     if (Tree == NULL) return 0;
      else if ((Tree->left == NULL) && (Tree->right == NULL)) return Tree->key;
      else if((Tree->left != NULL) && (Tree->right != NULL))
         return Tree->key + min(min_sum1(Tree->left), min_sum1(Tree->right));
           else if(Tree->left==NULL)
            return Tree->key + min_sum1(Tree->right);
             else if(Tree->right==NULL)
                return Tree->key + min_sum1(Tree->left);
}

void min_sum2(PNode Tree)
{
    if(Tree!=NULL)
    {
        sum2+=Tree->key;
        if ((Tree->left==NULL) && (Tree->right==NULL) && (sum2<min2))
           min2 = sum2;
        min_sum2(Tree->left);
        min_sum2(Tree->right);
        sum2-=Tree->key;
    }
}

void min_sum3(PNode Tree)
{
  if (Tree != NULL)
   {
      sum3 += Tree->key;
      if (sum3<min3)
      {
        if ((Tree->left==NULL) && (Tree->right==NULL)) min3 = sum3;
        else if(Tree->right==NULL) min_sum3(Tree->left);
         else if (Tree->left==NULL)  min_sum3(Tree->right);
          else
            (Tree->left->key<Tree->right->key)? min_sum3(Tree->left) : min_sum3(Tree->right);
      }

  }
}



int main()
{
    int mas[50];
    int i, n, h=0;
    cout<<"n= ";
    cin>>n;
    cout<<"mas = ";
    for(i=0;i<n;i++)
        cin>>mas[i];
    PNode Tree = new Node; //создали вершину дерева
    Tree = MakeTree(mas, 0, n);
    PrintTree(Tree, h);
    cout<<"sum1 = "<<min_sum1(Tree);
    cout<<endl;
    min_sum2(Tree);
    cout<<"sum2 = "<<min2;
    cout<<endl;
    min_sum3(Tree);
    cout<<"sum3 = "<<min3;

}
