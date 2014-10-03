# include <iostream>

using namespace std;

void ex1();
void ex2();
void ex3();
void ex4();

int main()
{
	cout << "Exercise 1:\n-----------\n";
	ex1();

	cout << "\n\n\nExercise 2:\n-----------\n";
	ex2();
	
	cout << "\n\n\nExercise 3:\n-----------\n";
	ex3();
	
	cout << "\n\n\nExercise 4:\n-----------\n";
	ex4();
	
	return 0;
}

void ex1() {
	int sizeOne = 10;
	int sizeTwo = 10;
	for ( int i=0; i < sizeOne; i++ ) {
		for ( int j=0; j < sizeTwo; j++ )
			cout << "0 ";
		cout << endl;
	}
}

void ex2() {
	for ( int i=100; i < 202; i += 2 )
		cout << i << "\t";
	cout << endl;
}

void ex3() {
	int i = 98;
	while ( (i+=2) < 202 )
		cout << i << "\t";
	cout << endl;
}

void ex4() {
	int i = 98;
	do {
		cout << ( i+=2 ) << "\t";
	} while ( i < 200 );
	cout << endl;
}
