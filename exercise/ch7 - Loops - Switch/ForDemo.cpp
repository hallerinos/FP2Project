# include <iostream>

int main()
{
	// if defined in for ( int counter = 0 ), counter is private
	int counter;	
	for ( counter = 0; counter < 5; counter++ )
		std::cout << "Looping! ";

	std::cout << "\nCounter: " << counter << "\n\n";

	return 0;
}
