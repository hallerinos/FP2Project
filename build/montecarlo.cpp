#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "System.hpp"

using namespace std;


int main()
{
	// initialise random seed	
	// srand( time(NULL) );		// different seeds
	srand( 0 );								// same seed 

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	
	/*--------------------------------------------------------------------
	 * Read system settings from input file
	 *------------------------------------------------------------------*/
	int numOfParticles=0, dimOfSystem=0;
	
	ifstream inputFile("SystemSpecs.txt");
	string line;
	getline( inputFile, line ); cout << line << endl;
	getline( inputFile, line ); cout << line << endl;
	getline( inputFile, line ); cout << line << endl;
	if ( inputFile.is_open() ) {
		getline( inputFile, line ); cout << line << " ";
		getline( inputFile, line );
		cout << (numOfParticles = atoi( line.c_str() )) << endl;
		
		getline( inputFile, line ); cout << line << " "; 
		getline( inputFile, line );
		cout << ( dimOfSystem = atoi( line.c_str() ) ) << endl;
		
		inputFile.close();
	}

	System MC( numOfParticles, dimOfSystem );

	MC.PrintCoordinates();
	cout << MC.GetDistance( 1, 2);	
	
	/*--------------------------------------------------------------------
	 * Calculate energy 
	 *------------------------------------------------------------------*/
	
	/*--------------------------------------------------------------------
	 * Make trial state
	 *------------------------------------------------------------------*/
	gettimeofday(&end, NULL);
	cout << "Time needed to create System: " 
		<< ( (end.tv_sec  - start.tv_sec )*1000000 + 
				  end.tv_usec - start.tv_usec ) / 1000000. << endl;
	return 0;
}


