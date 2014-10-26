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


int main()
{
	ofstream tempEn;
	tempEn.open( "Temp_Pot.txt", ios::app );
	//Calculation Mean and Error of Temp
	ifstream energyFile;
	energyFile.open( "Temperatures.txt" );
	string line;
	int len = 2900;

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

//	double variance = 0;
//	for ( int i = 0; i < len; i++ )
//		variance += (energies[i]-energyAv)*(energies[i]-energyAv);
//	cout << "Variance: " << variance << endl;
	
	double energySqAv = 0;
	for ( int i = 0; i < len; i++ )
		energySqAv += energies[i]*energies[i];
	energySqAv *= 1./len;
	double error = sqrt( (energySqAv - energyAvSq) / len );
	cout << "T = " << energyAv << " +- " << error << endl;
	tempEn << energyAv << "\t" << error << "\t"; 
	energyFile.close();
		
	//Calculation Mean and Error of Pot Energy
	energyFile.open( "Energys.txt" );

	for ( int i=0;  i < len; i++) {
		getline( energyFile, line );
		energies[i] = atof( line.c_str() );
	}
		
	energyAv = 0;
	for ( int i = 0; i < len; i++ )
		energyAv += energies[i];	
	energyAv *= 1./(len);
	energyAvSq = energyAv*energyAv;

//	double variance = 0;
//	for ( int i = 0; i < len; i++ )
//		variance += (energies[i]-energyAv)*(energies[i]-energyAv);
//	cout << "Variance: " << variance << endl;
	
	energySqAv = 0;
	for ( int i = 0; i < len; i++ )
		energySqAv += energies[i]*energies[i];
	energySqAv *= 1./len;
	error = sqrt( (energySqAv - energyAvSq) / len );
	cout << "EPot = " << energyAv << " +- " << error << endl;
	tempEn << energyAv << "\t" << error << endl;
	return 0;
}
