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

void readFromFile();
void writeConditionsToFile();

int numOfParticles, dimOfSystem;
double sizeOfSys;
long MC_STEPS, MAX_STEPS;
double tempOfSystem;
double eps;
string choice;

int main()
{
	readFromFile();

	cout << "Number of Particles: " << numOfParticles;
	cout << "\tSize of system: " << (double)sizeOfSys;
	cout << "\t\tTemperature: " << tempOfSystem;
	cout << "\nParticle density: " << 
		(double)numOfParticles/(sizeOfSys*sizeOfSys*sizeOfSys) << endl;
	cout << "Number of MC steps: " << MC_STEPS;
	cout << "\tEpsilon: " << eps;
	
	// writeConditionsToFile();
	
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 


	System MC( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys );
	
	cout << "\n\nInitial energy: " << setprecision(5) << MC.GetEnergy();

	long steps = 0;
	
	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	while ( steps < MC_STEPS )	{
		MC.MonteCarloStep( eps );
		// cout << "\r" << ((double)steps++/MC_STEPS*100);
		steps++;
	}

	cout << "\t\tFinal energy:";
	cout << setprecision(5) << MC.GetEnergy() << endl << endl;

	steps = 0;	
	double* energies = new double[MAX_STEPS];
	cout << "For energy average, calculate " << MAX_STEPS <<
			" additional MC. Save snapshots: " << choice;
	cout << "\nProgress:\n";
	if ( choice == "No" )
		while ( steps < MAX_STEPS )	{
			MC.MonteCarloStep( eps );
			energies[steps] = MC.GetEnergy();
			cout << "\r" << setprecision(4) 
				<< (double)(steps++ + 1)/MAX_STEPS*100;	
	} else if ( choice == "Yes" ) 
	  while ( steps < MAX_STEPS )	{
			//for ( int i=0; i < numOfParticles; i++ )
	  		MC.MonteCarloStep( eps );
	  	energies[steps] = MC.GetEnergy();
	  	MC.PrintCoordinates( to_string(eps) +"Snapshots.txt" );
	  	cout << "\r" << setprecision(4) 
	  		<< (double)(steps++ + 1)/MAX_STEPS*100;	
	}
	
	stringstream eneSs;
	ofstream file;
	file.open((string("plots/")+to_string(eps)+"EnergySeries.txt").c_str());
	for ( int i=0; i < MAX_STEPS; i++ ) 
		for ( int j=0; j<250; j++ )
			eneSs  << setprecision(6) << energies[i] << endl;
	file << eneSs.str();
	file.close();

	gettimeofday(&end, NULL);
	cout << "\n\nCalculation time: " 
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
	if ( inputFile.is_open() ) {
		getline( inputFile, line );
		getline( inputFile, line );
		( numOfParticles = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( dimOfSystem = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( sizeOfSys = atof( line.c_str() ) );

		getline( inputFile, line );
		getline( inputFile, line );
		( tempOfSystem = atof( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( MC_STEPS = atol( line.c_str() ) );

		getline( inputFile, line );
		getline( inputFile, line );
		( MAX_STEPS = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( eps = atof( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( choice = line.c_str() );

		inputFile.close();
	}
}

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates( string fileName ) const {
	ofstream file;
	file.open( (string("plots/")+fileName).c_str(), ios::app );
	// file << "Number_of_particles: " << numOfParticles << endl;
	// file << "Size_of_system: " << sizeOfSys << endl;
	// file << "Potential_Energy: " << GetEnergy() << endl;
	// file << "X\t\tY\t\tZ" << endl;
	for ( int i = 0; i < numberOfParticles; i++ ) {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			file << setprecision(4) << coords[i*dimOfSystem + j] << "\t";
		}
		file << endl;
	}
	// file << endl;
	// file << endl;
	file.close();
}

/*--------------------------------------------------------------------
 * Write initial settings to a file...
 *------------------------------------------------------------------*/
void writeConditionsToFile() {
	cout << "Writing Conditions...";
	stringstream iniConditions;
	iniConditions << "Number_of_particles:\t" << endl;
	iniConditions << numOfParticles << endl;
	iniConditions << "Dimension:\t" << endl;
	iniConditions << dimOfSystem << endl;
	iniConditions << "Size:\t" << endl;
	iniConditions << sizeOfSys << endl;
	iniConditions << "Temperature:\t" << endl;
	iniConditions << tempOfSystem << endl;
	ofstream file;
	file.open( "plots/"+to_string(eps)+"SystemSpecs.txt" );
	file << iniConditions.str();
	file.close();
	cout << " Done." << endl;
}
