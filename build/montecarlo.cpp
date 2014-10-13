#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

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
	


	/*--------------------------------------------------------------------
	 * Particle Coordinates
	 *------------------------------------------------------------------*/
	int *parts = new int[ numOfParticles * dimOfSystem ];
	
	// assign and print initial coordinates to a *.txt file
	ofstream file;
	file.open( "initialCoords.txt" );
	file << "Initial coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numOfParticles; i++ ) {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			file << (parts[i*dimOfSystem + j] = rand() % 101 - 50) << "\t";
		}
		file << endl;
	}
	file.close();

		
	/*--------------------------------------------------------------------
	 * Calculate relative distances 
	 *------------------------------------------------------------------*/
	
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
