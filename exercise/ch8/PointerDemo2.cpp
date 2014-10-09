# include <iostream>

using namespace std;

int main()
{
	unsigned short int myAge = 5, yourAge = 10;

	unsigned short int *pAge = &myAge;

	cout << "myAge:\t" << myAge << "\t\tyourAge:\t" << yourAge << endl;
	cout << "&myAge:\t"<< &myAge<< "\t&yourAge:\t"  << &yourAge<< endl;

	cout << "pAge:\t" << pAge << endl;
	cout << "*pAge:\t"<< *pAge << endl;

	cout << "\nReassigning: pAge = &yourAge..." << endl << endl;
	pAge = &yourAge;

	cout << "myAge:\t" << myAge << "\t\tyourAge:\t" << yourAge << endl;
	cout << "&myAge:\t"<< &myAge<< "\t&yourAge:\t"  << &yourAge<< endl;

	cout << "pAge:\t" << pAge << endl;
	cout << "*pAge:\t"<< *pAge << endl;

	return 0;
}
