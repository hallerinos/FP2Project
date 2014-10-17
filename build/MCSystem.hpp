#include "System.hpp"

/*--------------------------------------------------------------------
 * Monte-Carlo step with Metropolis criteria
 *------------------------------------------------------------------*/
double System::MonteCarloStep( double eps ) {
	int choice = rand() % numberOfParticles;
	double tmp[dimOfSystem];
	double ene;
	ene = System::GetEnergy();
	double sigma = 0;

	for ( int j = 0; j < dimOfSystem; j++ ) {
		// save the old coordinates in case of discard
		tmp[j] = coords[ choice*dimOfSystem + j ];
		// choose random step of size eps*rand in {-1,0,1}
		coords[ choice*dimOfSystem + j ] += 
			eps * ( rand() % 3 - 1 ) * sizeOfSys;
		// use round(...) to avoid if statement
		coords[ choice*dimOfSystem + j ] -= sizeOfSys * 
			round( coords[ choice*dimOfSystem + j ] / sizeOfSys - 1./2);
	}

	// ene < 0 => E_before < E_after
	ene -= System::GetEnergy();
	if ( ene < 0 ) {
		// roll a rand in (0, 1) and check Metropolis criteria
		sigma = (float)rand() / INT_MAX;
		if ( sigma > exp( 1./tempOfSystem * ene ) ) {
			// step dismissed - discard coord changes
			for ( int j = 0; j < dimOfSystem; j++ ) {
				coords[ choice*dimOfSystem + j ] = tmp[j];
			};
			return eps*0.999;
		}	
	}
	return eps;
}


