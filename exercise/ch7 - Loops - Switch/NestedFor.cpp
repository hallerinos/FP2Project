# include <iostream>

using namespace std;

int main()
{
	int endFirst;
	int endSecond;

	cout << "Enter first break condition: ";
	cin >> endFirst;
	cout << "Enter second break condition: ";
	cin >> endSecond;
	for ( int i=0; i < endFirst; i++ )
		for ( int j=0; j < endSecond; j++ )
			cout << "i: " << i << " j: " << j << endl;

	return 0;
}
