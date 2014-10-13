#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "System.hpp"

using namespace std;
void readFromFile();

int numOfParticles = 2, dimOfSystem = 3, tempOfSystem = 1, sizeOfSys = 50;

int main()
{
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);

	System MC( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys);

	MC.PrintCoordinates( "InitialCoordinates.txt" );
	
/*
	cout << "Get absolute distance of Particle: " << endl;
	for ( int i = 0; i < numOfParticles; i++)
		for ( int j = i+1; j < numOfParticles; j++ )
			cout << "# " << i  << ", " << j 
				<< ":\t"<< MC.GetDistance(i, j) << endl;
*/

	cout << "System energy: " << endl;
	cout << MC.GetEnergy() << endl;

	double MC_STEPS = 100000.;
	for ( int i = 0; i < MC_STEPS; i++)	
		MC.MonteCarloStep( 0.1 );

	cout << endl << "System energy: " << endl;
	cout << setprecision(15) << MC.GetEnergy() << endl;
	
	MC.PrintCoordinates( "FinalCoordinates.txt" );

/*
	cout << "Get absolute distance of Particle: " << endl;
	for ( int i = 0; i < numOfParticles; i++)
		for ( int j = i+1; j < numOfParticles; j++ )
			cout << "# " << i  << ", " << j 
				<< ":\t"<< MC.GetDistance(i, j) << endl;
*/

	gettimeofday(&end, NULL);
	cout << "Time needed to create System: " 
		<< ( (end.tv_sec  - start.tv_sec )*1000000 + 
				  end.tv_usec - start.tv_usec ) / 1000000. << endl;


	return 0;
}

/*--------------------------------------------------------------------
 * Read system settings from input file
 *------------------------------------------------------------------*/	
void readFromFile() {
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
}
