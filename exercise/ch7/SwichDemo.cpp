# include <iostream>

using namespace std;

int main()
{
	unsigned short int number;

	cout << "Enter a number between 1 and 5: ";
	cin >> number;

	switch( number ) {
		case 0: 
			cout << "Too small, sorry!";
			break;
		case 5:
			cout << "Good job!" << endl;
			break;
		case 4:
			cout << "Nice Pick!" << endl;
			break;
		case 3:
			cout << "You like the median, eh?" << endl;
		case 2:
			cout << "Masterful!" << endl;
		case 1:
			cout << "Incredible!" << endl;
			break;
		default:
			cout << "Too Large!" << endl;
			break;
	}
	cout << endl << endl;

	return 0;
}
