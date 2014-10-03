# include <iostream>

using namespace std;

int main()
{
	int counter;

	cout << "I'm rather unfriendly... How many greetings?" << endl;
	cin >> counter;

	while ( counter > 0 ) {
		cout << "Hello!\n";
		counter--;
	}
	cout << "Counter: " << counter << endl << endl;

	cout << "I'm rather friendly... How many greetings?" << endl;
	cin >> counter;

	do {
		cout << "Hello!\n";
		counter--;
	} while ( counter > 0 );

  cout << "Counter: " << counter << endl << endl;


	return 0;
}
