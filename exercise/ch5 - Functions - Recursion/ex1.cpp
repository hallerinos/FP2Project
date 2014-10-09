# include <iostream>

using namespace std;
typedef unsigned short int USHORT;

inline USHORT perimeter( USHORT a, USHORT b ); 

int main()
{
	int a, b;
	cout << "Give a value for a: ";
	cin >> a;
	cout << "Give a value for b: ";
	cin >> b;
	cout << "The Perimeter is: " << perimeter( a, b ) 
		<< endl << endl;
	unsigned short int x = 10;
	int y = x;
	cout << y;
	return 0;
}

USHORT perimeter( USHORT a, USHORT b )
{
	return 2*(a+b);
}
