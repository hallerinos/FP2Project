#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <stdlib.h>

using namespace std;

double* randomVecOnUnitSphere3D();

int main()
{
	srand( time(NULL) );

	double* vec;
	ofstream fout;
	fout.open( "randomSphere.txt" );
	fout << "X\tY\tZ" << endl;
	long step = 0;
	while ( step < 10000 ) {
		vec = randomVecOnUnitSphere3D();	
		fout << setprecision(7) << vec[0] << "\t" << vec[1] << "\t" << vec[2] << "\t";
		fout << endl;
		step++;
	}
	fout.close();

	return 0;
}

#define PI 3.14159265
double* randomVecOnUnitSphere3D() {
	double* coord = new double[3];
	double 	u, theta;

	u			= (double)2*rand()/INT_MAX - 1;
	theta = ((double)2*rand()/INT_MAX - 1)*PI;

	coord[0] = sqrt( 1 - u*u ) * cos(theta);
	coord[1] = sqrt( 1 - u*u ) * sin(theta);
	coord[2] = u;

	return coord;
}
