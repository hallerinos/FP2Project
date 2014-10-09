# include <iostream>

using namespace std;

# define EVER ;;

int main() {
	
	long int *pPointer;
	int i = 0;
	for ( EVER ) {
		pPointer = new long int;
		*pPointer = i++;
	}

	return 0;
}
