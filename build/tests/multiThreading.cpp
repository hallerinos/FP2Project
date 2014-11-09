#include <iostream>
#include <thread>

using namespace std;

void foo() {
	printf("Do this. ");
}

void bar( ) { 
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
