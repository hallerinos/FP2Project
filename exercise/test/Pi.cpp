# include <iostream>
# include <stdlib.h> 
# include <time.h>
# include <tgmath.h>

# define EVER ;;
using namespace std;

int main() 
{
	// initialise rand. seed
	srand( time(NULL) );
	
	double pi = 0;
	unsigned long rNumx;
	unsigned long rNumy;
	unsigned long cHit = 0;
	unsigned long cAll = 0;
	for ( ;cAll < 1000000000; cAll++ ) {
		rNumx = rand() % 10000;
		rNumy = rand() % 10000;
		if ( (sqrt(rNumx*rNumx + rNumy*rNumy)/10000) < 1 ) {
			cHit++;
		};
		pi = ((double)cHit) / cAll * 4;
	}

		cout << "\r Total: " << cAll;
		cout << "\r \t\tHits: " << cHit;
		cout << "\r \t\t\t\tPi: " << pi;
	return 0;
}
