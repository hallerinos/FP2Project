# include <iostream>

using namespace std;

void myFunction();

int x = 5, y = 7;

int main()
{

	cout << "x from main: " << x << endl;
	cout << "y from main: " << y << endl << endl;
	myFunction();
	cout << "Back from myFunction!" << endl << endl;
	cout << "x from main: " << x << endl;
	cout << "y from main: " << y << endl << endl;

	return 0;
}

void myFunction()
{
	int y = 10;
	cout << "x from myFunction: " << x << endl;					// uses global var x
	cout << "y from myFunction: " << y << endl << endl;	// uses local  var y
}
