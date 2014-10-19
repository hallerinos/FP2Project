#include "System.hpp"

/*------------------------------------------------------------------
 * Molecular Dynamic Step ( Velocity Verlet )
 * ---------------------------------------------------------------*/
void System::VeloVerletStepMD ( double dT ) {
	
	//Calculate Constants used in the Veloverlet Steps
	
	double c1 = pow(dT,2)/(2*mass);
	double c2 = dT/(2*mass);

	//cout << "Distance between 1 and 2: " << GetDistance(0,1) << endl;
	//Calculate new Coordinates
	
	for (int i = 0; i < dimOfSystem*numberOfParticles; i++){
		coords[i] = coords[i] + velos[i] * dT + forces[i]*c1;
		//Periodic Boundary
		coords[i] = coords[i] 
			- round( (coords[i] / sizeOfSys - 0.5 ) ) * sizeOfSys;
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
				// Periodic Boundary
				diffV[k] = diffV[k] - sizeOfSys * round( diffV[k] / sizeOfSys );
				
				rsq += pow(diffV[k],2);
			}
			
			//Cutoff Criteria
			if ( rsq > 9 ) continue;

			double forceFactor = 48 / pow(rsq,7) - 24 / pow(rsq,4);
			
			for ( int k = 0; k < dimOfSystem; k++ ){
				forces2[i*dimOfSystem + k] += diffV[k] * ( forceFactor );
				forces2[j*dimOfSystem + k] -= diffV[k] * ( forceFactor );
			}
		}			
	}

	//Calculate new Velocities
	
	for (int i = 0; i < dimOfSystem * numberOfParticles; i++){
		velos[i] = velos[i] + (forces[i] + forces2[i])*c2;
	}

	//overWrite old Forces
	
	for (int i = 0; i < dimOfSystem * numberOfParticles; i++){
		forces[i] = forces2[i];
	}

	/*cout << "New Coordinate 1: " << coords[0] << "\t" << coords[1] << "\t"
		<< coords[2] << endl;
	cout << "New Coordinate 2: " << coords[3] << "\t" << coords[2] << "\t"
		<< coords[3] << endl;*/
}

/*------------------------------------------------------------------
 * Calculate Kinetic Energy
 * ---------------------------------------------------------------*/
double System::GetKinEnergy() const {
	double vsq = 0;
	for ( int i = 0; i < dimOfSystem * numberOfParticles; i++ )
		vsq += pow(velos[i],2);
	return mass*vsq/2;	
}

/*-----------------------------------------------------------------
 * Adjust Velocities to Maxwell-Boltzmann Distribution
 * --------------------------------------------------------------*/

void System::AdjustVelos() {
	double vsq = 0, vnew = 0, vmax = sqrt( dimOfSystem * tempOfSystem / mass);
	double random = 0;
	double c1 = sqrt( mass / (2 * 3.1416 * dimOfSystem * tempOfSystem) );
	double c2 = mass / (2 * dimOfSystem * tempOfSystem);
	for (int i = 0; i < numberOfParticles; i++){
		vsq = 0;
		for (int j = 0; j < dimOfSystem; j++)
			vsq += pow( velos[i*dimOfSystem + j], 2);
		// Set new Velocity
		vnew = (double) rand() / INT_MAX * 4 * vmax;
		random = (double) rand() / INT_MAX;
		// Check Boltzmann
		if ( random < (c1 * exp(-c2 *pow(vnew,2))) ){
			for (int j = 0; j < dimOfSystem; j++)
				velos[i*dimOfSystem+j] = velos[i*dimOfSystem+j] * vnew / sqrt(vsq);
		}
	}
}
