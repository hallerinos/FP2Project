#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>

#define EVER ;;
using namespace std;

long MAX_STEPS = 40000;

int main()
{
	ifstream energyFile;
	energyFile.open( "plots/rho_0.349800EnergySeries.txt" );
	
	string line;
	double* energies = new double[ MAX_STEPS ];
	for ( int i=0;  i < MAX_STEPS; i++) {
		getline( energyFile, line );
		energies[i] = atof( line.c_str() );
	}
		
	double energyAv = 0;
	for ( int i = 0; i < MAX_STEPS; i++ )
		energyAv += energies[i];	
	energyAv *= 1./(MAX_STEPS);
	double energyAvSq = energyAv*energyAv;
	cout << "Energy average: " << energyAv << "\tsquared: " << energyAvSq << endl;

//	double variance = 0;
//	for ( int i = 0; i < len; i++ )
//		variance += (energies[i]-energyAv)*(energies[i]-energyAv);
//	cout << "Variance: " << variance << endl;
	
	double energySqAv = 0;
	for ( int i = 0; i < MAX_STEPS; i++ )
		energySqAv += energies[i]*energies[i];
	energySqAv *= 1./MAX_STEPS;
	cout << "Energy squared: " << energySqAv << endl;

	double* corr = new double[MAX_STEPS];
	for ( int n=0; n < MAX_STEPS; n++ ) {
		double tp = 0;
		for ( int i=0; i < MAX_STEPS - n; i++ )
			tp += energies[i]*energies[i+n];
		tp *= 1./(MAX_STEPS-n);
		tp -= energyAvSq;
		tp *= 1./(energySqAv - energyAvSq);
		corr[n] = tp;
	}

	energyAv = 0;
	
	// int i;
	// for ( EVER ) {
	// 	cout << "\nWhich correlation do you want to see?";
	// 	cin >> i;
	// 	cout << corr[i];
	// }
	stringstream cs;
	ofstream corrFile;
	corrFile.open( "plots/CorrelationSeries/CorrelationSeries.txt" );
	for ( int i=0; i < MAX_STEPS; i++ ) 
		cs << setprecision(6) << corr[i] << endl;
	corrFile << cs.str();
	corrFile.close();

	return 0;
}
