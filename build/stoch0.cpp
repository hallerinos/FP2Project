#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;
int wuerfelNMal( int );
int main()
{
	srand( time(NULL) );
	int count = 0;
	int MAXIMUM = 1000000;
	for ( int i = 0; i < MAXIMUM; i++ ) {
		count += wuerfelNMal(4);
	}
	cout << (double)count/MAXIMUM;

	return 0;
}
int wuerfelNMal( int n ) {
	for ( int j = 0; j < n; j++ )
		if ( (rand() % 6 + 1) > 4 )
			return 0;
	return 1;
}
