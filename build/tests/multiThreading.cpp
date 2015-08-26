#include <iostream>
#include <thread>

using namespace std;

void foo() {
	for ( int i=1 ; i < 10; i++)
		printf("Do this. ");
}

void bar( ) { 
	for ( int j=1 ; j < 10; j++)
		printf("Do that. ");
}

int main()
{
	thread first( foo );
	thread second( bar );

	first.join();
	second.join();

	cout << "Finished.";

	return 0;
}
