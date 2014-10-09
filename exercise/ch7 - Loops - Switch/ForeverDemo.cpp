# include <iostream>

# define EVER ;;

int main()
{
	char stop;
	for ( EVER ) {
		std::cout << "Type in 'q' to quit.\n";
		std::cin >> stop;
		if ( stop == 'q' )
			break;
	}

	std::cout << "Finally, a quit call.\n\n";

	return 0;
}
