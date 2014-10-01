# include <iostream>

using namespace std;

int main()
{
	int a, b;
	cout << "Enter two integer numbers: " << endl;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	a = ( a > b ) ? b : b = a;
	cout << "a = " << a << endl << "b = " << b << endl;
	return 0;
}	
