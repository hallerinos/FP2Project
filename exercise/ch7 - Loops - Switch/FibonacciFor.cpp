# include <iostream>

using namespace std;

long int fibForQueue( int stop );

int main()
{
	int stop;
	cout << "Which Fibonacci do you want?\nstop: ";
	cin >> stop;
	long int fibSearched = 1;

	fibSearched = fibForQueue( stop );
	cout << "The " << stop << "'th Fibonacci is " << fibSearched << endl;
	
	long int largestFibInLong;
	while ( ( fibSearched) > 0 ) {
		largestFibInLong = fibSearched;
		fibSearched = fibForQueue( ++stop );
	}

	cout << "The last Fibonacci number that fits in a long is " << endl 
		<< "Number: " << stop-1 << " Value: "<< largestFibInLong << "\n\n";
	return 0;
}

long int fibForQueue( int stop ) {
	
	long int fibNull = 0;
	long int fibOne = 1;
	long int fibPlusOne;
	
	if ( stop < 2 ) {
		return ( stop == 0 ) ? fibNull : fibOne;
	}

	for ( stop-- ; stop; stop-- ) {
		fibPlusOne = fibNull + fibOne;
		fibNull = fibOne;
		fibOne = fibPlusOne;
	}

	return fibPlusOne;
}
