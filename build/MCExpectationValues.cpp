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

void readFromFile();
int numOfParticles, dimOfSystem;
double sizeOfSys;
long MC_STEPS, MAX_STEPS;
double tempOfSystem;
double eps;

int main()
{
	readFromFile();
	ifstream energyFile;
	energyFile.open( "plots/" + to_string(eps) + "EnergySeries.txt" );
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
	int corrlength = 10000;
	for ( int n=0; n < MAX_STEPS; n++ ) {
		double tp = 0;
		for ( int i=0; i < MAX_STEPS - n; i++ )
			tp += energies[i]*energies[i+n];
		tp *= 1./(MAX_STEPS-n);
		tp -= energyAvSq;
		tp *= 1./(energySqAv - energyAvSq);
		corr[n] = tp;
		if ( corr[n] < 0 ){ 
			corrlength = n;
			break;
		}
	}

	cout << "Correlation = 0 at: " <<
		( ( corrlength > 1000 ) ? corrlength=1000 : corrlength );

	energyAv = 0;
	for ( int i = 0; i*corrlength < MAX_STEPS; i++ )
		energyAv += energies[i*corrlength];
	energyAv *= 1./(MAX_STEPS/corrlength);

	double variance = 0;
	for ( int i = 0; i*corrlength < MAX_STEPS; i++ )
		variance += (energies[i*corrlength]-energyAv)*(energies[i*corrlength]-energyAv);
	variance *= 1./(MAX_STEPS/corrlength);
	cout << "\nVariance: " << variance << endl;

	cout << "Energy average for uncorrelated data points: " << (double)energyAv/numOfParticles << " pm " << sqrt(variance)/numOfParticles;
	// int i;
	// for ( EVER ) {
	// 	cout << "\nWhich correlation do you want to see?";
	// 	cin >> i;
	// 	cout << corr[i];
	// }
	stringstream cs;
	ofstream corrFile;
	corrFile.open( (string("plots/")+ to_string(eps) +"CorrelationSeries.txt").c_str() );
	for ( int i=0; i < MAX_STEPS; i++ ) 
		cs << setprecision(6) << corr[i] << endl;
	corrFile << cs.str();
	corrFile.close();

	return 0;
}

void readFromFile() {
	ifstream inputFile("SystemSpecs.txt");
	string line;
	if ( inputFile.is_open() ) {
		getline( inputFile, line );
		getline( inputFile, line );
		( numOfParticles = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( dimOfSystem = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( sizeOfSys = atof( line.c_str() ) );

		getline( inputFile, line );
		getline( inputFile, line );
		( tempOfSystem = atoi( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( MC_STEPS = atol( line.c_str() ) );

		getline( inputFile, line );
		getline( inputFile, line );
		( MAX_STEPS = atol( line.c_str() ) );
		
		getline( inputFile, line );
		getline( inputFile, line );
		( eps = atof( line.c_str() ) );
		
		inputFile.close();
	}
}

