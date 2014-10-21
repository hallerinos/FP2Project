#include <iostream>

#include <sstream>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#include "MDSystem.hpp"

using namespace std;
void readFromFile();

int numOfParticles = 250, dimOfSystem = 3, sizeOfSys = 8;
double tempOfSystem = 2;
float particleMass = 1;

int main()
{
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 
	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);

	System MD( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys, particleMass );
	double eKin = MD.GetKinEnergy();
	double ePot = MD.GetEnergy();

	cout << "Kinetic Energy: " << eKin << endl;
	cout << "Total Energy: " << eKin + ePot << endl;	
	cout << "System Energy: " << ePot << endl;
	cout << "Temperature: " << MD.GetTemperature() << endl;

	ofstream file;
	file.open( "Snapshots.dat" );
	//Thermostat on
	bool thermos = 1;

	for ( int j = 0; j < 3000; j++){
	file << "Snapshot_" << j << "------------------------------------" 
		<< endl << endl;
	file << "Potential_Energy: " << eKin << endl;
	file << "Temperature: " << eKin * 2 / (numOfParticles * dimOfSystem)	<< endl;
	file << "Total_Energy: " << eKin + ePot << endl;
	file << "Coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numOfParticles; i++ ) {
		for ( int k = 0; k < dimOfSystem; k++ ) {
			file << MD.GetCoordinate(i,k) << "\t";
		}
		file << endl;
	}
	file << endl;
	for ( int i = 0; i < 20; i++) 
		MD.VeloVerletStepMD( 0.001, thermos, 2.0, 10 );
	//if ( j < 1200 )	MD.AdjustVelos();
	
	//Thermostat off after ... Snapshots
	if ( j == 1200 ) thermos = 0;

	eKin = MD.GetKinEnergy();
	ePot = MD.GetEnergy();

	/*stringstream ss;
	ss << j;   // To Print in seperate Files
	string s = "Snapshot" + ss.str() + ".txt";
	MD.PrintCoordinates( s );*/

	cout << "\r" << j << " of 3000 Pictures taken";
	}
	file.close();
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

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates( string fileName ) const {
	ofstream file;
	file.open( (string("snapshots/")+fileName).c_str() );
	file << "Potential_Energy: " << GetEnergy() << endl;
	file << "Kinetic_Energy: " << GetKinEnergy() << endl;
	file << "Total_Energy: " << GetKinEnergy() + GetEnergy() << endl;
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
