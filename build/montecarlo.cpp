#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "MCSystem.hpp"

using namespace std;
void ReadFromFile();
void WriteConditionsToFile();

int numOfParticles = 10, dimOfSystem = 3, sizeOfSys = 10;
double tempOfSystem = 1e-5;
float particleMass = 1;

int main()
{
	void WriteConditionsToFile();
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 


	System MC( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys );
	
	cout << endl << "Energy per interaction: " << endl;
	cout << setprecision(15) << 2*MC.GetEnergy()/(numOfParticles*(numOfParticles-1)) << endl;

	double eps = 0.25;
	long steps = 1;
	
	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	while ( eps > 1e-6 )	{
		for ( int j = 0; j < numOfParticles; j++)
			eps=MC.MonteCarloStep( eps );
		// stringstream ss;
		// ss << "Snapshot";
		// ss.width(5);
		// ss << setfill('0') << steps;
		// ss << ".txt";
		// MC.PrintCoordinates( ss.str() );
		steps++;
	}

	cout << endl << "Energy per interaction: " << endl;
	cout << setprecision(15) << 2*MC.GetEnergy()/(numOfParticles*(numOfParticles-1)) << endl;
	
/*	
	cout << "Get absolute distance of Particle: " << endl;
	for ( int i = 0; i < numOfParticles; i++)
		for ( int j = i+1; j < numOfParticles; j++ )
			cout << "# " << i  << ", " << j 
				<< ":\t"<< MC.GetDistance(i, j) << endl;
*/
	gettimeofday(&end, NULL);
	cout << "Calculation time: " 
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

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates( string fileName ) const {
	ofstream file;
	file.open( (string("snapshots/")+fileName).c_str() );
	file << "Potential_Energy: " << GetEnergy() << endl;
	file << "Coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numberOfParticles; i++ ) {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			file << coords[i*dimOfSystem + j] << "\t";
		}
		file << endl;
	}
	file.close();
}

void WriteConditionsToFile() {	
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
}
