# include <iostream>

int main()
{
	int x = 0;
	// curly brackets are important!
	if ( false ) {
		x++;
		x--;
	}
	std::cout << x;
	return 0;
}
