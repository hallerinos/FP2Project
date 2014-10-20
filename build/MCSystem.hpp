#include "System.hpp"

/*--------------------------------------------------------------------
 * Draw a random vector on a unit sphere in 3D
 *------------------------------------------------------------------*/
#define PI 3.14159265
double* System::randomVecOnUnitSphere3D() const {
	double* ranVec;
	double 	coord[ dimOfSystem ];
	double 	phi, theta;

	phi		= (double) rand() / INT_MAX;
	theta	= (double) rand() / INT_MAX;

	coord[0] = cos(2*PI*phi)*sin(2*PI*theta);
	coord[1] = sin(2*PI*phi)*sin(2*PI*theta);
	coord[2] = cos(2*PI*theta);

	return ranVec = coord;
}

double System::GetEnergyI( int i ) const {
	double ene = 0;
	double distSq = 0;
	double normalisation = 0; // = 127./16384;
	
	// use two different loops to avoid j==i case
	for ( int j = 0; j < i; j++ ) {
		distSq = System::GetDistanceSq( i, j );
		( distSq > MAX_CUTOFF ) ? ene += 0 :
			( ene += 4. * ( pow(distSq, -6) 
											- pow(distSq, -3) + normalisation ) );
	}
	for ( int j = i+1; j < numberOfParticles; j++ ) {
		distSq = System::GetDistanceSq( i, j );
		( distSq > MAX_CUTOFF ) ? ene += 0 :
			( ene += 4. * ( pow(distSq, -6) 
											- pow(distSq, -3) + normalisation ) );
	}

	return ene;
}
/*--------------------------------------------------------------------
 * Monte-Carlo step with Metropolis criteria
 *------------------------------------------------------------------*/
void System::MonteCarloStep( double eps ) {
	cout << "MCStep";
	int choice = rand() % numberOfParticles;
	double tmp[dimOfSystem];
	double ene = System::GetEnergyI( choice );
	double sigma = 0;
	double* randVec;
	for ( int j = 0; j < dimOfSystem; j++ ) {
		// draw a random vector of a unit sphere
 		randVec = System::randomVecOnUnitSphere3D();
		// save the old coordinates in case of discard
		tmp[j] = coords[ choice*dimOfSystem + j ];
		// do a random step along a unit sphere
		coords[ choice*dimOfSystem + j ] += 
			eps * randVec[j] * sizeOfSys;
		// check PBC, use round(...) to avoid if statement
		coords[ choice*dimOfSystem + j ] -= sizeOfSys * 
			round( coords[ choice*dimOfSystem + j ] / sizeOfSys - 1./2);
	}

	// ene < 0 => E_before < E_after
	ene -= System::GetEnergyI( choice );
	if ( ene < 0 ) {
		// roll a rand in (0, 1) and check Metropolis criteria
		sigma = (float)rand() / INT_MAX;
		if ( sigma > exp( 1./tempOfSystem * ene ) ) {
			// step dismissed - discard coord changes
			for ( int j = 0; j < dimOfSystem; j++ ) {
				coords[ choice*dimOfSystem + j ] = tmp[j];
			};
		}	
	}
}


