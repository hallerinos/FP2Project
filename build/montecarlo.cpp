#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "System.hpp"

using namespace std;
void readFromFile();

int numOfParticles = 10, dimOfSystem = 3, sizeOfSys = 10;
double tempOfSystem = 10000;
float particleMass = 1;

int main()
{
	stringstream iniConditions;
	iniConditions << "Number_of_particles:\t";
	iniConditions << numOfParticles << endl;
	iniConditions << "Dimension:\t";
	iniConditions << dimOfSystem << endl;
	iniConditions << "Size:\t";
	iniConditions << sizeOfSys << endl;
	iniConditions << "Temperature:\t";
	iniConditions << tempOfSystem << endl;
	ofstream file;
	file.open( "snapshots/InitialConditions.txt" );
	file << iniConditions.str();
	file.close();
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);

	System MC( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys );
/*	
	cout << "Get absolute distance of Particle: " << endl;
	for ( int i = 0; i < numOfParticles; i++)
		for ( int j = i+1; j < numOfParticles; j++ )
			cout << "# " << i  << ", " << j 
				<< ":\t"<< MC.GetDistance(i, j) << endl;
*/
	cout << "System energy: " << endl;
	cout << MC.GetEnergy() << endl;

	int MC_STEPS = 10000;
	for ( int i = 0; i < MC_STEPS; i++)	{
		MC.MonteCarloStep( 0.1 );
		stringstream ss;
		ss << "Snapshot";
		ss.width(5);
		ss << setfill('0') << i;
		ss << ".txt";
		MC.PrintCoordinates( "snapshots/"+ss.str() );
	}

	cout << endl << "System energy: " << endl;
	cout << setprecision(15) << MC.GetEnergy() << endl;
	
/*	
	cout << "Get absolute distance of Particle: " << endl;
	for ( int i = 0; i < numOfParticles; i++)
		for ( int j = i+1; j < numOfParticles; j++ )
			cout << "# " << i  << ", " << j 
				<< ":\t"<< MC.GetDistance(i, j) << endl;
*/
	gettimeofday(&end, NULL);
	cout << "Time needed to do this shid: " 
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
