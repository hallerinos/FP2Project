# include <iostream>

int main()
{
	using namespace std;

	int firstNum, secondNum;
	cout << "Enter two numbers.\n First: ";
	cin >> firstNum;
	cout << "Second: ";
	cin >> secondNum;
	cout << endl << endl;

	if ( firstNum >= secondNum ) {
		if ( ( firstNum % secondNum ) == 0) {
			if ( firstNum == secondNum )
				cout << "They are equal.";
			else
				cout << "They are evenly diversible.";
		}
		else
			cout << "They are not evenly diversible.";
	}
	else
		cout << "The second Number is larger.";

	return 0;
}
