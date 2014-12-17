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
	energyFile.open( "Energys.txt" );
	string line;
	int len = 95000;

	double energies[ len ];
	for ( int i=0;  i < len; i++) {
		getline( energyFile, line );
		energies[i] = atof( line.c_str() );
	}
		
	double energyAv = 0;
	for ( int i = 0; i < len; i++ )
		energyAv += energies[i];	
	energyAv *= 1./(len);
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
		tp *= 1./(len-n);
		tp -= energyAvSq;
		tp *= 1./(energySqAv - energyAvSq);
		corr[n] = tp;
	}
	int i;

	ofstream corrs;
	corrs.open ( "Correlations.txt" );
	for ( i = 0; i < len; i++)
		corrs << corr[i] << endl;

	for ( EVER ) {
		cout << "\nWhich correlation do you want to see?";
		cin >> i;
		cout << corr[i];
	}
	return 0;
}
