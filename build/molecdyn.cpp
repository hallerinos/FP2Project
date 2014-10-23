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

int numOfParticles, dimOfSystem;
int numberOfSnaps, stepsBetwSnaps, stepsThermos, thermCoupling;
double tempOfSystem, tempOfThermos, rho, sizeOfSys, stepSize;
float particleMass = 1;

int main()
{
	readFromFile();

	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 
	

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);


	System MD( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys, particleMass );
	double eKin = MD.GetKinEnergy();
	double ePot = MD.GetEnergy();
	double meanTemp = 0, meanPot = 0;

	// Output of System Parameters and initial Energies.
	cout << "System initialized with following parameters: " << endl << endl;
	cout << "Number of Particles: " << numOfParticles << "\t Density: " << rho;
	cout << endl << "Boxlength: " << sizeOfSys << "\t Dimension: " 
		<< dimOfSystem << endl;
	cout << "Initial T: " << tempOfSystem << "\t Thermostat T: " 
		<< tempOfThermos << endl;
 	cout << "Thermostat is turned on for " << stepsThermos << " Snapshots. " 
	 	<<	"The Couplingfrequency is " << thermCoupling << "." << endl;
 	cout << "Taking " << numberOfSnaps << " Snapshots with " << stepsBetwSnaps 
		<< " MDSteps of Size " << stepSize << " in between ..." << endl << endl;

	cout << "Initial Values: " << endl;
	cout << "Kinetic Energy: " << eKin << endl;
	cout << "Total Energy: " << eKin + ePot << endl;	
	cout << "System Energy: " << ePot << endl;
	cout << "Temperature: " << MD.GetTemperature() << endl << endl;

	//open File for Snapshots
	ofstream file;
	string fileName = "Snapshots.dat";
	file.open( fileName.c_str() );

	//Thermostat on
	bool thermos = 1;

	for ( int j = 0; j < numberOfSnaps; j++){

		//take Snapshot
		MD.PrintCoordinates2( fileName , eKin, ePot, j+1 );

		for ( int i = 0; i < stepsBetwSnaps; i++) 
			MD.VeloVerletStepMD( stepSize, thermos, tempOfThermos, thermCoupling );
		//if ( j < 1200 )	MD.AdjustVelos();
	
		//Thermostat off after ... Snapshots
		if ( j == stepsThermos ) {
			thermos = 0;
			meanTemp = 0;
			meanPot = 0;
		}

		eKin = MD.GetKinEnergy();
		ePot = MD.GetEnergy();

		meanTemp += eKin;
		meanPot += ePot;

		//cout << "\r" << j+1 << " of " << numberOfSnaps << " Pictures taken";
		cout << "\r" << (int) ((double) (j + 1) / numberOfSnaps * 100) << "% done ...";
	}
	file.close();

	//Calculating Mean Values
	meanTemp = meanTemp * 2 / (numberOfSnaps - stepsThermos) 
		/ (numOfParticles * dimOfSystem);
	meanPot = meanPot / (numberOfSnaps - stepsThermos);

	cout << endl << endl << "Mean Values after Thermostat turned off: " << endl;
	cout << "Temperature: " << meanTemp << "\tPotential Energy: " << meanPot 
		<< endl << endl;
	
	gettimeofday(&end, NULL);
	cout << "Time needed to do this: " 
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
		getline (inputFile, line);
		getline (inputFile, line);
		( numOfParticles = atoi ( line.c_str() ) );
	
		getline (inputFile, line);
		getline (inputFile, line);
		( dimOfSystem = atoi ( line.c_str() ) );
	
		getline (inputFile, line);
		getline (inputFile, line);
		( rho = atof ( line.c_str() ) );
	
		getline (inputFile, line);
		getline (inputFile, line);
		( tempOfSystem = atof ( line.c_str() ) );

		getline (inputFile, line);
		getline (inputFile, line);
		( tempOfThermos = atof ( line.c_str() ) );
	
		getline (inputFile, line);
		getline (inputFile, line);
		( numberOfSnaps = atoi ( line.c_str() ) );

		getline (inputFile, line);
		getline (inputFile, line);
		( stepsBetwSnaps = atoi ( line.c_str() ) );

		getline (inputFile, line);
		getline (inputFile, line);
		( stepSize = atof ( line.c_str() ) );
		
		getline (inputFile, line);
		getline (inputFile, line);
		( stepsThermos = atoi ( line.c_str() ) );

		getline (inputFile, line);
		getline (inputFile, line);
		( thermCoupling = atof ( line.c_str() ) );
		
		sizeOfSys = pow ( (double) numOfParticles / rho , 1.0 / dimOfSystem );
	}
}

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates2( string fileName, double eKin, double ePot, int shotNumber ) const {
	ofstream file;
	file.open( fileName.c_str(), ios::app );
	file << "Snapshot_" << shotNumber << "------------------------------------" 			<< endl << endl;
	file << "Potential_Energy: " << ePot << endl;
	file << "Temperature: " << eKin * 2 / (numOfParticles * dimOfSystem)	
		 	 << endl;
	file << "Total_Energy: " << eKin + ePot << endl;
	file << "Coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numOfParticles; i++ ) {
		for ( int k = 0; k < dimOfSystem; k++ ) {
			file << setprecision(5) << coords[i*dimOfSystem + k] << "\t";
		}
		file << endl;
	}
	file << endl;
}
