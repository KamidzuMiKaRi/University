#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int n,m;

void printlab(char **lab)
{
	int i,j;
	cout<<"--------------------------------"<<'\n';
	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
			cout<<lab[i][j];
		cout<<'\n';
	}
}

void go(char **&lab, int x,int y)
{
	if (lab[x][y]==' ') //клетка свободна
	{
		lab[x][y]='+'; //шаг в клетку
		if ((x==0)||(x==n-1)||(y==0)||(y==m-1)) //край
			printlab(lab);
		else
		{
			go(lab,x+1,y);
			go(lab,x-1,y);
			go(lab,x,y+1);
			go(lab,x,y-1);
		}
     lab[x][y]=' '; //возвращение назад
	}
}
int main()
{
	int j,i;
	string s;
   	cin>>n>>m;
	char **lab;
	lab=new char *[n];
	for (i=0;i<n;i++)
		lab[i]=new char[m];
	cin.ignore(); //необходим, чтобы пропустить в конце предыдущей строки символ //перехода на новую строку, чтобы он не считывался командой getline
	for (i=0;i<n;i++)
	{
	   getline(cin,s);
	   for (j=0;j<m;j++)
		    lab[i][j]=s[j];

	}
	go(lab,n/2,m/2);

}
