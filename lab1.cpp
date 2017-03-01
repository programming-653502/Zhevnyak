#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

int main ()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i,k;
	char a[30];
	cout<<"Введите k-ую позицию,которую хотите определить:";
	cin>>k;

	i=1;
	while(k>0) {
		itoa(i*i, a, 10);
		k -= strlen(a);
		i++;
	}
	k += strlen(a);
	cout << a[k-1] << endl;
	getch();
	return 0;
}
