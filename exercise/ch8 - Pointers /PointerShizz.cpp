# include <iostream>

using namespace std;

int main() {


	int * pAge = 0;
	cout << "Size of an adress to an int: " << sizeof(* pAge) << endl;

	int var1 = 10;
	int var2 = 20;

	int *pVar1 = 0;
	int *pVar2 = 0;
	pVar1 = &var1;
	pVar2 = &var2;

	cout << "At this point: exact copy of var1 & var2..." << endl;	
	cout << "var1: " << var1 << ", *pVar1: " << *pVar1 << endl;
	cout << "var2: " << var2 << ", *pVar2: " << *pVar2 << endl;

	*pVar1 = var2;
	*pVar2 = var1;	
	
	cout << "By changing the assigned value of pVar1 to var2"
	 " and then pVar2 to var1" << endl;	
	cout << "var1: " << var1 << ", *pVar1: " << *pVar1 << endl;
	cout << "var2: " << var2 << ", *pVar2: " << *pVar2 << endl;
	
	return 0;
}
