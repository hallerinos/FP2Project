#include "System.hpp"

/*------------------------------------------------------------------
 * Molecular Dynamic Step ( Velocity Verlet )
 * ---------------------------------------------------------------*/
void System::VeloVerletStepMD ( double dT ) {

	//cout << "Distance between 1 and 2: " << GetDistance(0,1) << endl;
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
}

/*------------------------------------------------------------------
 * Molecular Dynamic Step ( Velocity Verlet )
 * ---------------------------------------------------------------*/
double System::GetKinEnergy() const {
	double vsq = 0;
	for ( int i = 0; i < dimOfSystem * numberOfParticles; i++ )
		vsq += pow(velos[i],2);
	return mass*vsq/2;	
}
