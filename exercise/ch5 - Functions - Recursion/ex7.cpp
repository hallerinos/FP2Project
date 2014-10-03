# include <iostream>

int power( int a, int b);

int main()
{
	int a, b;
	std::cout << "a: ";
	std::cin >> a;
	std::cout << "b: ";
	std::cin >> b;
	std::cout << a << " to the power of " << b << " = " << power( a, b);
}

int power( int a, int b )
{
	if ( b == 0 )
		return 1;
	else
		return a*power( a, b-1 );
}
