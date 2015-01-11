#include "System.hpp"

/*--------------------------------------------------------------------
 * Draw a random vector on a unit sphere in 3D
 *------------------------------------------------------------------*/
#define PI 3.14159265
	double* System::makeRandomOnUnitSphere( double* vec ) const {
	double* returnVec;
 	returnVec	= vec;
	double 	u, theta;

	u			= (double)2*rand()/INT_MAX - 1;
	theta = ((double)2*rand()/INT_MAX - 1)*PI;

	returnVec[0] = sqrt( 1 - u*u ) * cos(theta);
	returnVec[1] = sqrt( 1 - u*u ) * sin(theta);
	returnVec[2] = u;

	return returnVec;
}

double System::GetEnergyI( int i ) const {
	double ene = 0;
	double distSq = 0;
	double normalisation = 127./16384;
	
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

long System::GetAcceptedSteps() {
	int temp = acceptedSteps;
	acceptedSteps = 0;
	return temp;
}

/*--------------------------------------------------------------------
 * Monte-Carlo step with Metropolis criteria
 *------------------------------------------------------------------*/
void System::MonteCarloStep( double eps ) {
	int choice = rand() % numberOfParticles;
	double tmp[dimOfSystem];
	double ene = System::GetEnergyI( choice );
	double sigma = 0;
	double* randVec = new double[ dimOfSystem ];
	acceptedSteps++;
	for ( int j = 0; j < dimOfSystem-1; j++ ) {
		// draw a random vector of a unit sphere
 		randVec = System::makeRandomOnUnitSphere( randVec );
		// save the old coordinates in case of discard
		tmp[j] = coords[ choice*dimOfSystem + j ];
		// do a random step along a unit sphere
		coords[ choice*dimOfSystem + j ] += 
			eps * randVec[j] * sizeOfSys;
		// check PBC, use round(...) to avoid if statement
		coords[ choice*dimOfSystem + j ] -= sizeOfSys * 
			round( coords[ choice*dimOfSystem + j ] / sizeOfSys - 1./2);
	}
/**/
	// draw a random vector of a unit sphere
 	randVec = System::makeRandomOnUnitSphere( randVec );
	// save the old coordinates in case of discard
	tmp[2] = coords[ choice*dimOfSystem + 2 ];
	// do a random step along a unit sphere
	coords[ choice*dimOfSystem + 2 ] += 
		eps * randVec[2] * sizeOfSys;
	// check PBC, use round(...) to avoid if statement
	coords[ choice*dimOfSystem + 2 ] -= 2 * sizeOfSys * 
		round( coords[ choice*dimOfSystem + 2 ] / (2*sizeOfSys) - 1./2);
/**/
	// ene < 0 => E_before < E_after
	ene -= System::GetEnergyI( choice );
	if ( ene < 0 ) {
		// roll a rand in (0, 1) and check Metropolis criteria
		if ( ene < -100 || (sigma = (float)rand() / INT_MAX) > exp( 1./tempOfSystem * ene ) ) {
			// step dismissed - discard coord changes
			for ( int j = 0; j < dimOfSystem; j++ ) {
				coords[ choice*dimOfSystem + j ] = tmp[j];
			};
			acceptedSteps--;
		}	
	}
	
	delete randVec;
}

void System::MonteCarloStep2() {
	double sigma = (double)(rand()%INT_MAX)/INT_MAX;
	acceptedSteps++;

	if( rand()%2 ) {
		cout << "Particle inserted.";
		numberOfParticles++;
		for( int i=0; i<2; i++){
			coords[numberOfParticles*dimOfSystem + i] = (double)sizeOfSys*((rand()%INT_MAX)/INT_MAX);
		}
		coords[numberOfParticles*dimOfSystem + 2] = (double)2*sizeOfSys*((rand()%INT_MAX)/INT_MAX); 
		double energy = System::GetEnergyI(numberOfParticles);
		cout << (energy!=energy);
		if ( energy != energy || energy > 20 || sigma > sizeOfSys*sizeOfSys*2*sizeOfSys/(numberOfParticles+1)*exp(-(energy-chemPot)/tempOfSystem) ) {
			acceptedSteps--;
			for( int i=0; i<dimOfSystem; i++ )
				coords[numberOfParticles*dimOfSystem + i] = 0;
		}
	} else { 	
		cout << "Particle deleted.";
		int choice = rand() % numberOfParticles;
		double tp[dimOfSystem];
		double energy = System::GetEnergyI(choice);
		for( int i=0; i<dimOfSystem; i++ ) {
			tp[i] = coords[numberOfParticles*dimOfSystem + i];
			for ( int j=choice; j<numberOfParticles-1; j++)
				coords[j*dimOfSystem+i]=coords[(j+1)*dimOfSystem+i];
			coords[numberOfParticles*dimOfSystem + i] = 0;
		}
		numberOfParticles--;
		if ( energy > 20 || sigma > sizeOfSys*sizeOfSys*2*sizeOfSys/(numberOfParticles+1)*exp((energy-chemPot)/tempOfSystem) ) {
			acceptedSteps--;
			numberOfParticles++;
			for( int i=0; i<dimOfSystem; i++ )
				coords[numberOfParticles*dimOfSystem + i] = tp[i];
		}
	}
}

void System::InsertParticle() {
}

void System::DeleteParticle() {
}
