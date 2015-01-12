#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstdio>

#include "MCSystem.hpp"

using namespace std;

void readFromFile();
void writeConditionsToFile(float rho, float ratio);
void do_it();

int numOfParticles, dimOfSystem;
double sizeOfSys;
long MC_STEPS, MAX_STEPS;
double tempOfSystem;
double eps;
double chemPot;
string choice;

int main()
{
	readFromFile();
	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);

	cout << "Number of Particles: " << numOfParticles;
	cout << "\tSize of system: " << (double)sizeOfSys;
	cout << "\nTemperature: " << tempOfSystem;
	cout << "\t\tParticle density: " << 
		(double)numOfParticles/(2*sizeOfSys*sizeOfSys*sizeOfSys) << endl;
	cout << "Number of MC steps: " << MC_STEPS;
	cout << "\tEpsilon: " << eps << endl;
	cout << "Chemical Potential: " << chemPot << endl;
	// initialise random seed	
	srand( time(NULL) );		// different seeds
	// srand( 0 );						// same seed 
	
	System MC( numOfParticles, dimOfSystem, tempOfSystem, sizeOfSys, chemPot );
	cout << "\nInitial energy: " 
		<< setprecision(6) << MC.GetEnergy() << endl;
	for( long i=0; i<MC_STEPS; i++)
		MC.MonteCarloStep2();
	for( long i=0; i<MC_STEPS; i++) {
		for ( int j=0; j<100; j++ ) {
			MC.MonteCarloStep2();
	}
	cout << setprecision(3) << MC.GetEnergy() << "\t" << MC.GetNumberOfParts() << endl; 
	}
	MC.PrintCoordinates("T_" + to_string(tempOfSystem) + "rho_"+ 
			to_string(
			 (double)numOfParticles/(2*sizeOfSys*sizeOfSys*sizeOfSys)
			 ) + "Snapshots.txt");
	cout << INT_MAX;
	// cout << "\nFinal energy: " 
	// 	<< setprecision(6) << MC.GetEnergy() << endl;
	// cout << "Number of particles: " << MC.GetNumberOfParts() << endl;
	// cout << "Density:             " << MC.GetNumberOfParts()/(2*sizeOfSys*sizeOfSys*sizeOfSys) << endl;

	// gettimeofday(&end, NULL);
	// cout << "\n\nCalculation time: " 
	// 	<< ( (end.tv_sec  - start.tv_sec )*1000000 + 
	// 			  end.tv_usec - start.tv_usec ) / 1000000. << endl;


	return 0;
}
/*
void do_it() {

	long steps = 0;
	float optRatio = 0.60;
	float accRatio;
	cout << "First, find a good step size... " 
		<< "Optimum ratio: " << optRatio << endl;
	// do {
	// 	System testSys(numOfParticles,dimOfSystem,tempOfSystem,sizeOfSys);
	// 	while ( steps < 332000 )	{
	// 		testSys.MonteCarloStep( eps );
	// 		steps++;
	// 	}
	// 	accRatio = (double)testSys.GetAcceptedSteps()/steps;
	// 	steps = 0;
	// 	if ( accRatio < optRatio ) {
	// 		cout << "Bad Ratio. Give a smaller initial MC step size!";
	// 		break;
	// 	}
	// 	if ( accRatio-optRatio<0.015 ) {
	// 		cout << "Ratio OK: " << accRatio << ", start equilibration...";
	// 		break;
	// 	}
	// 	cout << "Acceptance Ratio bad... " 
	// 		<< "Ratio: " << accRatio << " new MC step size: " << eps << endl;
	// 	eps += 0.0002;
	// } while ( eps > 0 && eps < 0.5 );

	steps = 0;
	while ( steps < MC_STEPS )	{
		for ( int i = 0; i < numOfParticles; i++ ) {
			MC.MonteCarloStep2();
		}
		accRatio = (double)100*MC.GetAcceptedSteps()/numOfParticles;
		printf("\rProgress: %.2f \%%",(double)(100*steps++ +1)/MC_STEPS);
		printf("\r\t\t\tAcceptance Ratio: %.2f \%%",accRatio);
	}
	cout << "\nDone. Final energy:";
	cout << setprecision(10) << MC.GetEnergy();
	cout << "\nAcceptance ratio: " 
		<< accRatio << endl << endl;
	
	steps = 0;	
	double* energies = new double[MAX_STEPS];
	cout << "Measuring... " << MAX_STEPS <<
			" additional MC steps. Snapshots are saved: " << choice << endl;
	if ( choice == "No" )
		while ( steps < MAX_STEPS )	{
			for ( int i=0; i < 50*numOfParticles; i++ )
				MC.MonteCarloStep( eps );
			energies[steps] = MC.GetEnergy();
			printf("\rProgress: %.2f \%%",(double)(100*steps++ +1)/MAX_STEPS);
	} else if ( choice == "Yes" ) 
	  while ( steps < MAX_STEPS )	{
			for ( int i=0; i < 50*numOfParticles; i++ )
	  		MC.MonteCarloStep( eps );
			MC.PrintCoordinates("T_" + to_string(tempOfSystem) + "rho_"+ 
					to_string(
					 (double)numOfParticles/(2*sizeOfSys*sizeOfSys*sizeOfSys)
					 ) + "Snapshots.txt");
	  	energies[steps] = MC.GetEnergy();
			printf("\rProgress: %.2f \%%",(double)(100*steps++ +1)/MAX_STEPS);
	}
	
	stringstream eneSs;
	ofstream file;
	file.open(
			"plots/T_" + to_string(tempOfSystem) + "rho_"+to_string((double)numOfParticles/(2*sizeOfSys*sizeOfSys*sizeOfSys))+"EnergySeries.txt");
	for ( int i=0; i < MAX_STEPS; i++ ) 
			eneSs  << setprecision(10) << energies[i] << endl;
	file << eneSs.str();
	file.close();
	cout << "\nProgramm finished." << endl;
}
*/
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

		getline( inputFile, line );
		getline( inputFile, line );
		( chemPot = atof(line.c_str()) );

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
			file << setprecision(8) << coords[i*dimOfSystem + j] << "\t";
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
void writeConditionsToFile(float rho, float ratio) {
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
	iniConditions << "Acceptance Ratio:\t" << endl;
	iniConditions << ratio << endl;
	ofstream file;
	file.open( "plots/"+to_string(rho)+"SystemSpecs.txt" );
	file << iniConditions.str();
	file.close();
	cout << " Done." << endl;
}
