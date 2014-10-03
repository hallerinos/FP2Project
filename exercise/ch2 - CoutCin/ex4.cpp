#include <iostream>

int Subtract( int first, int second )
{
	std::cout << "In Subtract(), received " << first << " and "
		<< second << std::endl;
	return ( first - second );
}

int main()
{
	using std::cout;
	using std::endl;
	using std::cin;

	cout << "I'm in main()!" << endl;
	int a, b, c;
	cout << "Enter two numbers: " << endl;
	cin >> a;
	cin >> b;
	cout << "Calling Subtract()" << endl;
	c = Subtract( a, b );
	cout << "Back in main()." << endl;
	cout << "c was set to " << c << endl;
	cout << "Exiting..." << endl << endl;
	return 0;
}
