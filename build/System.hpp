#include <iostream>		// std::cout, std::fixed
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>		// i/o file streams
#include <cmath>		// sqrt etc
#include <iomanip>		// std::setprecision

using namespace std;

class System {
	public:
		// Con- and Destructor
		System( int numPart, int dimSys, double tempSys, int sizeOfSys);
		~System();
		// Methods
		//int GetEnergy();
		//int McStep();
		//int MdStep();
		// Getter
		int GetCoordinate( int partNumber, int axis ) const;
		double GetDistance( int partNumOne, int partNumTwo) const;
		double GetEnergy() const;
		void MonteCarloStep( double eps );
		void PrintCoordinates( string fileName ) const;
	private:	
		int numberOfParticles, dimOfSystem, sizeOfSys;
		double tempOfSystem;
		double *coords;
};

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates
 *------------------------------------------------------------------*/
System::System( int newNumberOfParticles, int newDimOfSystem, 
		double newTempOfSystem, int newSizeOfSys) {
	tempOfSystem = newTempOfSystem;
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;
	sizeOfSys = newSizeOfSys;

	coords = new double[ numberOfParticles * dimOfSystem ];
	// cout << "These are the " << numberOfParticles 
	// << " Particles:" << endl;
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	{
			(coords)[i*dimOfSystem + j] = rand() % sizeOfSys;
			// (coords)[i*dimOfSystem + j] = i*dimOfSystem + j;
			// cout << "Particle: " << i << " Axis: " << j << ": \t" 
			// << (coords)[i*dimOfSystem + j] << "\t" << endl;
		}
	cout << endl;
}

System::~System() { 
	delete coords;
	cout << "Destructor call." << endl; 
}

int System::GetCoordinate ( int partNumber, int axis) const {
	return (coords)[partNumber*dimOfSystem + axis];
}

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates( string fileName ) const {
	ofstream file;
	file.open( "snapshots/"+fileName );
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

/*--------------------------------------------------------------------
 * Calculate minimal distances (PBC)
 *------------------------------------------------------------------*/
double System::GetDistance( int partNumOne, int partNumTwo ) const {
	double dist = 0;
	double coordOne;
	double coordTwo;
	for ( int j = 0; j < dimOfSystem; j++ ) {
		coordOne = coords[ partNumOne*dimOfSystem + j];
		coordTwo = coords[ partNumTwo*dimOfSystem + j];
		if( coordOne - coordTwo > sizeOfSys/2 ||
				coordOne - coordTwo < sizeOfSys/2  ) {
			dist += pow( coords[ partNumOne*dimOfSystem + j] -
				 coords[ partNumTwo*dimOfSystem + j], 2 );
		} else {
			dist += pow( coords[ partNumOne*dimOfSystem + j] -
				 coords[ partNumTwo*dimOfSystem + j], 2 );
		}
	}
	return sqrt( dist );
}

/*--------------------------------------------------------------------
 * Calculate total energy 
 *------------------------------------------------------------------*/
double System::GetEnergy() const {
	double ene = 0;
	double dist;
	double normalisation = 0; // = 127./16384;
	
	for ( int i = 0; i < numberOfParticles; i++ )
		for ( int j = i + 1; j < numberOfParticles; j++ ) {
			dist = System::GetDistance( i, j );
			ene += ( pow(dist, -12) - pow(dist, -6) + normalisation );
	}

	return ene;
}

/*--------------------------------------------------------------------
 * Make trial state
 *------------------------------------------------------------------*/
void System::MonteCarloStep( double eps ) {
	int choice = rand() % numberOfParticles;
	double tmp[dimOfSystem];
	double energyBefore = System::GetEnergy();
	// cout << "\rEnergy: " << energyBefore;
	double energyAfter;
	double sigma;

/*	
	cout << "Old coordinates: " << endl;
	for ( int j = 0; j < dimOfSystem; j++ ) 
		cout << coords[ choice*dimOfSystem + j ] << "\t";
	cout << endl;
*/

	for ( int j = 0; j < dimOfSystem; j++ ) {
		tmp[j] = coords[ choice*dimOfSystem + j ];
		coords[ choice*dimOfSystem + j ] += 
			eps * ( rand() % sizeOfSys - sizeOfSys/2 );
		if ( coords[ choice*dimOfSystem + j ] < 0 ) {
			coords[ choice*dimOfSystem + j ] += sizeOfSys;
		} else if ( coords[ choice*dimOfSystem + j ] > sizeOfSys ) {
			coords[ choice*dimOfSystem + j ] -= sizeOfSys;
		}
	}
	energyAfter = System::GetEnergy();
	if ( energyBefore > energyAfter && 
			(sigma = (float)( rand() % 1000 ) / 1000.) 
			< exp(- 1./tempOfSystem * (energyBefore - energyAfter )) ) {
	} else {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			coords[ choice*dimOfSystem + j ] = tmp[j];
		};
	}
	
/*
	cout << "New coordinates: " << endl;
	for ( int j = 0; j < dimOfSystem; j++ ) 
		cout << coords[ choice*dimOfSystem + j ] << "\t";
	cout << endl;
*/
}
