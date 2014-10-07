# include <iostream>

using namespace std;

int main() 
{
	int localVariable = 5;
	int *pLocal = &localVariable;
	int *pHeap = new int;

	*pHeap = 7;

	cout << "localVariable: " << localVariable << endl;
	cout << "*pLocal: " << *pLocal << endl;
	cout << "*pHeap: " << *pHeap << endl << endl;

	delete pHeap;

	pHeap = new int;
	*pHeap = 9;

	cout << "After delete, reassigning *pHeap = 9..." << endl;
	cout << "*pHeap: " << *pHeap << endl;
	delete pHeap;
	
	return 0;
}
