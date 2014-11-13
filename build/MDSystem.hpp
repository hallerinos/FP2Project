#include "System.hpp"

/*------------------------------------------------------------------
 * Molecular Dynamic Step ( Velocity Verlet )
 * ---------------------------------------------------------------*/
void System::VeloVerletStepMD ( double dT, bool thermostat, double tempThermos, double thermosCoupling ) {
	
	//Calculate Constants used in the Veloverlet Steps
	
	double c1 = pow(dT,2)/(2*mass);
	double c2 = dT/(2*mass);

	//cout << "Distance between 1 and 2: " << GetDistance(0,1) << endl;
	//Calculate new Coordinates
	
	for (int i = 0; i < dimOfSystem*numberOfParticles; i++){
		coords[i] = coords[i] + velos[i] * dT + forces[i]*c1;
	}
		//Periodic Boundary, Z coordinate gets double length
	for (int i = 0; i < numberOfParticles; i++){
		coords[i*dimOfSystem] -= 
			round( (coords[i*dimOfSystem] / sizeOfSys - 0.5 ) ) * sizeOfSys;
		coords[i*dimOfSystem + 1] -= 
			round( (coords[i*dimOfSystem + 1] / sizeOfSys - 0.5 ) ) * sizeOfSys;
		coords[i*dimOfSystem + 2] -= 
			round((coords[i*dimOfSystem + 2] / (2*sizeOfSys) - 0.5 )) *2* sizeOfSys;
	}

	//Calculate new Forces	
	double rsq;
	double diffV[3];

	for ( int i = 0; i < numberOfParticles * dimOfSystem; i++ )
		forces2[i]=0;

	for ( int i = 0; i < numberOfParticles; i++ ){
		for ( int j = i+1; j < numberOfParticles; j++ ){
			rsq = 0;
			
			//Calculating Distance squared. Seperate for Z coordinate because of
			//doubled length
			for ( int k = 0; k < dimOfSystem-1; k++ ){
				diffV[k] = coords[i*dimOfSystem + k] - coords[j*dimOfSystem + k];
				// Periodic Boundary
				diffV[k] -= sizeOfSys * round( diffV[k] / sizeOfSys );
				
				rsq += pow(diffV[k],2);
			}
				diffV[2] = coords[i*dimOfSystem + 2] - coords[j*dimOfSystem + 2];
				// Periodic Boundary
				diffV[2] -= 2*sizeOfSys * round( diffV[2] / (2*sizeOfSys) );
				
				rsq += pow(diffV[2],2);
			
			//Cutoff Criteria
			if ( rsq > MAX_CUTOFF ) continue;

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

	// Anderson Thermostat
	
	double tempa = 0;
	double random = 0;
	
	if ( thermostat == true ){
		tempa = GetTemperature();
		double v0 = sqrt ( tempThermos / mass ) * 2.0 * ( rand()%2 - 0.5);
		double sigma = sqrt( tempa / numberOfParticles );
		for ( int i = 0; i < numberOfParticles; i++ ){
			random = (double) rand() / INT_MAX;
			if ( random < thermosCoupling * dT ){
				for (int j = 0; j < dimOfSystem; j++){
					double v1 = 0, v2 = 0, r = 2;
					while ( r >= 1 ){
						v1 = (double) rand() / INT_MAX * 2 - 1;
						v2 = (double) rand() / INT_MAX * 2 - 1;
						r = v1*v1 + v2*v2;
					}
					velos[i*dimOfSystem + j] = v0 + v1 * sigma * sqrt( -2. * log(r)/r );
				}	
			}
		}
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

/*------------------------------------------------------------------
 * Calculate Temperature
 * ---------------------------------------------------------------*/
double System::GetTemperature() const {
	double vsq = 0;
	for ( int i = 0; i < dimOfSystem * numberOfParticles; i++ )
		vsq += pow(velos[i],2);
	return mass*vsq/(numberOfParticles*dimOfSystem);	
}

/*-----------------------------------------------------------------
 * Adjust Velocities to Temperature
 * --------------------------------------------------------------*/

void System::AdjustVelos( double oldMeanT, double newT) {
	double rescale = sqrt( newT / oldMeanT );
	for (int i = 0; i < numberOfParticles*dimOfSystem; i++){
	velos[i] = velos[i] * rescale;
	}
}

/*-----------------------------------------------------------------
 * VeloAdjustment by David
 * --------------------------------------------------------------

void System::AdjustVelosDavid( double temp, double nu) {
	double sigma = sqrt ( GetTemperature() );
	
}*/
