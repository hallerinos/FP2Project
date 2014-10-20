#include <iostream>

using namespace std;
int main()
{
	int numPartPerDim = 5;
	double *coords = new double[numPartPerDim*numPartPerDim*numPartPerDim*3];
	
	for ( int i3=0; i3<numPartPerDim; i3++)
	for ( int d = 0; d < 3; d++ ) 
	for ( int i2=0; i2<numPartPerDim; i2++)
	for ( int i1=0; i1<numPartPerDim; i1++)
	 {	
		coords[(i1 + numPartPerDim*(i2 + numPartPerDim*i3))*3 + d] 
			= 0.5/numPartPerDim + ( (d==0)?(double)i1/numPartPerDim : (d==1)?(double)i2/numPartPerDim : (double)i3/numPartPerDim );
	 }

	cout << "X\tY\tZ" << endl;	
	for ( int i=0; i< numPartPerDim*numPartPerDim*numPartPerDim; (cout << "Particle: " << ++i << endl) ) {
		for ( int d=0; d<3; d++)
			cout << coords[i*3 + d] << "\t";
	}
	return 0;
}
