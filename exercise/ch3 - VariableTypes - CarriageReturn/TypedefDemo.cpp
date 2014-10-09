# include <iostream>

typedef unsigned short int USHORT; // typedef defined
using namespace std;

int main()
{
	USHORT width, length, area;
	cout << "Type the length: " << endl;
	cin >> length;
	cout << "Type the width: " << endl;
	cin >> width;
	cout << "Area = " << (area = width*length ) << endl << endl;
	return 0;
}
