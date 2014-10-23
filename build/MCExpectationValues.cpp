#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#define EVER ;;
using namespace std;


int main()
{
	ifstream energyFile;
	energyFile.open( "plots/EnergySeries.txt" );
	string line;
	int len = 0;
	if ( energyFile.is_open() ) {
		getline( energyFile, line ); cout << line << endl;
		getline( energyFile, line ); cout << ( len = atoi( line.c_str() ) ) << endl;
		getline( energyFile, line ); cout << line << endl;
		getline( energyFile, line ); cout << line << endl;
		getline( energyFile, line ); cout << line << endl;
		getline( energyFile, line ); cout << line << endl;
	}

	double energies[ len ];
	for ( int i=0;  i < len; i++) {
		getline( energyFile, line );
		energies[i] = atof( line.c_str() );
	}
		
	double energyAv = 0;
	for ( int i = 0; i < len; i=i+29 )
		energyAv += energies[i+50];	
	energyAv *= 1./(len/29.-2);
	double energyAvSq = energyAv*energyAv;
	cout << "Energy average: " << energyAv << "\tsquared: " << energyAvSq << endl;

//	double variance = 0;
//	for ( int i = 0; i < len; i++ )
//		variance += (energies[i]-energyAv)*(energies[i]-energyAv);
//	cout << "Variance: " << variance << endl;
	
	double energySqAv = 0;
	for ( int i = 0; i < len; i++ )
		energySqAv += energies[i]*energies[i];
	energySqAv *= 1./len;
	cout << "Energy squared: " << energySqAv << endl;

	double corr[len];
	for ( int n=0; n < len; n++ ) {
		double tp = 0;
		for ( int i=0; i < len - n; i++ )
			tp += energies[i]*energies[i+n];
		tp *= 1./len;
		tp -= energyAvSq;
		tp *= 1./(energySqAv - energyAvSq);
		corr[n] = tp;
	}
	int i;
	for ( EVER ) {
		cout << "\nWhich correlation do you want to see?";
		cin >> i;
		cout << corr[i];
	}
	return 0;
}
