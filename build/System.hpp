#include <iostream>		// std::cout, std::fixed
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>		// i/o file streams
#include <cmath>		// sqrt etc
#include <iomanip>		// std::setprecision
#include <climits>
#include <string>

using namespace std;

class System {
	public:
		// MC Constructor
		System( int numPart, int dimSys, double tempSys, int sizeOfSys
			 	);
		// MD Constructor 
		System( int numPart, int dimSys, double tempSys, int sizeOfSys, float particleMass );
		// Destructor
		~System();
		// Getter
		double GetCoordinate( int partNumber, int axis ) const;
		double GetDistance( int partNumOne, int partNumTwo) const;
		double GetEnergy() const;
		double GetKinEnergy() const;
		// Print and Step Methods
		void MonteCarloStep( double eps );
		void VeloVerletStepMD( double dT );
		void AdjustVelos();
		void PrintCoordinates( string fileName ) const;
		//Member Variables
	private:	
		int numberOfParticles, dimOfSystem, sizeOfSys;
		double MIN_CUTOFF, MAX_CUTOFF; 	// Cutoff Distances for Interaction
		double tempOfSystem;
		double *coords, *velos, *forces, *forces2;
		float mass;
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
	MIN_CUTOFF = pow( 10, -6 );
	MAX_CUTOFF = sizeOfSys;
	forces = 0;
	forces2 = 0;
	velos = 0;
	coords = new double[ numberOfParticles * dimOfSystem ];

	//Initialization of the particle locations
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	
			(coords)[i*dimOfSystem + j] = (float)rand() / INT_MAX * sizeOfSys;
	}

System::~System() { 
	delete coords;
	delete velos;
	delete forces;
	delete forces2;
	cout << "Destructor call." << endl; 
}

double System::GetCoordinate ( int partNumber, int axis) const {
	return (coords)[partNumber*dimOfSystem + axis];
}

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates, velocities,
 * calculates initial Forces and takes a Mass.
 *------------------------------------------------------------------*/

System::System( int newNumberOfParticles, int newDimOfSystem, 
		double newTempOfSystem, int newSizeOfSys, float newMass) {

	tempOfSystem = newTempOfSystem;
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;
	sizeOfSys = newSizeOfSys;
	mass = newMass;
	MIN_CUTOFF = pow( 10, -12 );
	MAX_CUTOFF = sizeOfSys/2;
	forces2 = new double[ numberOfParticles * dimOfSystem ];
	forces = new double[ numberOfParticles * dimOfSystem ];
	velos = new double[ numberOfParticles * dimOfSystem ];
	coords = new double[ numberOfParticles * dimOfSystem ];

	// Initialization of particle locations
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )
			(coords)[i*dimOfSystem + j] = (float) rand() / INT_MAX * sizeOfSys ;

	//Initalization of Velocities
	double vmax =  sqrt(dimOfSystem * tempOfSystem / mass) ; // k_B=1
	double vnew = 0;
	double random = 0;
	double c1 = sqrt(mass/(2*3.1416*tempOfSystem));
	double c2 = mass / (2 * tempOfSystem);
	for ( int i = 0; i < numberOfParticles; i+=2 )
		for ( int j = 0; j < dimOfSystem; j++ ) {
			//Generate random Velocity and Random Number [0,1]
			vnew = (double) rand() / INT_MAX * 3 * vmax - 1.5 * vmax;
			random = (double) rand() / INT_MAX;
			//Check Boltzmann
			if ( random < ( c1 * exp(-c2*pow(vnew,2))) )
			{
			(velos)[i*dimOfSystem + j] = (double) rand () / INT_MAX * 2 *vmax
			 	- vmax;
			(velos)[(i+1)*dimOfSystem + j] = -(velos)[i*dimOfSystem + j];
			} else j--;
		}


	// Calculation of initial Forces
	
	double rsq;
	double diffV[3];

	for ( int i = 0; i < numberOfParticles * dimOfSystem; i++ )
		forces[i]=0;

	for ( int i = 0; i < numberOfParticles; i++ ){
		for ( int j = i+1; j < numberOfParticles; j++ ){

			//Get distance vector and calculate distance-squared between
			//particles i and j
			rsq = 0;
			for ( int k = 0; k < dimOfSystem; k++ ){
				diffV[k] = coords[i*dimOfSystem + k] - coords[j*dimOfSystem + k];
				if( diffV[k] > sizeOfSys/2 ) {
					diffV[k] = diffV[k] - sizeOfSys;
				} else if ( diffV[k] < - sizeOfSys/2 ) {
					diffV[k] = diffV[k] + sizeOfSys;
				}
				rsq += pow(diffV[k],2);
			}

			//Check cutoff distance save force
			if ( rsq < MIN_CUTOFF || rsq > MAX_CUTOFF ){} else
				for ( int k = 0; k < dimOfSystem; k++ ){
					forces[i*dimOfSystem + k] += 
						24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
					forces[j*dimOfSystem + k] -=
						24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
				}
		}			
	}
	
	cout << endl;
}

/*--------------------------------------------------------------------
 * Calculate minimal distances (PBC)
 *------------------------------------------------------------------*/
double System::GetDistance( int partNumOne, int partNumTwo ) const {
	double dist = 0;
	double coordDiff = 0;
	for ( int j = 0; j < dimOfSystem; j++ ) {
		coordDiff = coords[ partNumTwo*dimOfSystem + j] 
			- coords[ partNumOne*dimOfSystem + j];

		if( coordDiff > sizeOfSys/2 ) {
			dist += pow( coordDiff - sizeOfSys, 2 );
		} else if ( coordDiff < - sizeOfSys/2 ) {
			dist += pow( coordDiff + sizeOfSys, 2 );
		} else dist += pow( coordDiff, 2 );
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
			( dist < MIN_CUTOFF || dist > MAX_CUTOFF ) ? ene += 0 :
				( ene += 4 * ( pow(dist, -12) - pow(dist, -6) + normalisation ) );
	}

	return ene;
}

