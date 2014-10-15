#include <iostream>		// std::cout, std::fixed
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>		// i/o file streams
#include <cmath>		// sqrt etc
#include <iomanip>		// std::setprecision
#include <climits>

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
		void MonteCarloStep( double eps );
		void VeloVerletStepMD( double dT );
		void PrintCoordinates( string fileName ) const;
	private:	
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
	
	forces = 0;
	forces2 = 0;
	velos = 0;
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
	delete velos;
	delete forces;
	delete forces2;
	cout << "Destructor call." << endl; 
}

int System::GetCoordinate ( int partNumber, int axis) const {
	return (coords)[partNumber*dimOfSystem + axis];
}

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates and velocities.
 * Takes Mass.
 *------------------------------------------------------------------*/

System::System( int newNumberOfParticles, int newDimOfSystem, 
		double newTempOfSystem, int newSizeOfSys, float newMass) {
	tempOfSystem = newTempOfSystem;
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;
	sizeOfSys = newSizeOfSys;
	mass = newMass;

	forces2 = new double[ numberOfParticles * dimOfSystem ];
	forces = new double[ numberOfParticles * dimOfSystem ];
	velos = new double[ numberOfParticles * dimOfSystem ];
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
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------
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

/*------------------------------------------------------------------
 * Molecular Dynamic Step ( Velocity Verlet )
 * ---------------------------------------------------------------*/

void System::VeloVerletStepMD ( double dT ) {

	//Calculate new Coordinates
	
	for (int i = 0; i < dimOfSystem*numberOfParticles; i++){
		coords[i] = coords[i] + velos[i] * dT + forces[i]*pow(dT,2)/(2*mass);
		if ( coords[i] > sizeOfSys ) {
			coords[i] -= sizeOfSys;
		} else if (coords[i] < 0) {
			coords[i] += sizeOfSys;
		}
	}

	//Calculate new Forces
	
	double rsq;
	double diffV[3];

	for ( int i = 0; i < numberOfParticles * dimOfSystem; i++ )
		forces2[i]=0;

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

			for ( int k = 0; k < dimOfSystem; k++ ){
				forces2[i*dimOfSystem + k] += 
					24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
				forces2[j*dimOfSystem + k] -=
					24 * diffV[k] * ( 2/pow(rsq,7) - 1/pow(rsq,4) );
			}
		}			
	}

	//Calculate new Velocities
	
	for (int i = 0; i < dimOfSystem * numberOfParticles; i++){
		velos[i] = velos[i] + (forces[i] + forces2[i])*dT/(2*mass);
	}

	//overWrite old Forces
	
	for (int i = 0; i < dimOfSystem * numberOfParticles; i++){
		forces[i] = forces2[i];
	}

	/*cout << "New Coordinate 1: " << coords[0] << "\t" << coords[1] << "\t"
		<< coords[2] << endl;
	cout << "New Coordinate 2: " << coords[3] << "\t" << coords[2] << "\t"
		<< coords[3] << endl;*/
	cout << "Distance between 1 and 2: " << GetDistance(0,1) << endl;
}
