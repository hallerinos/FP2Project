# include <iostream>

using namespace std;

long fibNum( int );
double totalSteps = 0;

int main()
{
	int n;
	cout << "Give the n'th concrete Fibonacci number: ";
	cin >> n;
	long fibNumberSearched = fibNum( n );
	cout << "The " << n << "'th Fibonacci number is: " << fibNumberSearched
		<< endl;
	cout << "Total steps: " << totalSteps << endl << endl;
	return 0;
}

long fibNum( int n )
{
	cout << "\r" << totalSteps++;
	if ( n < 3 ) {
		return 1;
	} else {
		return fibNum( n-1 ) + fibNum( n-2 );
	}
}
