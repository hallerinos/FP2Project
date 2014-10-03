# include <iostream>

using namespace std;

int main()
{
	int intVar = -1;
	unsigned int uIntVar = intVar;
	signed int sIntVar = intVar;
	cout << "Assign an integer " << intVar << " to:" << endl;
	cout << "A signed variable: " << sIntVar << endl;
	cout << "And to an unsigned variable:" << uIntVar << endl << endl;
	return 0;
}
