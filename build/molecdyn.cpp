#include <iostream>

#include <sstream>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>

#include "System.hpp"

using namespace std;
void readFromFile();

int numOfParticles = 2, dimOfSystem = 3, sizeOfSys = 13;
double tempOfSystem = 0.1;
float particleMass = 0.1;

int main()
{
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);

	System MD( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys, particleMass );
	
	for (int i = 0; i < 50; i++){
	MD.VeloVerletStepMD( 0.0005 );
	}


	gettimeofday(&end, NULL);
	cout << "Time needed to do this shid: " 
		<< ( (end.tv_sec  - start.tv_sec )*1000000 + 
				  end.tv_usec - start.tv_usec ) / 1000000. << endl;

	cout << "Now for an fstream" << endl;
	ofstream stuff;
	stuff.open ( "yomamma.txt" );
	stuff << "Yo Mamma is so fat, daaaaaamn!" << endl;
	stuff.close();

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
