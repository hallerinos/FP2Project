# include <iostream>

using namespace std;

int main()
{

	int counter = 0;

doNothing:
	if ( counter == 0 ) // do nothing
		;
	else 	// signal backjump
		cout << "Why the fuck can this thing jump back?!" << endl;

doSomething:
	counter++;
	cout << "Counter: " << counter << endl;
	if ( counter < 5 )
		goto doSomething;
	if ( counter == 5 )
		goto doNothing;

	cout << "Complete. Counter: " << counter << endl << endl;

	return 0;
}
