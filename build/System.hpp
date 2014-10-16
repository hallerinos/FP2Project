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
		// Con- and Destructor
		System( int numPart, int dimSys, double tempSys, int sizeOfSys
			 	);
		// MD Constructor 
		System( int numPart, int dimSys, double tempSys, int sizeOfSys, float particleMass );
		~System();
		// Methods
		//int GetEnergy();
		//int McStep();
		//int MdStep();
		// Getter
		int GetCoordinate( int partNumber, int axis ) const;
		double GetDistance( int partNumOne, int partNumTwo) const;
		double GetEnergy() const;
		double GetKinEnergy() const;
		void MonteCarloStep( double eps );
		void VeloVerletStepMD( double dT );
		void PrintCoordinates( string fileName ) const;
	private:	
		double MIN_CUTOFF, MAX_CUTOFF;
		int numberOfParticles, dimOfSystem, sizeOfSys;
		double tempOfSystem;
		double *coords;
		double *velos;
		double *forces;
		double *forces2;
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
	// cout << "These are the " << numberOfParticles 
	// << " Particles:" << endl;
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	{
			(coords)[i*dimOfSystem + j] = (float)rand() / INT_MAX * sizeOfSys;
			// (coords)[i*dimOfSystem + j] = i*dimOfSystem + j;
			// cout << "Particle: " << i << " Axis: " << j << ": \t" 
			// << (coords)[i*dimOfSystem + j] << "\t" << endl;
		}
	cout << endl;
}

System::~System() { 
	delete coords;
	delete velos;
	delete forces;
	delete forces2;
	cout << "Destructor call." << endl; 
}

int System::GetCoordinate ( int partNumber, int axis) const {
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
	// cout << "These are the " << numberOfParticles 
	// << " Particles:" << endl;
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	{
			(coords)[i*dimOfSystem + j] = (float) rand() / INT_MAX * sizeOfSys ;
			// (coords)[i*dimOfSystem + j] = i*dimOfSystem + j;
			// cout << "Particle: " << i << " Axis: " << j << ": \t" 
			// << (coords)[i*dimOfSystem + j] << "\t" << endl;
		}

	//Initalization of Velocities
	float vmax =  sqrt(dimOfSystem * tempOfSystem / mass) ; // k_B=1
	for ( int i = 0; i < numberOfParticles; i+=2 )
		for ( int j = 0; j < dimOfSystem; j++ ) {
			(velos)[i*dimOfSystem + j] = (float) rand () / INT_MAX * 2 *vmax
			 	- vmax;
			(velos)[(i+1)*dimOfSystem + j] = -(velos)[i*dimOfSystem + j];
		}

	/*
	double sum=0;

	for ( int i = 0; i < numberOfParticles*dimOfSystem; i++){
		sum+= velos[i];
	}
	cout << "Sum of Velocities: " << sum << endl;
	
	sum=0;

	for ( int i = 0; i < numberOfParticles*dimOfSystem; i++){
		sum+= pow(velos[i],2);
	}
	cout << "vmax: " << vmax << endl;

	cout << "E(v^2): " << sum / numberOfParticles << endl;*/



	// Calculation of initial Forces
	
double rsq;
double diffV[3];

for ( int i = 0; i < numberOfParticles * dimOfSystem; i++ )
	forces[i]=0;

for ( int i = 0; i < numberOfParticles; i++ ){
	for ( int j = i+1; j < numberOfParticles; j++ ){
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

		if ( rsq < MIN_CUTOFF || rsq > MAX_CUTOFF ){} else
			for ( int k = 0; k < dimOfSystem; k++ ){
				forces[i*dimOfSystem + k] += 
					24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
				forces[j*dimOfSystem + k] -=
					24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
			}
	}			
}
	
/*	cout << "Coords 1: " << coords[0] << "\t" << coords[1] << "\t" << coords[2] << endl;
	cout << "Coords 2: " << coords[3] << "\t" << coords[4] << "\t" << coords[5] << endl;

	cout << "Forces 1: " << forces[0] << "\t" << forces[1] << "\t" 
		<< forces[2] << endl;
	cout << "Forces 2: " << forces[3] << "\t" << forces[4] << "\t" 
		<< forces[5] << endl;*/

	cout << endl;
}

/*--------------------------------------------------------------------
 * Calculate minimal distances (PBC)
 *------------------------------------------------------------------*/
double System::GetDistance( int partNumOne, int partNumTwo ) const {
	double dist = 0;
	double tmp = 0;
	double coordOne;
	double coordTwo;
	for ( int j = 0; j < dimOfSystem; j++ ) {
		coordOne = coords[ partNumOne*dimOfSystem + j];
		coordTwo = coords[ partNumTwo*dimOfSystem + j];
		tmp = coordTwo - coordOne;	
		if( tmp > sizeOfSys/2 ) {
			dist += pow( tmp - sizeOfSys, 2 );
		} else if ( tmp < - sizeOfSys/2 ) {
			dist += pow( tmp + sizeOfSys, 2 );
		} else dist += pow( tmp, 2 );
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
				( ene += ( pow(dist, -12) - pow(dist, -6) + normalisation ) );
	}

	return ene;
}

