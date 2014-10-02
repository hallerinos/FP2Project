# include <iostream>

int main()
{
	int counter = 0;
	while ( 1 ) {
		counter++;
		if ( counter > 100 ) 
			break;
	}
	std::cout << "Counter: " << counter << "\n\n";

	return 0;
}
