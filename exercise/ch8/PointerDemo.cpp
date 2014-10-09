# include <iostream>

using namespace std;
typedef unsigned short int USHORT;

int main ()
{
	USHORT myAge;
	USHORT *pAge = 0;

	myAge = 5;

	cout << "myAge: " << myAge << endl;
	pAge = &myAge;
	cout << "*pAge: " << *pAge << endl << endl;
	
	cout << "Setting *pAge = 7... " << endl;
	*pAge = 7;

	cout << "*pAge: " << *pAge << endl;
	cout << "myAge: " << myAge << endl << endl;

	cout << "Setting myAge = 9... " << endl;
	myAge = 9;
	cout << "myAge: " << myAge << endl;
	cout << "*pAge: " << *pAge << endl;


	return 0;
}
