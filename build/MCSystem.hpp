#include "System.hpp"

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
			eps * ( rand() % 3 - 1 );
		if ( coords[ choice*dimOfSystem + j ] < 0 ) {
			coords[ choice*dimOfSystem + j ] += sizeOfSys;
		} else if ( coords[ choice*dimOfSystem + j ] > sizeOfSys ) {
			coords[ choice*dimOfSystem + j ] -= sizeOfSys;
		}
	}
	energyAfter = System::GetEnergy();
//	cout << "ej - ei: " << energyAfter - energyBefore << endl;
// 	cout <<	"sigma: " << ( sigma = (float)( rand() % 1000 ) / 1000. ) <<
//		"\texp: " << exp(- 1./tempOfSystem * (energyAfter- energyBefore))<< endl;
	if ( energyBefore < energyAfter ) {
		sigma = (float)( rand() % 1000 ) / 1000.;
		if ( sigma < exp(- 1./tempOfSystem * (energyAfter- energyBefore)) ) {
			// cout << "Yeah, temperature - step accepted" << endl;
		} else {
				// cout << "aww... dismissed" << endl;
				for ( int j = 0; j < dimOfSystem; j++ ) {
					coords[ choice*dimOfSystem + j ] = tmp[j];
				};
		}	
	}
/*
	cout << "New coordinates: " << endl;
	for ( int j = 0; j < dimOfSystem; j++ ) 
		cout << coords[ choice*dimOfSystem + j ] << "\t";
	cout << endl;
*/
}


