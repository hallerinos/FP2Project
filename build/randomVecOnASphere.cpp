#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265
using namespace std;

double * randomVecOnUnitSphere();
int main()
{
	srand( time(NULL) );
	double * coord;
	cout << "X\t\tY\t\tZ\t\t"<<endl;
	for ( int i = 0; i < 1000; i++ ) {
		coord = randomVecOnUnitSphere();	
		cout << coord[0] << "\t" << coord[1] << "\t" << coord[2];
		cout << "\t\tNorm: " << coord[0]*coord[0] + coord[1]*coord[1] + coord[2]*coord[2] << endl;
	}
	return 0;
}

double * randomVecOnUnitSphere() {
	double * coord = new double[3];
	double phi, theta;
	phi		= (double) rand() / INT_MAX;
	theta	= (double) rand() / INT_MAX;
	coord[0] = cos(2*PI*phi)*sin(2*PI*theta);
	coord[1] = sin(2*PI*phi)*sin(2*PI*theta);
	coord[2] = cos(2*PI*theta);

	return coord;
}
