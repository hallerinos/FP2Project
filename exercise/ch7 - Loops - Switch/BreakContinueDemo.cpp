# include <iostream>
using namespace std;

int main()
{
	unsigned short small;
	unsigned long large;
	unsigned long skip;
	unsigned long target;
	const unsigned short MAXSMALL = 65535;

	cout << "Enter a small number: ";
	cin >> small;

	cout << "Enter a large number: ";
	cin >> large;

	cout << "Enter a skip number: ";
	cin >> skip;

	cout << "Enter a target number: ";
	cin >> target;

	cout << "\n";

	while( small < large && small < MAXSMALL ) {
		small++;

		if ( small % skip == 0 ) {
			cout << "Skipping on " << small << endl;
			continue;
		}
		
		if ( large == target ) {
			cout << "\nTarget reached";
			break;
		}

		large -= 2;
	}

	cout << "\nSmall: " << small << "\nLarge: " << large
		<< endl << endl;
	
	return 0;
}
