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
		System( int numPart, int dimSys, double tempSys, double sizeOfSys	);
		// MD Constructor 
		System( int numPart, int dimSys, double tempSys, double sizeOfSys, float particleMass );
		// Destructor
		~System();
		// Methods used by both Algorithms
		double 	GetCoordinate( int partNumber, int axis ) const;
		double 	GetEnergy() const;
		long	 	GetAcceptedSteps();
		void 		PrintCoordinates( string fileName ) const;
		void 		FirstHalf( double ene, double normalisation) const;
		void 		SecondHalf( double ene, double normalisation) const;
		// MC Methods
		double* makeRandomOnUnitSphere( double* vec ) const;
		double 	GetEnergyI( int ) const;
		void 		MonteCarloStep( double eps );
		double 	GetDistanceSq( int partNumOne, int partNumTwo) const;
		// MD Methods
		void 		VeloVerletStepMD( double dT, bool termostat, double tempThermos, double coupling );
		void 		AdjustVelos();
		void 		AdjustVelosDavid( double tempOfThermostat, double coupling );
		double 	GetKinEnergy() const;
		double 	GetTemperature() const;
		void 		PrintCoordinates2( string fileName, double eKin, double ePot, int ShotNumber ) const;
		//Member Variables
	private:	
		int 		numberOfParticles, dimOfSystem;
		long		acceptedSteps;
		double 	sizeOfSys;
		double 	MIN_CUTOFF, MAX_CUTOFF; 	// Cutoff Distances for Interaction
		double 	tempOfSystem;
		double 	*coords, *velos, *forces, *forces2;
		float 	mass;
};

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates
 *------------------------------------------------------------------*/
System::System( int newNumberOfParticles, int newDimOfSystem, 
		double newTempOfSystem, double newSizeOfSys) {

	tempOfSystem = newTempOfSystem;
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;
	sizeOfSys = newSizeOfSys;
	acceptedSteps = 0;
	MAX_CUTOFF = 5.039684;
	forces = 0;
	forces2 = 0;
	velos = 0;
	coords = new double[ numberOfParticles * dimOfSystem ];

	// for ( int i3 = 0; i3 < numberOfParticles; i3++ )
	// for ( int  d = 0;  d < dimOfSystem			; d++ ) 
	// for ( int i2 = 0; i2 < numberOfParticles; i2++ )
	// for ( int i1 = 0; i1 < numberOfParticles; i1++ )
	//  {	
	// 	coords[(i1 + numberOfParticles*(i2 + numberOfParticles*i3))*3 + d] 
	// 		= 0.5/numberOfParticles+ ( (d==0)?(double)i1/numberOfParticles : (d==1)?(double)i2/numberOfParticles: (double)i3/ numberOfParticles );
	//  }
	
	// Initialization of particle locations on lattice
	int sitesPerDim = ceil( pow( numberOfParticles, (1.0/dimOfSystem) ) );
	double step = (double) sizeOfSys / sitesPerDim;
	for ( int i = 0; i < dimOfSystem; i++ ){
		for ( int j = 0; j < numberOfParticles; )
			for ( double k = 0 ; k < (sizeOfSys-0.5*step); k+=step ){
				for ( int l = 0; l < pow( sitesPerDim ,i); l++ ){
					coords[ j * dimOfSystem + i ] = k;
					j++;
					if ( j == numberOfParticles ) break;
				}
				if ( j == numberOfParticles ) break;
			}
	}
}

/*-------------------------------------------------------------------
 * Destructor
 * ----------------------------------------------------------------*/

System::~System() { 
	delete coords;
	delete velos;
	delete forces;
	delete forces2;
	cout << "Destructor call." << endl; 
}

/*-------------------------------------------------------------------
 * Return one Coordinate of a Particle
 * ----------------------------------------------------------------*/

double System::GetCoordinate ( int partNumber, int axis) const {
	return (coords)[partNumber*dimOfSystem + axis];
}

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates, velocities,
 * calculates initial Forces and takes a Mass.
 *------------------------------------------------------------------*/

System::System( int newNumberOfParticles, int newDimOfSystem, 
		double newTempOfSystem, double newSizeOfSys, float newMass) {

	tempOfSystem = newTempOfSystem;
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;
	sizeOfSys = newSizeOfSys;
	mass = newMass;
	MAX_CUTOFF = 5.039684;
	forces2 = new double[ numberOfParticles * dimOfSystem ];
	forces = new double[ numberOfParticles * dimOfSystem ];
	velos = new double[ numberOfParticles * dimOfSystem ];
	coords = new double[ numberOfParticles * dimOfSystem ];

	// Initialization of particle locations on lattice
	int sitesPerDim = ceil( pow( numberOfParticles, (1.0/dimOfSystem) ) );
	double step = (double) sizeOfSys / sitesPerDim;
	for ( int i = 0; i < dimOfSystem; i++ ){
		for ( int j = 0; j < numberOfParticles; )
			for ( double k = 0.5*step ; k < (sizeOfSys); k+=step ){
				for ( int l = 0; l < pow( sitesPerDim ,i); l++ ){
					coords[ j * dimOfSystem + i ] = k;
					j++;
					if ( j == numberOfParticles ) break;
				}
				if ( j == numberOfParticles ) break;
			}
	}

	/*Random Particlelocations Generator 
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )
			(coords)[i*dimOfSystem + j] = (float) rand() / INT_MAX * sizeOfSys ;
			*/

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
				diffV[k] -= sizeOfSys * round ( diffV[k] / sizeOfSys );
				
				/*if( diffV[k] > sizeOfSys/2 ) {
					diffV[k] = diffV[k] - sizeOfSys;
				} else if ( diffV[k] < - sizeOfSys/2 ) {
					diffV[k] = diffV[k] + sizeOfSys;
				}*/

				rsq += pow(diffV[k],2);
			}

			//Check cutoff distance, save force
			if ( rsq > MAX_CUTOFF ){} else
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
double System::GetDistanceSq( int partNumOne, int partNumTwo ) const {
	double dist = 0;
	double coordDiff = 0;
	for ( int j = 0; j < dimOfSystem-1; j++ ) {
		coordDiff = coords[ partNumTwo*dimOfSystem + j] 
			- coords[ partNumOne*dimOfSystem + j];
		coordDiff = coordDiff - sizeOfSys*round( coordDiff/sizeOfSys );
		coordDiff*=coordDiff;
		dist += coordDiff;
	}
/**/
	coordDiff = coords[ partNumTwo*dimOfSystem + 2] 
		- coords[ partNumOne*dimOfSystem + 2];
	coordDiff = coordDiff - 2*sizeOfSys*round( coordDiff/(2*sizeOfSys) );
	coordDiff*=coordDiff;
	dist += coordDiff;
/**/
	return dist;
}

/*--------------------------------------------------------------------
 * Calculate total energy 
 *------------------------------------------------------------------*/
double System::GetEnergy() const {
	double ene = 0;
	double distSq = 0;
	double normalisation =  127./16384;
	
	for ( int i = 0; i < numberOfParticles; i++ )
		for ( int j = i + 1; j < numberOfParticles; j++ ) {
			distSq = System::GetDistanceSq( i, j );
			( distSq > MAX_CUTOFF ) ? ene += 0 :
				( ene += 4. * ( pow(distSq, -6) - pow(distSq, -3) + normalisation ) );
	}

	return ene;
}
